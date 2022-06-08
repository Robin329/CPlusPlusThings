// 1. mkfifo fifo
//
// 2. write:
// while :; do echo "hello fifo"; sleep 1; done> fifo
//
// 3. read:
// cat < fifo

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILE_NAME "myfifo"

int main() {
    // 但实际上创建出来文件的权限值还会受到umask（文件默认掩码）的影响，
    // 实际创建出来文件的权限为：mode&(~umask)。umask的默认值一般为0002，当我们设置mode值为0666时实际创建出来文件的权限为0664。
    umask(0);                          //将文件默认掩码设置为0
    if (mkfifo(FILE_NAME, 0666) < 0) { //使用mkfifo创建命名管道文件
        perror("mkfifo");
        return 1;
    }
    // create success...

    return 0;
}
