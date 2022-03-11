//
// Created by renbin jiang on 2021/3/17.
//
//
// 主线程创建单独线程的例子，创建完新的线程后，
// 主线程将打印一些信息并等待新创建的线程退出。
//
#include <iostream>
#include <thread>
#include <pthread.h>

#include "base.h"

using namespace base;

using namespace std;

void thread_func1() {
    for (int i = 0; i < 2; i++) {
        cout << "<--- thread1 runing " << i << " ID:[ "
             << "]--->" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void thread_func2() {
    for (int i = 0; i < 2; i++) {
        cout << "<--- thread2 runing " << i << " ID:[ "
             << "]--->" << endl;
    }
    thread threadObj3(thread_func1);
    cout << "<--- creat threadObj3 -->" << endl;
    threadObj3.detach();
    cout << "<--- detach threadObj3 -->" << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "<--- sleep 1s -->" << endl;
}

int main() {
    thread threadObj1(thread_func1);
    cout << "<--- threadObj1 ID:["
         << "] -->" << endl;
    threadObj1.join();
    thread threadObj2(thread_func2);
    cout << "<--- threadObj2 ID:["
         << "] -->" << endl;

    threadObj2.join();
    // 其中的.join()是用来同步线程的，
    // 该函数会一直阻塞直到thread完成。当然也可以通过detach来将线程执行和线程对象分离开
    for (int i = 0; i < 2; i++) {
        cout << "<--- display main thread ID:["
             << "]-->" << endl;
    }
    cout << "<--- exit of main thread -->" << endl;
    return 0;
}