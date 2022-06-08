#include "shm_comm.h"

int main() {
    key_t key = ftok(PATHNAME, PROJ_ID); //获取key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
    int shm = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666); //创建新的共享内存
    if (shm < 0) {
        perror("shmget");
        return 2;
    }
    printf("key: %x\n", key); //打印key值
    printf("shm: %d\n", shm); //打印句柄

    printf("attach begin!\n");
    sleep(2);
    char* mem = shmat(shm, NULL, 0); //关联共享内存
    if (mem == (void*)-1) {
        perror("shmat");
        return 1;
    }
    printf("attach end!\n");
    sleep(2);

    shmctl(shm, IPC_RMID, NULL); //释放共享内存
    return 0;
}
// 将共享内存连接到进程地址空间我们需要用shmat函数，shmat函数的函数原型如下：

// void *shmat(int shmid, const void *shmaddr, int shmflg);
// 1
// shmat函数的参数说明：

// 第一个参数shmid，表示待关联共享内存的用户级标识符。
// 第二个参数shmaddr，指定共享内存映射到进程地址空间的某一地址，通常设置为NULL，表示让内核自己决定一个合适的地址位置。
// 第三个参数shmflg，表示关联共享内存时设置的某些属性。
// shmat函数的返回值说明：

// shmat调用成功，返回共享内存映射到进程地址空间中的起始地址。
// shmat调用失败，返回(void*)-1。
// 其中，作为shmat函数的第三个参数传入的常用的选项有以下三个：

// 选项	作用
// SHM_RDONLY	关联共享内存后只进行读取操作
// SHM_RND	若shmaddr不为NULL，则关联地址自动向下调整为SHMLBA的整数倍。公式：shmaddr-(shmaddr%SHMLBA)
// 0	默认为读写权限
