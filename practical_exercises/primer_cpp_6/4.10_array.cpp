//
// Created by renbin jiang on 2021/4/28.
//
#include <array>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char **argv) {
    cout << "1.------------------------" << endl;
    vector<int> vi;
    int n;
    n = 1;
    vector<double> vd(n);

    cout << "2.------------------------" << endl;
    array<int, 5> ai;
    array<double, 4> ad = {1.2, 2.1, 3.34, 4.3};
    cout << ad[1] << endl;
}