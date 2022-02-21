//
// Created by light on 20-1-31.
//

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono;
using namespace std;

/**
 * 1.普通函数指针
 * 2.Lambda函数
 * 3.Functors
 * 4.非静态成员函数
 * 5.静态成员函数
 */

using ull = unsigned long long;
ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end) {
    ull i;
    for (i = start; i <= end; ++i) {
        //        std::cout << "findEven i:" << i << std::endl;
    }
    if ((i & 1) == 0) EvenSum += i;
    std::cout << "EvenSum:" << EvenSum << std::endl;
}

void findOdd(ull start, ull end) {
    ull i;
    for (i = start; i <= end; ++i) {
        //        std::cout << "findOdd i:" << i << std::endl;
    }
    if ((i & 1) == 1) OddSum += i;
    std::cout << "OddSum:" << OddSum << std::endl;
}

int main() {
    ull start = 0, end = 19;

    auto startTime = high_resolution_clock::now();
    std::thread t1(findEven, start, end);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::thread t2(findOdd, start, end);
    std::cout << "sleep before" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "sleep after" << std::endl;
    t1.join();
    t2.join();

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "OddSum : " << OddSum << endl;
    cout << "EvenSum: " << EvenSum << endl;
    cout << "Sec: " << duration.count() / 1000000 << endl;
    return 0;
}
