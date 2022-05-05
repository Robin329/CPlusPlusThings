//
// Created by renbin jiang on 2022/5/6.
//
#include "std_lib_facilities.h"

void print(const vector<int> &v, const string &label) {
    cout << label << endl;
    for (const auto i : v) {
        cout << i << endl;
    }
}
int main() {
    vector<int> num{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print(num, "Num 1 - 10:");

    return 0;
}