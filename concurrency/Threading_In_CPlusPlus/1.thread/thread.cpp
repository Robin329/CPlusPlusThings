//
// Created by light on 20-1-31.
//

#include <chrono>
#include <iostream>
#include <mutex>
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
std::mutex Mutex;
void findEven(ull start, ull end) {
    //    std::unique_lock<std::mutex> l(Mutex);
    //    ull i;
    //    for (i = start; i <= end; ++i) {
    //        //        std::cout << "findEven i:" << i << std::endl;
    //    }
    //    if ((i & 1) == 0) EvenSum += i;
    //    std::cout << "EvenSum:" << EvenSum << std::endl;

    for (int i = 5; i > 0; --i) {
        std::cout << "findEven sleep :" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    //    std::cout << "findEven sleep :" << 2 << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void findOdd(ull start, ull end) {
    //    std::unique_lock<std::mutex> l(Mutex);
    //    ull i;
    //    for (i = start; i <= end; ++i) {
    //        //        std::cout << "findOdd i:" << i << std::endl;
    //    }
    //    if ((i & 1) == 1) OddSum += i;
    //    std::cout << "OddSum:" << OddSum << std::endl;
    for (int i = 5; i > 0; --i) {
        std::cout << "findOdd sleep :" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    //    std::cout << "findOdd sleep :" << 2 << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    ull start = 0, end = 19;

    auto startTime = high_resolution_clock::now();
    std::thread t1(findEven, start, end);
    //    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::thread t2(findOdd, start, end);
    std::cout << "sleep before" << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "sleep after" << std::endl;
    if (t1.joinable()) {
        t1.join();
    }
    std::cout << "t1.join()" << std::endl;
    if (t2.joinable()) {
        std::cout << "t2 is joinable" << std::endl;
        t2.join();
    }
    std::cout << "t2.join()" << std::endl;
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "OddSum : " << OddSum << endl;
    cout << "EvenSum: " << EvenSum << endl;
    cout << "Sec: " << duration.count() / 1000000 << endl;
    return 0;
}
