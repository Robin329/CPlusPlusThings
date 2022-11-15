#include <bits/stdint-uintn.h>
#include <gtest/gtest.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "base.h"
using namespace base;

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
#if 0
TEST(DemoTest, Bool) {
    EXPECT_EQ(false, demo());
    //    EXPECT_TRUE(demo());
    EXPECT_FALSE(demo());
}
#endif
#if 1
int max_robin(int b1total, int b1rem, int b2total, int b2rem) {
    if ((b1total) > (b2total)) {
        return ((b1rem) ? ((b1total) + 1) : (b1total));
    } else if ((b1total) == (b2total)) {
        return ((b1rem) ? ((b1total) + 1) : ((b2rem) ? (b2total + 1) : (b2total)));
    } else if ((b1total) < (b2total)) {
        return (b2rem ? b2total + 1 : b2total);
    }
    return 0;
}

int main() {
    Timer1 t("main");
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
    int b1t = 0;
    int b1r = 1;
    int b2t = 1;
    int b2r = 0;
    int ret1 = max_robin(b1t, b1r, b2t, b2r);
    cout << "return:" << ret1;
    uint32_t arrary[] = {0x00000012, 0x00000023, 0x00000034, 0x00000033};
    printf("sizeof (arrary) =%d \n", sizeof(arrary));
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