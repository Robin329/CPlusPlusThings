#include "pipe_fifo_comm.h"

int main() {
    umask(0);                          //将文件默认掩码设置为0
    if (access(FILE_NAME, F_OK)) {
        if (mkfifo(FILE_NAME, 0666) < 0) { //使用mkfifo创建命名管道文件
            perror("mkfifo");
            return 1;
        }
    }
    int fd = open(FILE_NAME, O_RDONLY); //打开命名管道文件
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
            //服务端进行计算任务
            char* lable = "+-*/%";
            char* p = msg;
            int flag = 0;
            while (*p) {
                switch (*p) {
                    case '+':
                        flag = 0;
                        break;
                    case '-':
                        flag = 1;
                        break;
                    case '*':
                        flag = 2;
                        break;
                    case '/':
                        flag = 3;
                        break;
                    case '%':
                        flag = 4;
                        break;
                }
                p++;
            }
            char* data1 = strtok(msg, "+-*/%");
            char* data2 = strtok(NULL, "+-*/%");
            int num1 = atoi(data1);
            int num2 = atoi(data2);
            int ret = 0;
            switch (flag) {
                case 0:
                    ret = num1 + num2;
                    break;
                case 1:
                    ret = num1 - num2;
                    break;
                case 2:
                    ret = num1 * num2;
                    break;
                case 3:
                    ret = num1 / num2;
                    break;
                case 4:
                    ret = num1 % num2;
                    break;
            }
            printf("%d %c %d = %d\n", num1, lable[flag], num2, ret); //打印计算结果
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
