//
// Created by renbin jiang on 2022/5/8.
//
#include "iostream"
#include <vector>
#define DETECTION(a)                                                                        \
    do {                                                                                    \
        typeof(a) x_ = 1.1;                                                                 \
        (x_ - (int)x_) ? std::cout << a << " is float.\n" : std::cout << a << " is int.\n"; \
    } while (0)

int main() {
    int a = 100;
    float b = 1.0;
    DETECTION(a);
    DETECTION(b);
    DETECTION(1.0);
    DETECTION(1);
    std::vector<int> vec;
    for (int i = 0; i <= 4611686018427387903;i++) {
        vec.push_back(i);
//        std::cout << "i:" << i << " ";
    }
    std::cout << "capacity : " <<  vec.capacity() << std::endl;
    std::cout << "max size : " <<  vec.max_size() << std::endl;
    return 0;
}