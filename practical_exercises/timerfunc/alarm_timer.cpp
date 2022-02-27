//
// Created by renbin jiang on 2022/2/27.
//

#include "alarm_timer.h"

#include <sys/time.h>
#include <time.h>

#include <chrono>
#include <iostream>

alarmTimer *alarmTimer::m_pInstance = nullptr;

bool alarmTimer::getCurrentTime(unsigned int &hour, unsigned int &minute, unsigned int &second) {
#if 0
    hour = std::chrono::duration_cast<std::chrono::hours>(
                   std::chrono::system_clock::now().time_since_epoch())
                   .count();
    minute = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count();
    second = std::chrono::duration_cast<std::chrono::seconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count();
#else
    time_t now = time(0);
    tm *localTm = localtime(&now);
    hour = localTm->tm_hour;
    minute = localTm->tm_min;
    second = localTm->tm_sec;
#endif
    mCurHours = hour;
    mCurMinutes = minute;
    mCurSeconds = second;
    std::cout << "get current time : hour = " << hour << ", minute = " << minute
              << ", second = " << second << std::endl;
    return true;
}

bool alarmTimer::showTimer(void) {
    std::cout << " hour:   " << mHours << std::endl;
    std::cout << " minute: " << mMinutes << std::endl;
    std::cout << " second: " << mSeconds << std::endl;
    return true;
}

bool alarmTimer::showCurrentTime() {
#if 0
    std::cout << "hour:"
              << std::chrono::duration_cast<std::chrono::hours>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count()
              << std::endl;
    std::cout << "minute:"
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count()
              << std::endl;
    std::cout << "second:"
              << std::chrono::duration_cast<std::chrono::seconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count()
              << std::endl;
    std::cout << "msecond:"
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count()
              << std::endl;
#else
    time_t now = time(0);
    // convert now to tm struct
    tm *localTm = localtime(&now);
    struct timeval time;
    gettimeofday(&time, NULL);
    std::cout << "The local date and time is: \n" << asctime(localTm) << std::endl;
    std::cout << "Cur time is: \n" << ctime(&now) << std::endl;
    std::cout << "Years:  " << 1900 + localTm->tm_year << std::endl;
    std::cout << "Mon:    " << 1 + localTm->tm_mon << std::endl;
    std::cout << "Day:    " << localTm->tm_mday << std::endl;
    std::cout << "Hours:  " << localTm->tm_hour << std::endl;
    std::cout << "Minute: " << localTm->tm_min << std::endl;
    std::cout << "Second: " << localTm->tm_sec << std::endl;
    std::cout << "Msecond:"
              << static_cast<long long>(time.tv_sec * 1000) +
                    static_cast<long long>(time.tv_usec / 1000)
              << std::endl;
    std::cout << "Usecond:"
              << static_cast<long long>(time.tv_sec * 1000) +
                    static_cast<long long>(time.tv_usec / 1000) +
                    static_cast<long long>(time.tv_sec * 1000) +
                    static_cast<long long>(time.tv_usec)
              << std::endl;

//    tm *gmtm = gmtime(&now);
//    std::cout << "The UTC and time is: \n" << asctime(gmtm) << std::endl;
#endif
    return true;
}

bool alarmTimer::setTimer() {
    if (mHours == 0 && mMinutes == 0 && mSeconds == 0) {
        std::cout << "alarm timer is not set!!!" << std::endl;
        printf("h:%d m:%d s:%d\n", mHours, mMinutes, mSeconds);
        return false;
    }
#if 0
    time_t now = time(0);
    // convert now to tm struct
    tm *localTm = localtime(&now);
    if (mHours && localTm->tm_hour != (mHours + mCurHours)) {
        std::cout << "local hour:" << localTm->tm_hour << std::endl;
    }
    if (mMinutes && localTm->tm_min != (mMinutes + mCurMinutes)) {
        std::cout << "local min:" << localTm->tm_min << std::endl;
    }
    if (localTm->tm_sec == (mSeconds + mCurSeconds) && (localTm->tm_hour != (mHours + mCurHours)) &&
        (localTm->tm_min != (mMinutes + mCurMinutes))) {
        std::cout << "---------------------------" << std::endl;
        std::cout << "-------alarm is reach------" << std::endl;
        std::cout << "---------------------------" << std::endl;
        return true;
    } else {
        std::cout << "local sec:" << localTm->tm_sec << std::endl;
    }
#else
    long long second = std::chrono::duration_cast<std::chrono::seconds>(
                               std::chrono::system_clock::now().time_since_epoch())
                               .count();
    std::cout << "second:" << second << std::endl;

    static bool update = true;
    static long long alarmSecond = 0;
    if (update) {
        alarmSecond = second;
        if (mSeconds) {
            alarmSecond += mSeconds;
        }
        if (mMinutes) {
            alarmSecond += (mMinutes * 60);
        }
        if (mHours) {
            alarmSecond += (mHours * 3600);
        }
        update = false;
        std::cout << "alarmSecond:" << alarmSecond << std::endl;
    }
    //    std::cout << "alarmSecond:" << alarmSecond << std::endl;
    if (second == alarmSecond) {
        std::cout << "---------------------------" << std::endl;
        std::cout << "-----alarm is reached------" << std::endl;
        std::cout << "---------------------------" << std::endl;
    } else {
        return false;
    }
#endif
    return true;
}
alarmTimer *alarmTimer::get(void) {
    if (m_pInstance == nullptr) {
        m_pInstance = new alarmTimer();
    }
    return m_pInstance;
}