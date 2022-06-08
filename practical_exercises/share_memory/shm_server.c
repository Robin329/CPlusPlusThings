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
    printf("shm: %d\n", shm); //打印共享内存用户层id

    char* mem = shmat(shm, NULL, 0); //关联共享内存

    while (1) {
        //不进行操作
        printf("client# %s\n", mem);
        sleep(1);
    }

    shmdt(mem); //共享内存去关联

    shmctl(shm, IPC_RMID, NULL); //释放共享内存
    return 0;
}
