//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Enter a measurement in miles to convert to kilometers:\n";
    double miles;
    cin >> miles;
    double kilometers = miles * 1.609;
    cout << "There are " << kilometers
         << " kilometers in " << miles
         << " miles.\n";
    return 0;
}