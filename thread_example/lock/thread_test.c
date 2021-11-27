//
// Created by renbin jiang on 2021/4/2.
//

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static void *func1(void *arg);
static void *func2(void *arg);

void *func1(void *arg) {
    static bool threadlock = false;
    printf("-- func1 thread --\n");
    //    if(threadlock) {
    //        printf("threadlock is true\n");
    //        return NULL;
    //    }

    threadlock = true;
    printf("++ thread start ++\n");
    func2(NULL);
    printf("-- thread start --\n");
    threadlock = false;
    pthread_exit(NULL);
    return NULL;
}

void *func2(void *arg) {
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();

    for (int i = 0; i < 5; i++) {
        printf("[%s:%d] i is [%d]\n", __FUNCTION__, __LINE__, i);
    }
    //   while(true) {
    //       sleep(1);
    //       printf("[%s:%d] pid %u tid %u (0x%x)\n", __FUNCTION__, __LINE__, (unsigned int)pid,
    //                (unsigned int)tid, (unsigned int)tid); /* tid是unsigned long int,这里只是方便转换 */
    //   }
    return NULL;
}
int main(int argc, char **argv) {
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    pthread_t thread_id;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    printf("[%s:%d] pthread START\n", __FUNCTION__, __LINE__);
    int ret = pthread_create(&thread_id, &thread_attr, func1, NULL);
    if (ret) {
        printf("creat thread FAILED\n");
        assert(0);
    }
    pthread_attr_destroy(&thread_attr);
    printf("[%s:%d] pid %u tid %u (0x%x)\n", __FUNCTION__, __LINE__, (unsigned int)pid, (unsigned int)tid,
           (unsigned int)tid); /* tid是unsigned long int,这里只是方便转换 */
    printf("[%s:%d] pthread END\n", __FUNCTION__, __LINE__);
    return 0;
}