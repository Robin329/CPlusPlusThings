#include "shm_comm.h"


int main() {
    key_t key = ftok(PATHNAME, PROJ_ID); //获取key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
    int shm = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666); //创建新的共享内存
    if (shm < 0) {
        perror("shmget exists!!");
        shmctl(3, IPC_RMID, NULL); //释放共享内存
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

    printf("detach begin!\n");
    sleep(2);
    shmdt(mem); //共享内存去关联
    printf("detach end!\n");
    sleep(2);

    shmctl(shm, IPC_RMID, NULL); //释放共享内存
    return 0;
}
