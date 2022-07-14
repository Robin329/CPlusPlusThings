#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("[%s:%d] fork failed!!!\n", __FUNCTION__, __LINE__);
    } else if (pid == 0) {
        if ((pid = fork()) < 0) {
            printf("[%s:%d] fork failed!!!, pid:%d\n", __FUNCTION__, __LINE__, pid);
        } else if (pid > 0) { // first child pid
            printf("[%s:%d] first child fork failed!!!!, pid:%d\n", __FUNCTION__, __LINE__, getppid());
            return 0;
        }
        sleep(1); // second child pid
        printf("[%s:%d] second child fork success!!!!, pid:%d\n", __FUNCTION__, __LINE__, getppid());
        return 0;
    }
    printf("[%s:%d] parent pid:%d\n", __FUNCTION__, __LINE__, getppid()); // parent pid
    if (waitpid(pid, NULL, 0) != pid) {
        printf("[%s:%d] waitpid error!!!!, pid:%d\n", __FUNCTION__, __LINE__, pid);
    }
    return 0;
}
