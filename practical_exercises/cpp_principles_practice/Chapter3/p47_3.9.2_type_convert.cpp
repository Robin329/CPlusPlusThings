//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    double x = 2.7;
    int a = x;
    char c = 0;
    int a1 = 0;
    cout << "a:" << a << endl;
    cout << "Please input:\n";
    while(cin >> x) {
        a = x;
        c = a;
        a1 = c;
        cout << "x == " << x
        << " a == " << a
        << " c == " << c << " , " << std::hex << c << std::oct
        << " a1 == " << a1
        << endl;
    }
    
//    cout << "a:" << a << endl;
    
    return 0;
}