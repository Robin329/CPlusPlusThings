//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Is it odd or even? Let me tell you! Enter a number:\n";
    int val;
    cin >> val;

    //    string result = "Its odd!\n";
    string result("Its odd!\n");

    if (val % 2 == 0) result = "Its even!\n";

    cout << result;

    // 9
    cout << endl;

    string str;
    int count;
    cout << "Please input num words:\n";
    cin >> str;
    string num[] = {"zero", "one", "two", "three", "four"};
    for(count = 0;count < num->size();count++) {
        if(str.compare(num[count].c_str()) == 0) break;
    }

    switch (count) {
        case 0:
            cout << "0\n";
            break;
        case 1:
            cout << "1\n";
            break;
        case 2:
            cout << "2\n";
            break;
        case 3:
            cout << "3\n";
            break;
        case 4:
            cout << "4\n";
            break;
        default:
            cout << "stupid computer!\n"; break;
    }

    return 0;
}