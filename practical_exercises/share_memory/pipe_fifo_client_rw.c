#include "pipe_fifo_comm.h"
// NOTE:Need create file.txt
int main() {
    int fd = open(FILE_NAME, O_WRONLY); //以写的方式打开命名管道文件
    if (fd < 0) {
        perror("open");
        return 1;
    }
    int fdin = open("file.txt", O_RDONLY); //以读的方式打开file.txt文件
    if (fdin < 0) {
        perror("open");
        return 2;
    }
    char msg[128];
    while (1) {
        //从file.txt文件当中读取数据

        ssize_t s = read(fdin, msg, sizeof(msg));
        printf("msg:%s\n", msg);
        if (s > 0) {
            write(fd, msg, s); //将读取到的数据写入到命名管道当中
        } else if (s == 0) {
            printf("read end of file!\n");
            break;
        } else {
            printf("read error!\n");
            break;
        }
    }
    close(fd);   //通信完毕，关闭命名管道文件
    close(fdin); //数据读取完毕，关闭file.txt文件
    return 0;
}
