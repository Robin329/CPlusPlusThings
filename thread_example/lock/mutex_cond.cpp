#include <pthread.h>
#include <unistd.h>

#include <chrono>
#include <iostream>

using namespace std;
int c = 0;
pthread_mutex_t m_mutex;
pthread_cond_t cond;

void *Thread(void *arg) {
    int i = 0;
    cout << "Thread start c:" << c << endl;

    while (true) {
        usleep(1000 * 1000);
        cout << "waiting ..." << endl;
        pthread_mutex_lock(&m_mutex);

        pthread_cond_wait(&cond, &m_mutex);
        cout << "i:" << i++ << endl;

        pthread_mutex_unlock(&m_mutex);
        cout << "Thread end c:" << c << endl;
    }
    return nullptr;
}

void func(void) {
    pthread_mutex_lock(&m_mutex);
    c += 1;
    cout << "before cond signal" << endl;
    cout << "after cond signal" << endl;
    usleep(2000 * 1000);
    pthread_mutex_unlock(&m_mutex);
    cout << "func end c:" << c << endl;
}

int main() {
    pthread_mutex_init(&m_mutex, nullptr);
    pthread_cond_init(&cond, NULL);
    pthread_t syncThreadId;
    pthread_attr_t syncThreadAttr;
    pthread_attr_init(&syncThreadAttr);
    pthread_attr_setdetachstate(&syncThreadAttr, PTHREAD_CREATE_JOINABLE);
    int ret = pthread_create(&syncThreadId, &syncThreadAttr, &Thread, nullptr);
    if (ret) {
        printf("Create syncEventThread failed ret = %d\n", ret);
    }
    func();
    int m = 0;
    while (true) {
        m++;
        usleep(1000 * 1000);
        if (m % 2) {
            cout << "m : " << m << endl;
            pthread_cond_signal(&cond);
        }
    }
    pthread_attr_destroy(&syncThreadAttr);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&m_mutex);
}
