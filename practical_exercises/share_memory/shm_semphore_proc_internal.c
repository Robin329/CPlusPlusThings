/*
 * @Author: james.chu
 * @Date: 2022-06-06 11:25:04
 * @LastEditors: james.chu
 * @LastEditTime: 2022-06-09 16:22:19
 * @FilePath: \undefinedx:\c_plus_plus\test_sham_semaphore.cpp
 * @Description:
 *
 * Copyright (c) 2022 by james.chu, All Rights Reserved.
 */
#include "shm_comm.h"
#define PATHNAME \
    "/home/ubuntu/workspace/CPlusPlusThings/practical_exercises/share_memory/shmfile" //路径名
#define FTOK_PARA_ID_VALUE (10)
#define SHEGET_PARA_SIZE (4096)
#define SHEGET_PARA_SHMFLAG_FILE_AUTHORRITY (0666)
#define SHEAT_PARA_SHMFLAG_WR_MODE 0
#define RUN_TIME (30u)
#define DELAY_TIME_LEVELS (5.0)

#define TIMESTAMP()                                \
    do {                                           \
        memset(&cur_time, 0x00, sizeof(cur_time)); \
        time(&cur_time);                           \
        printf("%s", ctime(&cur_time));            \
    } while (0)

time_t end_time, cur_time;
sem_t sem_W; // W信号量
sem_t sem_R; // R信号量

//负责写入数据到共享内存中
void *sham_write(void *arg) {
    int delay_time = 0;
    int *p_she = (int *)arg;

    while (time(NULL) < end_time) {
        delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX) / 2.0) + 1;
        TIMESTAMP();
        printf("%s will delay_time:%d\n", __func__, delay_time);
        sleep(delay_time);
        TIMESTAMP();
        printf("%s delay_time is ending\n", __func__);

        // 尝试产生数据
        sem_wait(&sem_W);
        printf("%s ---- write is start ---\n", __func__);
        memcpy(p_she, &delay_time, sizeof(int));
        printf("%s p_she:%p -> %d\n", __func__, p_she, *p_she);
        TIMESTAMP();
        printf("%s ---- write is ending ---\n", __func__);
        // 唤醒消费线程
        sem_post(&sem_R);
    }

    pthread_exit(NULL);
}

//负责从共享内存中读取数据
void *sham_read(void *arg) {
    int *p_she = (int *)arg;
    int delay_time = 0;

    while (time(NULL) < end_time) {
        delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX)) + 1;
        TIMESTAMP();
        printf("%s will delay_time:%d\n", __func__, delay_time);
        sleep(delay_time);
        TIMESTAMP();
        printf("%s delay_time is ending\n", __func__);

        // 尝试消费数据
        sem_wait(&sem_R);

        // TIMESTAMP();
        printf("%s ---- read is start ----\n", __func__);
        printf("%s p_she:%p -> %d\n", __func__, p_she, *p_she);
        memset(p_she, 0x00, SHEGET_PARA_SIZE);
        TIMESTAMP();
        printf("%s ---- read is ending ----\n", __func__);
        // 唤醒生产者线程
        sem_post(&sem_W);
    }

    pthread_exit(NULL);
}

