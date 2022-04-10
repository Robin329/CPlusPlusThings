//
// Created by renbin jiang on 2022/4/11.
//
#include "std_lib_facilities.h"

int main() {
    char c = 'a';
    int i = 0;
    for (; i < 26; i++) {
        cout << (char)(c + i) << "  " << c + i << endl;
    }
    return 0;
}