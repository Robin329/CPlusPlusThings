#include "pipe_fifo_comm.h"

int main() {
    int fd = open(FILE_NAME, O_WRONLY); //以写的方式打开命名管道文件
    if (fd < 0) {
        perror("open");
        return 1;
    }
    char msg[128];
    while (1) {
        msg[0] = '\0';            //每次读之前将msg清空
        printf("Please Enter# "); //提示客户端输入
        fflush(stdout);
        //从客户端的标准输入流读取信息
        // 0 : stdin
        // 1 : stdout
        // 2 : stderr
        ssize_t s = read(0, msg, sizeof(msg) - 1);
        if (s > 0) {
            msg[s - 1] = '\0';
            //将信息写入命名管道
            write(fd, msg, strlen(msg));
        }
    }
    close(fd); //通信完毕，关闭命名管道文件
    return 0;
}
