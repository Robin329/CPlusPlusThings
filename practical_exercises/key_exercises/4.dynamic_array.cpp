#include <gtest/gtest.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "base.h"
using namespace base;
class Timer1 {
public:
#define MILLION 1000000

    Timer1(std::string tag) {
        std::cout << "Timer()" << std::endl;

        m_tag = tag;

        if (m_tag.empty()) {
            m_tag = "GL";
        }

        clock_gettime(CLOCK_MONOTONIC, &tpStart);
    }

    ~Timer1() {
        std::cout << "~Timer()" << std::endl;

        clock_gettime(CLOCK_MONOTONIC, &tpEnd);

        timeCost = MILLION * (tpEnd.tv_sec - tpStart.tv_sec) +
                (tpEnd.tv_nsec - tpStart.tv_nsec) / 1000;

        std::cout << "[" << m_tag << "] cost: " << timeCost << " mS" << std::endl;

        m_tag = "";
    }

private:
    struct timespec tpStart;

    struct timespec tpEnd;

    float timeCost;

    std::string m_tag;
};

struct timespec tpStart1;

struct timespec tpEnd1;

float timeCost1;

bool demo(void) {
    Timer1 t("aaa");
    std::cout << "demo" << std::endl;
    clock_gettime(CLOCK_MONOTONIC, &tpStart1);
    for (int i; i < 1000000; i++) {
        //        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // sleep(1);
        //        std::cout << "enter demo delay func" <<std::endl;
    }
    clock_gettime(CLOCK_MONOTONIC, &tpEnd1);
    timeCost1 = MILLION * (tpEnd1.tv_sec - tpStart1.tv_sec) +
            (tpEnd1.tv_nsec - tpStart1.tv_nsec) / 1000;

    std::cout << "["
              << "] cost: " << timeCost1 << " mS" << std::endl;
    if (tpEnd1.tv_sec > tpStart1.tv_sec) {
        return true;
    }
    return false;
}

TEST(DemoTest, Bool) {
    EXPECT_EQ(false, demo());
    //    EXPECT_TRUE(demo());
    EXPECT_FALSE(demo());
}

#if 1

int main() {
    int ret = RUN_ALL_TESTS();
    cout << "ret = " << ret << endl;
    coor coo[5][3];
    point point_t[2][2];
    point point9[3][3];
    memset(&coo[0][0], 0, sizeof coo);
    memset(point_t, 0, sizeof point_t);
    memset(point9, 0, sizeof point9);
    dbgLevel = 1;
    //    COOR_T_LOG("coo", coo, 5, 3);
    POINT_LOG("point_t", point_t, 2, 2);
    POINT_LOG("point9", point9, 3, 3);
#if 0
    char *sPtr;
    const char *s = "hello";
    sPtr = new char[strlen(s) + 1];
    strncpy(sPtr, s, strlen(s));
    std::cout << "str len s is " << strlen(s) << std::endl;
    std::cout << "str len sPtr is " << strlen(sPtr) << std::endl;
    std::cout << sPtr << std::endl;
    delete sPtr;
    return 0;
#endif
}

#endif