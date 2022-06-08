#include "shm_comm.h"

int main() {
    key_t key = ftok(PATHNAME, PROJ_ID); //获取key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
    int shm = shmget(key, SIZE, IPC_CREAT | IPC_EXCL); //创建新的共享内存
    if (shm < 0) {
        perror("shmget");
        return 2;
    }
    printf("key: %x\n", key); //打印key值
    printf("shm: %d\n", shm); //打印句柄

    sleep(2);
    shmctl(shm, IPC_RMID, NULL); //释放共享内存
    sleep(2);
    return 0;
}
// shmctl函数的参数说明：

// 第一个参数shmid，表示所控制共享内存的用户级标识符。
// 第二个参数cmd，表示具体的控制动作。
// 第三个参数buf，用于获取或设置所控制共享内存的数据结构。
// shmctl函数的返回值说明：

// shmctl调用成功，返回0。
// shmctl调用失败，返回-1。
// 其中，作为shmctl函数的第二个参数传入的常用的选项有以下三个：

// 选项	作用
// IPC_STAT	获取共享内存的当前关联值，此时参数buf作为输出型参数
// IPC_SET	在进程有足够权限的前提下，将共享内存的当前关联值设置为buf所指的数据结构中的值
// IPC_RMID	删除共享内存段
