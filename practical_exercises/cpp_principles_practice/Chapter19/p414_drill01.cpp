//
// Created by renbin jiang on 2022/6/4.
//
#include "std_lib_facilities.h"

template<typename T>
struct S {
    T val;
};

int main() {
    
    S<double> sd;
    sd.val = 10.4f;
    cout << "sd.val:" << sd.val << endl;
    S<string> ss;
    ss.val = "robin";
    cout << "ss.val:" << ss.val << endl;
    
    return 0;
}