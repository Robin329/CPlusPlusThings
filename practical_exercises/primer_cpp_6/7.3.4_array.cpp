//
// Created by renbin jiang on 2021/5/25.
//
#include <iostream>

using namespace std;

int sum_arr(const int *begin, const int *end) {
    const int *pt = nullptr;
    int total = 0;

    for (pt = begin; pt != end; pt++) {
        total = total + *pt;
    }
    return total;
}

int main(int argc, const char *argv[]) {
    const int ArSize = 8;

    int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};

    int sum = sum_arr(cookies, cookies + ArSize);
    cout << "Total: " << sum << endl;
    sum = sum_arr(cookies, cookies + 3);
    cout << "cookies + 3 :" << *(cookies + 3) << endl;
    cout << "First : " << sum << endl;
    sum = sum_arr(cookies + 4, cookies + 8);
    cout << "Last four eaters ate " << sum << endl;
    cout << "2.-------------------------------" << endl;
    int years = 13;
    int *age = &years;
    const int *pt = age;
    (++years)++;
    cout << "pt : " << *pt << endl;
    return 0;
}