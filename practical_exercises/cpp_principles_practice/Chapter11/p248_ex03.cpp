//
// Created by renbin jiang on 2022/5/19.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 4
/*
        Write a program called multi_input.cpp that prompts the user to enter several
        integers in any combination of octal, decimal, or hexadecimal, using the 0
        and 0x base suffixes; interpret the numbers correctly; and converts them to
        decimal form. Then your program should output the values in properly spaced
        columns like this:
                0x43	hexadecimal		converts to		67 decimal
                0123	octal			converts to		83 decimal
                  65	decimal			converts to		65 decimal
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

vector<string> v_numbers;

// -----------------------------------------------------------------------------

bool isCorrectNumber(string s) {
    for (char c : s) {
        if (!isxdigit(c) && c != 'x') return false;
    }

    return true;
}

// -----------------------------------------------------------------------------

stringstream printLine(string s) {
    int num = stoi(s.c_str(), nullptr,
                   0); // setting base of 0 to allow stoi to determine if dec, oct or hex

    stringstream ss;
    if (s.size() == 1)
        ss << setw(5) << s << "\t"
           << "decimal\t\t" << setw(11) << "converts to" << setw(8) << num << setw(8) << " decimal"
           << endl;
    else if (s[0] == '0' && s[1] == 'x')
        ss << setw(5) << s << "\t"
           << "hexadecimal\t" << setw(11) << "converts to" << setw(8) << dec << num << setw(8)
           << " decimal" << endl;
    else if (s[0] == '0')
        ss << setw(5) << s << "\t"
           << "octal\t\t" << setw(11) << "converts to" << setw(8) << dec << num << setw(8)
           << " decimal" << endl;
    else
        ss << setw(5) << s << "\t"
           << "decimal\t\t" << setw(11) << "converts to" << setw(8) << num << setw(8) << " decimal"
           << endl;

    return ss;
}

// -----------------------------------------------------------------------------

int main() {
    cout << "Please enter numbers. Press ctrl+z to stop. To enter numbers other than decimal, use "
            "the following prefixes:"
         << endl;
    cout << "\tHex: 0x"
         << "\n\tOct: 0"
         << "\n>>";

    string temp;
    while (cin >> temp) {
        if (!isCorrectNumber(temp))
            cout << "That wasn't a number. Try again." << endl;
        else
            v_numbers.push_back(temp);

        cout << ">>";
    }

    for (string s : v_numbers) cout << printLine(s).str();

    cout << endl;
    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
