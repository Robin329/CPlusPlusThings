//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Please enter 3 string values to sort:\n";
    string val1;
    string val2;
    string val3;
    string greatest;
    string middlest;
    string smallest;
    cin >> val1 >> val2 >> val3;

    if (val1 < val2 && val1 < val3) {
        smallest = val1;

        if (val2 < val3) {
            middlest = val2;
            greatest = val3;
        } else {
            middlest = val3;
            greatest = val2;
        }

    } else if (val2 < val3) {
        smallest = val2;

        if (val1 < val3) {
            middlest = val1;
            greatest = val3;
        } else {
            middlest = val3;
            greatest = val1;
        }

    } else {
        smallest = val3;

        if (val1 < val2) {
            middlest = val1;
            greatest = val2;
        } else {
            middlest = val2;
            greatest = val1;
        }
    }

    cout << smallest << " " << middlest << " " << greatest << '\n';
    return 0;
}