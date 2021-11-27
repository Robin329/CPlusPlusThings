//
// Created by renbin jiang on 2021/3/28.
//

#ifndef CPLUSPLUSTHINGS_MUTEX_DEMO_H
#define CPLUSPLUSTHINGS_MUTEX_DEMO_H
#include <iostream>
#include <mutex>
#include <thread>

#define ROBIN_AUTOLOCK(p) \
    Autolock lock(p);     \
    printf("[Tid:%d][%s:%d]\n", getpid(), __FUNCTION__, __LINE__);

static pthread_mutex_t *m_pMutexTwo;

class Autolock {
public:
    inline Autolock(pthread_mutex_t *mutex) {
        m_pMutex = mutex;
        pthread_mutex_lock(m_pMutex);
    }

    inline ~Autolock() { pthread_mutex_unlock(m_pMutex); }

private:
    pthread_mutex_t *m_pMutex;
    pthread_mutex_t *m_pMutexOne;
};

#endif // CPLUSPLUSTHINGS_MUTEX_DEMO_H
