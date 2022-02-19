//
// Created by renbin jiang on 2022/2/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_RESULT_BUF_SIZE 1024

/*
 * cmd：待执行命令
 * result：命令输出结果
 * 函数返回：0 成功；-1 失败；
 */
int ExecuteCMD(const char *cmd, char *result) {
    int iRet = -1;
    char buf_ps[CMD_RESULT_BUF_SIZE];
    char ps[CMD_RESULT_BUF_SIZE] = {0};
    FILE *ptr;

    strcpy(ps, cmd);

    if ((ptr = popen(ps, "r")) != NULL) {
        while (fgets(buf_ps, sizeof(buf_ps), ptr) != NULL) {
            strcat(result, buf_ps);
            if (strlen(result) > CMD_RESULT_BUF_SIZE) {
                break;
            }
        }
        pclose(ptr);
        ptr = NULL;
        iRet = 0; // 处理成功
    } else {
        printf("popen %s error\n", ps);
        iRet = -1; // 处理失败
    }

    return iRet;
}

int main() {
    char result[CMD_RESULT_BUF_SIZE] = {0};

    // ExecuteCMD("ls -help", result);
    system("ls -help");
    printf("This is an example\n\n");
    printf("%s\n", result);
    printf("\n\nThis is end\n");

    return 0;
}