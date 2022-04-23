#include <iostream>
#include "base.h"
using namespace std;
using namespace base;
void fun(int x) {
    try {
        if (x == 0) throw "abnormal";
    } catch (...) {
        cout << "in fun" << endl;
        throw 1;
    }
}

int main(int argc, char const *argv[]) {
    try {
        fun(0);
    } catch (int n) {
        cout << "in main" << endl;
    }
    point p[9][9];
    cout << "point sizeof:" << sizeof (point) << endl;
    cout << "p sizeof:" << sizeof p << endl;
    return 0;
}
