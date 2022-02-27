//
// Created by renbin jiang on 2022/2/27.
//
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "alarm_timer.h"
alarmTimer *alarm = nullptr;

int addMinus(char *ch, unsigned int &num) {
    if (!ch || num < 0) {
        std::cout << "[" << __func__ << "] ch is NULL or num is zero!!!" << std::endl;
        return -1;
    }
    switch (*ch) {
        case 'w':
            num += 1;
            break;
        case 's':
            if (!num) return -1;
            num -= 1;
            break;
        default:
            std::cout << "ch is illegal!!!!" << std::endl;
            break;
    }
    return 0;
}

int inputHandle(char *ch) {
    if (!ch) {
        std::cout << "[" << __func__ << "] ch is NULL!!!" << std::endl;
        return -1;
    }
    unsigned int h, m, s;
    unsigned int ws;
    switch (*ch) {
        case 'h': {
            alarm->getCurrentTime(h, m, s);
            std::cout << "cur hours:" << h << std::endl;
            std::cout << "please input hours:";
            std::cin >> ws;
            std::cout << "set hours:" << ws << std::endl;
            alarm->setTimerHour(ws);
            break;
        } break;
        case 'm': {
            alarm->getCurrentTime(h, m, s);
            std::cout << "cur minute:" << m << std::endl;
            std::cout << "please input minute:";
            std::cin >> ws;
            std::cout << "set minute:" << ws << std::endl;
            alarm->setTimerMinute(ws);
            break;
        } break;
        case 's': {
            alarm->getCurrentTime(h, m, s);
            std::cout << "cur second:" << s << std::endl;
            std::cout << "please input second:";
            std::cin >> ws;
            std::cout << "set second:" << ws << std::endl;
            alarm->setTimerSecond(ws);
            break;
        } break;

        default:
            break;
    }
    return 0;
}

void timerThread() {
    while (true) {
        if (alarm->setTimer()) break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void help() {
    std::cout << "\n---------------------\n"
              << "input 'q' : exit\n"
              << "input 'h' : hours\n"
              << "input 'm' : minute\n"
              << "input 's' : seconds\n"
              << "---------------------\n"
              << std::endl;
}

int main() {
    alarm = alarmTimer::get();
    alarm->showCurrentTime();
    help();
    char ch;
    // Ctrl + z end
    while (true) {
        std::cout << "input:";
        std::cin >> ch;
        std::cout << "ch = " << ch << std::endl;

        if (inputHandle(&ch)) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (ch && !strcmp(&ch, "q")) break;
    }
    std::thread timerFunc(timerThread);
    if (timerFunc.joinable()) {
        timerFunc.join();
    }
    return 0;
}