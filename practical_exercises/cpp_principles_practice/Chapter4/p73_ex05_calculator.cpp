//
// Created by renbin jiang on 2022/4/13.
//
#include "std_lib_facilities.h"

int main() {
    double val1 = 0;
    double val2 = 0;
    double result = 0;

    char operation = ' ';

    cout << "Enter two values, in order, and an operation to perform\n";
    while (cin >> val1 >> operation >> val2) {
        switch (operation) {
            case '+':
                result = val1 + val2;
                break;
            case '-':
                result = val1 - val2;
                break;
            case '*':
                result = val1 * val2;
                break;
            case '/':
                result = val1 / val2;
                break;
            default:
                cout << "Error: unrecognized operation\n";
        }

        cout << "That equals: " << result << " shall we do another?\n";
    }
}