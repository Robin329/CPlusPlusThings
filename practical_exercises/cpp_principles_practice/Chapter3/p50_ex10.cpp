//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Provide an operation and two values you'd like operated on:\n";
    string operatus;
    double val1;
    double val2;
    cin >> operatus >> val1 >> val2;

    double result = 0;

    if (operatus == "+" || operatus == "plus")
        result = val1 + val2;
    else if (operatus == "-" || operatus == "minus")
        result = val1 - val2;
    else if (operatus == "*" || operatus == "mul")
        result = val1 * val2;
    else if (operatus == "/" || operatus == "div")
        result = val1 / val2;

    cout << "The result of your operation is:" << result << '\n';
    return 0;
}