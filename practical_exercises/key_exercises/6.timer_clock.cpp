//
// Created by robin on 11/2/21.
//

#include <unistd.h>

#include <chrono>
#include <iostream>

#include "base.h"
// A std::chrono clock based on CLOCK_BOOTTIME.
#include <string>
#include <vector>
using namespace std;
using namespace base;

int main(int argc, char *argv[]) {
    Timer t;
    std::cout << "sleep 1s" << sleep(1) << std::endl;
    vector<int> vec;
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    for (int i = 0; i < vec.size(); i++) {
        cout << "vec:" << vec.data() << endl;
        printf("vec[%d]:%d\n", i, vec[i]);
        vec.erase(vec.begin() + 1);
    }

    auto duration = t.duration();
    std::cout << "c++ duration = " << duration.count() << std::endl;
    printf("duration = %d ms\n", (int)duration.count());

    return 0;
}