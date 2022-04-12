//
// Created by renbin jiang on 2022/4/12.
//
#include "std_lib_facilities.h"
#define MIN(x, y) ((x) > (y) ? (y) : (x))

int main() {
    vector<double> x, y;
    double a, b;
    while (cin >> a >> b) {
        x.push_back(a);
        y.push_back(b);
        cout << "x:" << a << " y:" << b << " min:" << MIN(a, b) << endl;
        cout << "the smaller value is : " << (a > b ? b : a) << endl;

        cout << "the larger value is : " << (a > b ? a : b) << endl;
        if (a == b) {
            cout << "the numbers is equal" << endl;
        }

        if (((b >= a) ? (b - a) : (a - b)) < (1.0 / 100))
            cout << "the numbers are almost equal" << endl;
    }

    return 0;
}