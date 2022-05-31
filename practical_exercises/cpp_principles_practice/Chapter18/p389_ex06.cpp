//
// Created by renbin jiang on 2022/5/29.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 5, 6
/*
        5. Write a function, string cat_dot(const string& s1, const string& s2), that
           concatenates two strings with a dot in between. For example, cat_dot("Niels", "Bohr")
           will return a string containing Neils.Bohr.
        6. Modify cat_dot() from the previous exercise to take a string to be used as
        the seperator (rather than the dot) as its third argument.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// exercise 5
string cat_dot(const string& s1, const string& s2) {
    return s1 + "." + s2;
}

// -----------------------------------------------------------------------------

// exercise 6
string cat_dot2(const string& s1, const string& dot, const string& s2) {
    return s1 + dot + s2;
}

// -----------------------------------------------------------------------------

int main() {
    string s1, s2, s3;

    cout << "Enter two strings >> ";
    cin >> s1 >> s2;
    cout << "\nCat_dot: " << cat_dot(s1, s2) << endl << endl;

    cout << "Enter three strings word,punctuation(or another word),word >> ";
    cin >> s1 >> s2 >> s3;
    cout << "\nCat_dot: " << cat_dot2(s1, s2, s3) << endl << endl;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
