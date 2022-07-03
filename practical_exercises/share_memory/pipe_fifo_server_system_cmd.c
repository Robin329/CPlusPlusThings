#include "pipe_fifo_comm.h"

int main() {
    umask(0);                          //将文件默认掩码设置为0
    if (access(FILE_NAME, F_OK))
        if (mkfifo(FILE_NAME, 0666) < 0) { //使用mkfifo创建命名管道文件
            perror("mkfifo");
            return 1;
        }
    int fd = open(FILE_NAME, O_RDONLY); //以读的方式打开命名管道文件
    if (fd < 0) {
        perror("open");
        return 2;
    }
    char msg[128];
    while (1) {
	    msg[0] = '\0'; //每次读之前将msg清空
	    //从命名管道当中读取信息
	    ssize_t s = read(fd, msg, sizeof(msg) - 1);
	    if (s > 0) {
		    msg[s] = '\0'; //手动设置'\0'，便于输出
		    printf("client# %s\n", msg);
		    int ret[1024] = { 0 };
		    int num = 0;
		    if (fork() == 0) {
			    // child
			    execlp(msg, msg, NULL); //进程程序替换
			    exit(1);
		    }
		    waitpid(-1, NULL, 0); //等待子进程
	    } else if (s == 0) {
		    printf("client quit!\n");
		    break;
	    } else {
		    printf("read error!\n");
		    break;
	    }
    }
    close(fd); //通信完毕，关闭命名管道文件
    return 0;
}
