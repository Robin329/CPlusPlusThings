#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int fd[2] = {0};
    if (pipe(fd) < 0) { //使用pipe创建匿名管道
        perror("pipe");
        return 1;
    }
    pid_t id = fork(); //使用fork创建子进程
    if (id == 0) {
        // child
        close(fd[0]); //子进程关闭读端
        //子进程向管道写入数据
        const char* msg = "hello father, I am child...";
        int count = 10;
        while (count--) {
            write(fd[1], msg, strlen(msg));
            sleep(1);
        }
        close(fd[1]); //子进程写入完毕，关闭文件
        exit(0);
    }
    // father
    close(fd[1]); //父进程关闭写端
    close(fd[0]); //父进程直接关闭读端（导致子进程被操作系统杀掉）
    int status = 0;
    waitpid(id, &status, 0);
    printf("child get signal:%d\n", status & 0x7F); //打印子进程收到的信号
    return 0;
}
// # kill -l
//  1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
//  6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
// 11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
// 16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
// 21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
// 26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
// 31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
// 38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
// 43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
// 48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
// 53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
// 58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
// 63) SIGRTMAX-1  64) SIGRTMAX