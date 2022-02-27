//
// Created by renbin jiang on 2022/2/27.
//

#ifndef CPLUSPLUSTHINGS_ALARM_TIMER_H
#define CPLUSPLUSTHINGS_ALARM_TIMER_H
#include "timer.h"
class alarmTimer : public timer_ {
public:
    alarmTimer()
          : mHours(0), mMinutes(0), mSeconds(0), mCurHours(0), mCurMinutes(0), mCurSeconds(0) {
        std::cout << "alarmTimer()" << std::endl;
    }
    alarmTimer(unsigned int h, unsigned int m, unsigned int s)
          : mHours(0), mMinutes(0), mSeconds(0), mCurHours(0), mCurMinutes(0), mCurSeconds(0) {
        std::cout << "alarmTimer()" << std::endl;
        std::cout << " h:" << h << ",m:" << m << ",s:" << s << std::endl;
    }
    ~alarmTimer() {
        std::cout << "~alarmTimer()" << std::endl;
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    bool setTimerHour(unsigned int hours) {
        if (!hours) {
            std::cout << "hours is zero!!" << std::endl;
            return false;
        }
        mHours = hours;
        return true;
    }

    bool setTimerMinute(unsigned int minutes) {
        if (!minutes) {
            std::cout << "minutes is zero!!" << std::endl;
            return false;
        }
        mMinutes = minutes;
        return true;
    }

    bool setTimerSecond(unsigned int secondes) {
        if (!secondes) {
            std::cout << "secondes is zero!!" << std::endl;
            return false;
        }
        mSeconds = secondes;
        return true;
    }

    bool setTimer();

    unsigned int getTimerHour(void) const { return mHours; }

    unsigned int getTimerMinute(void) const { return mMinutes; }

    unsigned int getTimerSecond(void) const { return mSeconds; }

    bool getCurrentTime(unsigned int &hour, unsigned int &minute, unsigned int &second);

    bool showTimer(void);

    bool showCurrentTime(void);

    static alarmTimer *get(void);

private:
    unsigned int mHours;
    unsigned int mMinutes;
    unsigned int mSeconds;

    unsigned int mCurHours;
    unsigned int mCurMinutes;
    unsigned int mCurSeconds;

    static alarmTimer *m_pInstance;
};

#endif // CPLUSPLUSTHINGS_ALARM_TIMER_H
