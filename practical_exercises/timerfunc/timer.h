//
// Created by renbin jiang on 2022/2/27.
//

#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>
#include <iostream>

class timer_ {
public:
    timer_() {}
    timer_(unsigned int h, unsigned int m, unsigned int s) {
        std::cout << "timer_()" << std::endl;
        std::cout << " h:" << h << ",m:" << m << ",s:" << s << std::endl;
    }
    virtual ~timer_() { std::cout << "~timer_()" << std::endl; }

    virtual bool setTimerHour(const unsigned int hours);

    virtual bool setTimerMinute(const unsigned int minutes);

    virtual bool setTimerSecond(const unsigned int secondes);

    virtual unsigned int getTimerHour(void) const;

    virtual unsigned int getTimerMinute(void) const;

    virtual unsigned int getTimerSecond(void) const;

    virtual bool getCurrentTime(unsigned int &hour, unsigned int &minute,
                                unsigned int &second) const;

    virtual bool setTimer(void);

    virtual bool showTimer(void);

    virtual bool showCurrentTime(void);

    static timer_ *get() {
        if (!instance) {
            instance = new timer_();
        }
        return instance;
    }

private:
    static timer_ *instance;
};
#endif // _TIMER_H_
