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
    //创建文件file-bat.txt，并以写的方式打开该文件
    int fdout = open("file-bat.txt", O_CREAT | O_WRONLY, 0666);
    if (fdout < 0) {
        perror("open");
        return 3;
    }
    char msg[128];
    while (1) {
        msg[0] = '\0'; //每次读之前将msg清空
        //从命名管道当中读取信息
        ssize_t s = read(fd, msg, sizeof(msg) - 1);
        printf("msg:%s s:%d\n", msg, s);
        if (s > 0) {
          write(fdout, msg, s);  //将读取到的信息写入到file-bat.txt文件当中
        } else if (s == 0) {
          printf("client quit!\n");
          break;
        } else {
          printf("read error!\n");
          break;
        }
    }
    close(fd);    //通信完毕，关闭命名管道文件
    close(fdout); //数据写入完毕，关闭file-bat.txt文件
    return 0;
}
