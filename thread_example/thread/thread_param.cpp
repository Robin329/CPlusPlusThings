//
// Created by renbin jiang on 2021/3/18.
//

#include <pthread.h>
#include <time.h>

#include <iostream>
#include <thread>

using namespace std;

void thread_func1(const int num) {
    for (int i = 0; i < num; i++) {
        cout << "<--- thread1 runing [" << i << "] ID:[ " << std::this_thread::get_id() << "]--->" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void thread_func2(const char *name) {
    cout << "<--- thread2 runing [" << name << "] ID:[ " << std::this_thread::get_id() << "]--->" << endl;

    thread threadObj3(thread_func1, 5);
    cout << "<--- creat threadObj3 -->" << endl;
    threadObj3.detach();
    cout << "<--- detach threadObj3 -->" << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "<--- sleep 1s -->" << endl;
}

int main() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    printf("[%s:%d] NOW time is %llu\n", __FUNCTION__, __LINE__,
           chrono::seconds(now.tv_sec) + chrono::nanoseconds(now.tv_nsec));
    thread threadObj1(thread_func1, 5);
    cout << "<--- threadObj1 ID:[" << threadObj1.get_id() << "] -->" << endl;
    thread threadObj2(thread_func2, "robin.jiang");
    cout << "<--- threadObj2 ID:[" << threadObj1.get_id() << "] -->" << endl;
    threadObj1.join();
    threadObj2.join();

    for (int i = 0; i < 2; i++) {
        cout << "<--- display main thread ID:[" << this_thread::get_id << "]-->" << endl;
    }
    cout << "<--- exit of main thread -->" << endl;
    return 0;
}