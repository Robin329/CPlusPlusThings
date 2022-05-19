//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 6
/*
        Write a program that replaces punctuation with whitespace. Consider .(dot),
        ; (semicolon), ,(comma), ? (question mark), - (dash), ' (single quote)
        punctuation characters. Don't modify characters within a pair of double
        quotes ("). For example "-don't use the as-if rule." becomes " don t use the
        as if rule ".
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void printCharClassification(string& s) {
    int quotesFound = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '"') ++quotesFound;
        if (ispunct(s[i]) && quotesFound == 0) s[i] = ' ';
        if (quotesFound == 2) quotesFound = 0;
    }
}

// -----------------------------------------------------------------------------

int main() {
    cout << "Please enter strings. Press ctrl+z to stop.\n>>";
    string temp;
    while (getline(cin, temp)) {
        printCharClassification(temp);
        cout << "\n" << temp << endl;
        cout << ">>";
    }

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
