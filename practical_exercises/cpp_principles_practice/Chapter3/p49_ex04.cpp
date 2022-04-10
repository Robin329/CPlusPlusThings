//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Please input 2 numbers:\n";
    int a, b;
    cin >> a >> b;
    cout << "a = " << a << " b = " << b << endl;
    if (a > b)
        cout << " a > b" << endl;
    else if (a < b)
        cout << "a < b" << endl;
    else
        cout << " a = b\n";

    cout << " a + b = " << a + b << endl;
    cout << " a - b = " << a - b << endl;
    cout << " a * b = " << a * b << endl;
    cout << " a / b = " << a / b << endl;
    
    cout << endl;
    cout << "Please input 2 floatint numbers:\n";
    double a1, b1;
    cin >> a1 >> b1;
    cout << "a1 = " << a1 << " b1 = " << b1 << endl;
    if (a1 > b1)
        cout << " a1 > b1" << endl;
    else if (a1 < b1)
        cout << "a1 < b1" << endl;
    else
        cout << " a1 = b1\n";
    
    cout << " a1 + b1 = " << a1 + b1 << endl;
    cout << " a1 - b1 = " << a1 - b1 << endl;
    cout << " a1 * b1 = " << a1 * b1 << endl;
    cout << " a1 / b1 = " << a1 / b1 << endl;
    return 0;
}