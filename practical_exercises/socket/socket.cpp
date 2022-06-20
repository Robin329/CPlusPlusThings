
#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>

#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

int socket_close(int sock)
{
	return close(sock);
}
#define LISTEN_BACKLOG 4

/* open listen() port on any interface */
int socket_inaddr_any_server(int port, int type)
{
	struct sockaddr_in6 addr;
	int s, n;

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	addr.sin6_addr = in6addr_any;

	s = socket(AF_INET6, type, 0);
	if (s < 0)
		return -1;

	n = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *)&n, sizeof(n));

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		close(s);
		return -1;
	}

	if (type == SOCK_STREAM) {
		int ret;

		ret = listen(s, LISTEN_BACKLOG);

		if (ret < 0) {
			close(s);
			return -1;
		}
	}

	return s;
}

static int toggle_O_NONBLOCK(int s)
{
	int flags = fcntl(s, F_GETFL);
	if (flags == -1 || fcntl(s, F_SETFL, flags ^ O_NONBLOCK) == -1) {
		close(s);
		return -1;
	}
	return s;
}

// Connect to the given host and port.
// 'timeout' is in seconds (0 for no timeout).
// Returns a file descriptor or -1 on error.
// On error, check *getaddrinfo_error (for use with gai_strerror) first;
// if that's 0, use errno instead.
int socket_network_client_timeout(const char *host, int port, int type,
				  int timeout, int *getaddrinfo_error)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = type;

	char port_str[16];
	snprintf(port_str, sizeof(port_str), "%d", port);

	struct addrinfo *addrs;
	*getaddrinfo_error = getaddrinfo(host, port_str, &hints, &addrs);
	if (*getaddrinfo_error != 0) {
		return -1;
	}

	int result = -1;
	for (struct addrinfo *addr = addrs; addr != NULL;
	     addr = addr->ai_next) {
		// The Mac doesn't have SOCK_NONBLOCK.
		int s = socket(addr->ai_family, type, addr->ai_protocol);
		if (s == -1 || toggle_O_NONBLOCK(s) == -1)
			break;

		int rc = connect(s, addr->ai_addr, addr->ai_addrlen);
		if (rc == 0) {
			result = toggle_O_NONBLOCK(s);
			break;
		} else if (rc == -1 && errno != EINPROGRESS) {
			close(s);
			continue;
		}

		fd_set r_set;
		FD_ZERO(&r_set);
		FD_SET(s, &r_set);
		fd_set w_set = r_set;

		struct timeval ts;
		ts.tv_sec = timeout;
		ts.tv_usec = 0;
		if ((rc = select(s + 1, &r_set, &w_set, NULL,
				 (timeout != 0) ? &ts : NULL)) == -1) {
			close(s);
			break;
		}
		if (rc == 0) { // we had a timeout
			errno = ETIMEDOUT;
			close(s);
			break;
		}

		int error = 0;
		socklen_t len = sizeof(error);
		if (FD_ISSET(s, &r_set) || FD_ISSET(s, &w_set)) {
			if (getsockopt(s, SOL_SOCKET, SO_ERROR, &error, &len) <
			    0) {
				close(s);
				break;
			}
		} else {
			close(s);
			break;
		}

		if (error) { // check if we had a socket error
			// TODO: Update the timeout.
			errno = error;
			close(s);
			continue;
		}

		result = toggle_O_NONBLOCK(s);
		break;
	}

	freeaddrinfo(addrs);
	return result;
}

int socket_network_client(const char *host, int port, int type)
{
	int getaddrinfo_error;
	return socket_network_client_timeout(host, port, type, 0,
					     &getaddrinfo_error);
}

int socket_set_receive_timeout(cutils_socket_t sock, int timeout_ms)
{
	timeval tv;
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;
	return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

ssize_t socket_send_buffers(cutils_socket_t sock,
			    const cutils_socket_buffer_t *buffers,
			    size_t num_buffers)
{
	if (num_buffers > SOCKET_SEND_BUFFERS_MAX_BUFFERS) {
		return -1;
	}

	iovec iovec_buffers[SOCKET_SEND_BUFFERS_MAX_BUFFERS];
	for (size_t i = 0; i < num_buffers; ++i) {
		// It's safe to cast away const here; iovec declares non-const
		// void* because it's used for both send and receive, but since
		// we're only sending, the data won't be modified.
		iovec_buffers[i].iov_base = const_cast<void *>(buffers[i].data);
		iovec_buffers[i].iov_len = buffers[i].length;
	}

	return writev(sock, iovec_buffers, num_buffers);
}

#if defined(__ANDROID__)
int android_get_control_socket(const char *name)
{
	int fd =
		__android_get_control_from_env(ANDROID_SOCKET_ENV_PREFIX, name);

	if (fd < 0)
		return fd;

	// Compare to UNIX domain socket name, must match!
	struct sockaddr_un addr;
	socklen_t addrlen = sizeof(addr);
	int ret = getsockname(fd, (struct sockaddr *)&addr, &addrlen);
	if (ret < 0)
		return -1;

	constexpr char prefix[] = ANDROID_SOCKET_DIR "/";
	constexpr size_t prefix_size = sizeof(prefix) - sizeof('\0');
	if ((strncmp(addr.sun_path, prefix, prefix_size) == 0) &&
	    (strcmp(addr.sun_path + prefix_size, name) == 0)) {
		// It is what we think it is
		return fd;
	}
	return -1;
}
#else
int android_get_control_socket(const char *)
{
	return -1;
}
#endif

int socket_get_local_port(cutils_socket_t sock)
{
	sockaddr_storage addr;
	socklen_t addr_size = sizeof(addr);

	if (getsockname(sock, reinterpret_cast<sockaddr *>(&addr),
			&addr_size) == 0) {
		// sockaddr_in and sockaddr_in6 always overlap the port field.
		return ntohs(reinterpret_cast<sockaddr_in *>(&addr)->sin_port);
	}
	return -1;
}