int main() {
    key_t key = IPC_PRIVATE;
    int shmid;
    void *p_shm;
    /**
     * @description:系统建立IPC通讯 （消息队列、信号量和共享内存）
     *时必须指定一个ID值。通常情况下，该id值通过ftok函数得到
     * @param {char *} fname
     *fname就是你指定的文件名（已经存在的文件名），一般使用当前目录，如：key =
     *ftok(".", 1); 这样就是将fname设为当前目录
     * @param {int} id id是子序号。虽然是int类型，但是只使用8bits(1-255)
     * @return {*}
     *key_t ftok( const char * fname, int id )
     */
    // 1. 申请共享内存的key值
    // 2. 单进程内不需要重新生成key
    // key = ftok(PATHNAME, FTOK_PARA_ID_VALUE);

    /**
     * @description:得到一个共享内存标识符或创建一个共享内存对象并返回共享内存标识符
     * @param {key_t} key 0(IPC_PRIVATE)：会建立新共享内存对象 |
     * 大于0的32位整数：视参数shmflg来确定操作。通常要求此值来源于ftok返回的IPC键值
     * @param {size_t} size 大于0的整数：新建的共享内存大小，以字节为单位 |
     * 0：只获取共享内存时指定为0
     * @param {int} shmflg 0：取共享内存标识符，若不存在则函数会报错 |
     * IPC_CREAT：当shmflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的共享内
     * 存，则新建一个共享内存；如果存在这样的共享内存，返回此共享内存的标识符 |
     * IPC_CREAT|IPC_EXCL：如果内核中不存在键值
     * 与key相等的共享内存，则新建一个共享内存；如果存在这样的共享内存则报错
     * @return {*} 成功：返回共享内存的标识符 |出错：-1，错误原因存于errno中
     * @note:在Linux环境中，对开始申请的共享内存空间进行了初始化，初始值为0x00，对于参数shmflg一般还会或上一个文件权限
     * int shmget(key_t key, size_t size, int shmflg)
     */
    // 2. 申请共享内存ID
    shmid = shmget(key, SHEGET_PARA_SIZE,
                   IPC_CREAT | IPC_EXCL | SHEGET_PARA_SHMFLAG_FILE_AUTHORRITY);

    /**
     * @description:连接共享内存标识符为shmid的共享内存，连接成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问
     * @param {int} shmid 共享内存标识符
     * @param {void} *shmaddr
     * 指定共享内存出现在进程内存地址的什么位置，直接指定为NULL让内核自己决定一个合适的地址位置
     * @param {int} shmflg SHM_RDONLY：为只读模式，其他为读写模式
     * @return {*} 成功：附加好的共享内存地址 | 出错：-1，错误原因存于errno中
     * @note:fork后子进程继承已连接的共享内存地址。exec后该子进程与已连接的共享内存地址自动脱离(detach)。进程结束后，已连接的共享内存地址会自动脱离(detach)
     * void *shmat(int shmid, const void *shmaddr, int shmflg)
     */
    // 3.映射一片内存空间，NULL代表系统分配空间
    printf("p_shm:%p key:%d\n", p_shm, key);
    p_shm = shmat(shmid, NULL, SHEAT_PARA_SHMFLAG_WR_MODE);
    printf("p_shm:%p key:%d\n", p_shm, key);

    if (p_shm) {
        memset(&cur_time, 0x00, sizeof(cur_time));
        memset(&end_time, 0x00, sizeof(end_time));
        srand(time(NULL));
        end_time = time(NULL) + RUN_TIME;

        // 4.初始化信号量
        memset(&sem_W, 0x00, sizeof(sem_t));
        memset(&sem_R, 0x00, sizeof(sem_t));
        /**
         * @description:初始化一个定位在 sem 的匿名信号量
         * @param {sem_t} *sem
         * @param {int} pshared
         * 指明信号量是由进程内线程共享，还是由进程之间共享。如果值为0，那么信号量将被进程内的线程共享，并且应该放置在这个进程的所有线程都可见的地址上(如全局变量，或者堆上动态分配的变量)
         * @param {unsigned int} value 参数指定信号量的初始值
         * @return {*}
         * int sem_init(sem_t *sem, int pshared, unsigned int value);
         */
        int sem_ret = sem_init(&sem_W, 0, 1);
        sem_ret += sem_init(&sem_R, 0, 0);
        if (sem_ret != 0) {
            printf("W:semaphore init is failed ##########\n");
            return -1;
        }

        // 5.主线程产生两个子线程，两个子线程都是随机执行
        pthread_t W_pthread_id, R_pthread_id;
        memset(&W_pthread_id, 0x00, sizeof(pthread_t));
        memset(&R_pthread_id, 0x00, sizeof(pthread_t));
        pthread_attr_t sham_read_pthread_attribute, sham_write_pthread_attribute;
        memset(&sham_read_pthread_attribute, 0x00, sizeof(pthread_attr_t));
        memset(&sham_write_pthread_attribute, 0x00, sizeof(pthread_attr_t));

        pthread_attr_init(&sham_read_pthread_attribute);
        pthread_attr_setdetachstate(&sham_read_pthread_attribute, PTHREAD_CREATE_JOINABLE);
        int W_creat_ret = pthread_create(&W_pthread_id, &sham_read_pthread_attribute, sham_write,
                                         (void *)p_shm);
        if (W_creat_ret != 0) {
            printf("W:pthread_create is failed ##########\n");
            return -1;
        }
        pthread_attr_destroy(&sham_read_pthread_attribute);

        pthread_attr_init(&sham_read_pthread_attribute);
        pthread_attr_setdetachstate(&sham_read_pthread_attribute, PTHREAD_CREATE_JOINABLE);
        int R_creat_ret = pthread_create(&R_pthread_id, &sham_read_pthread_attribute, sham_read,
                                         (void *)p_shm);
        if (R_creat_ret != 0) {
            printf("W:pthread_create is failed ##########\n");
            return -1;
        }
        pthread_attr_destroy(&sham_read_pthread_attribute);

        pthread_join(W_pthread_id, NULL);
        pthread_join(R_pthread_id, NULL);
        shmdt(p_shm);
        shmctl(shmid, IPC_RMID, NULL);
        return 0;
    } else {
        printf("p_shm is nullptr\n");
        return -1;
    }
}
