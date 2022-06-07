
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <pthread.h>
#include <condition_variable>

using namespace std;

bool isDispResumeEnd = false;
std::mutex mtx;
pthread_t disp_thread_id;
condition_variable dispCon;

void *XlabResumeThread(void *arg) {
    printf("FocusResume:Thread Start\n");
    for (int i{}; i < 5;++i) {
        // cout << __FUNCTION__ << ":" << __LINE__ << " i -> " << i << endl;
        printf("%s[%d] i:%d\n", __FUNCTION__, __LINE__, i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    printf("FocusResume:Thread end\n");
    pthread_exit(NULL);
    return NULL;
}

void *AudioResumeThread(void *arg) {
    printf("AudioResume:Thread Start\n");
    for (int i{}; i < 8; ++i) {
        // cout << __FUNCTION__ << ":" << __LINE__ << " i -> " << i << endl;
        printf("%s[%d] i:%d\n", __FUNCTION__, __LINE__, i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    printf("AudioResume:Thread end\n");
    pthread_exit(NULL);
    return NULL;
}

void DisplayResume(void) {
    printf("%s:%d Enter\n", __FUNCTION__, __LINE__);
    for (int i{}; i < 5; ++i) {
        // cout << __FUNCTION__ << ":" << __LINE__ << " i -> " << i << endl;
        printf("%s[%d] i:%d\n", __FUNCTION__, __LINE__, i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    printf("%s:%d End\n", __FUNCTION__, __LINE__);
}

void *DisplayResumeThread(void *arg) {
    printf("DisplayResume:Thread Start\n");
    isDispResumeEnd = false;
    DisplayResume();
    isDispResumeEnd = true;
    printf("DisplayResume:Thread end\n");
    pthread_exit(NULL);
    return NULL;
}

void CreateDisplayResumeThread(void) {
    int status;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    int ret = pthread_create(&disp_thread_id, &thread_attr, DisplayResumeThread, NULL);
    if (ret) {
        printf("Create DisplayResumeThread  failed ret = %d\n", ret);
    }
    // status = pthread_join(thread_id, NULL);
    // if (status) {
    //     printf("Create DisplayResumeThread join FAILED(%d)!\n", status);
    // }
    pthread_attr_destroy(&thread_attr);
}

void CreateXlabResumeThread(void) {
    pthread_t thread_id;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    int ret = pthread_create(&thread_id, &thread_attr, XlabResumeThread, NULL);
    if (ret) {
        printf("Create FocusResumeThread  failed ret = %d\n", ret);
    }
    pthread_attr_destroy(&thread_attr);
}

void CreateAudioResumeThread(void) {
    pthread_t thread_id;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    int ret = pthread_create(&thread_id, &thread_attr, AudioResumeThread, NULL);
    if (ret) {
        printf("Create AudioResumeThread  failed ret = %d\n", ret);
    }
    pthread_attr_destroy(&thread_attr);
}

int main() {
    CreateDisplayResumeThread();
    CreateXlabResumeThread();
    CreateAudioResumeThread();

    int timeCount = 0;
    while (timeCount < 10) {
        // std::unique_lock<std::mutex> dispMutex(mtx);
        if (isDispResumeEnd) {
            printf("------------ isDispResumeEnd is true ----------------\n");
            break;
        }
        timeCount++;
         printf("-->> %d\n", timeCount);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    printf("main END\n");
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}
