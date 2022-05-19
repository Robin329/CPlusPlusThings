//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 5
/*
        Write a program that reads strings and for each string outputs the character
        classification of each character, as defined by the character classification
        functions presented in section 11.6. Note that a character can have several
        classifications (e.g, x is both a letter and an alphanumeric)
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void printCharClassification(string s) {
    for (char c : s) {
        cout << "- " << c << " is: ";
        if (isspace(c)) cout << " A space. ";
        if (isalpha(c)) cout << " A letter.";
        if (isdigit(c)) cout << " A decimal digit.";
        if (isxdigit(c)) cout << " A hexadecimal digit.";
        if (isupper(c)) cout << " An uppercase character.";
        if (islower(c)) cout << " A lowercase character.";
        if (iscntrl(c)) cout << " A control character.";
        if (ispunct(c)) cout << " A punctuation character.";
        cout << endl;
    }
}

// -----------------------------------------------------------------------------

int main() {
    cout << "Please enter strings. Press ctrl+z to stop.\n>>";
    string temp;
    while (cin >> temp) {
        printCharClassification(temp);
        cout << ">>";
    }

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
