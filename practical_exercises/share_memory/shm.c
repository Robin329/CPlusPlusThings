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
    return 0;
}

// # ipcs
// ------ Message Queues --------
// key        msqid      owner      perms      used-bytes   messages

// ------ Shared Memory Segments --------
// key        shmid      owner      perms      bytes      nattch     status
// 0x66019101 0          ubuntu     0          4096       0

// ------ Semaphore Arrays --------
// key        semid      owner      perms      nsems

// -q：列出消息队列相关信息。
// -m：列出共享内存相关信息。
// -s：列出信号量相关信息。

/* Get shared memory segment.  */
//extern int shmget(key_t __key, size_t __size, int __shmflg)
// key	系统区别各个共享内存的唯一标识
// shmid	共享内存的用户层id（句柄）
// owner	共享内存的拥有者
// perms	共享内存的权限
// bytes	共享内存的大小
// nattch	关联共享内存的进程数
// status	共享内存的状态

// # release share memory
// ipcrm -m shmid