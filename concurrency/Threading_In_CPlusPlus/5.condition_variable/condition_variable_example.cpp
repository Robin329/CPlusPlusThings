//
// Created by renbin jiang on 2022/2/22.
//
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

bool moreDataToPrepare() {
    return true;
}

struct dataChunk {
    int a;
    float b;
    char c;
};

dataChunk &prepareData() {
    dataChunk *data = (dataChunk *)malloc(sizeof(dataChunk));
    data->a = 1;
    data->b = 2.0;
    data->c = 3;
    return *data;
}

void process(dataChunk &data) {
    std::cout << "dataChunk:" << std::endl;
    std::cout << "        a:" << data.a << std::endl;
    std::cout << "        b:" << data.b << std::endl;
    std::cout << "        c:" << data.c << std::endl;
}

bool isLastChunk(dataChunk &data) {
    return true;
}

std::mutex Mutex;
std::queue<dataChunk> dataQueue;
std::condition_variable dataCond;

void dataPreparetionThread() {
    while (moreDataToPrepare()) {
        dataChunk const data = prepareData();
        std::lock_guard<std::mutex> l(Mutex);
        dataQueue.push(data);
        dataCond.notify_one();
    }
}

void dataProcessingThread() {
    while (true) {
        std::unique_lock<std::mutex> l(Mutex);
        dataCond.wait(l, [] { return !dataQueue.empty(); });
        dataChunk data = dataQueue.front();
        process(data);
        dataQueue.pop();
        l.unlock();
        process(data);
        if (isLastChunk(data)) {
            std::cout << "is last chunk" << std::endl;
            break;
        }
    }
}
// 1. 生产者线程data_preparation_thread循环进行消息的准备，在37行往队列中插入一条记录后，
// 通过38行的std::condition_variable实例唤醒一个等待线程。
//
// 2. 消费者线程data_processing_thread在47行检查通过std::condition_variable.wait中的
// lambda表达式检查队列是否为空，如果队列为空，wait()函数将解锁互斥量,并且将这个线程(上段提到的
// 处理数据的线程)置于阻塞或等待状态。直到生产者线程data_preparation_thread有数据push到队列
// 中后，通过std::condition_variable.notify_one()在38行进行通知唤醒。一旦被唤醒，消费者线
// 程会再次获取互斥锁,并且对条件再次检查,并在条件满足的情况下,继续持有锁，并48行和以下部分的代码。
//
// 3. std::condition_variable.wait等待条件满足是直接与等待条件相关的，而与通知到达无关，
// 通知到达了，只是唤醒等待线程重新锁定共享数据，检查条件满足没有。wait的第一个参数为对共享数
// 据进行保护的锁，只有在锁定状态下，wait才会去检查wait条件是否达成。

int main() {
    std::thread t1(dataPreparetionThread);
    std::thread t2(dataProcessingThread);

    t1.join();
    t2.join();

    return 0;
}