//
// Created by renbin jiang on 2022/4/12.
//
#include "std_lib_facilities.h"

int square1(int v) {
    if (v < 0) return 0;
    int total = 0;
    for (int i = 0;i < v;++i) {
        total += v;
    }
    return total;
}

int main() {
    for (int i = 0;i < 100;++i) {
        cout << i << "^2 = " << square1(i) << endl;
    }
    return 0;
}
