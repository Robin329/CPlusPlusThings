//
// Created by renbin jiang on 2022/4/23.
//
//--------------------------------------------//
// C6 - Exercise 9
//--------------------------------------------//

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int main() {
    cout << "Enter up to 4 digits >> ";
    string digit;
    cin >> digit;

    if (digit.size() > 4) error("Too many numbers.");

    size_t found = digit.find_first_not_of("0123456789");
    if (found != digit.npos) error("That's not a number");

    int number = stoi(digit);

    cout << number << " is ";
    switch (digit.size()) {
        case 1:
            cout << digit[0] << " one(s)." << endl;
            break;
        case 2:
            cout << digit[0] << " ten(s) and " << digit[1] << " one(s)" << endl;
            break;
        case 3:
            cout << digit[0] << " hundred(s) and " << digit[1] << " ten(s) and " << digit[2]
                 << " one(s)." << endl;
            break;
        case 4:
            cout << digit[0] << " thousand(s) and " << digit[1] << " hundred(s) and " << digit[2]
                 << " ten(s) and " << digit[3] << " one(s)." << endl;
            break;
    }

    keep_window_open();
    return 0;
}

//------------------------------------------------------------------------------
