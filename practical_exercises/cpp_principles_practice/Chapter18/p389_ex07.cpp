//
// Created by renbin jiang on 2022/5/29.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 7
/*
        Write versions of the cat_dot()s from the previous exercises to take C-style
        strings as arguments and return a free-store-allocated C-style string as the
        result. Do not use standard library functions or types in the implementation.
        Test these functions with several strings. Be sure to free (using delete) all
        the memory you allocated from the free store (using new). Compare the effort
        involved in this exercise with the effort involved for exercises 5 and 6.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int aSize(const char* c) {
    char* temp = const_cast<char*>(c);
    int size = 0;
    for (; *temp != 0; ++temp) ++size;

    return size + 1;
}

// -----------------------------------------------------------------------------

char* cat_dot(const char* c1, const char* c2, const char* dot = ".") {
    int c1Size = aSize(c1) - 1; // no longer need these terminating zeroes
    int dotSize = aSize(dot) - 1;
    int c2Size = aSize(c2); // need one here though to get rid of garbage left in array

    char* newString = new char[c1Size + dotSize + c2Size];
    char* start = newString;

    for (int i = 0; i < c1Size; ++i) *start++ = *c1++;

    for (int i = 0; i < dotSize; ++i) *start++ = *dot++;

    for (int i = 0; i < c2Size; ++i) *start++ = *c2++;

    return newString;
}

// -----------------------------------------------------------------------------

int main() {
    const char* c1 = cat_dot("bjarne", "stroustrup");
    cout << c1 << endl;
    const char* c2 = cat_dot("Barnes", "Noble", " and ");
    cout << c2 << endl;

    const char* c3 = cat_dot("peanut butter", "jelly", " and ");
    cout << c3 << endl;
    const char* c4 = cat_dot("5", "10", " + ");
    cout << c4 << endl;

    delete[] c1;
    delete[] c2;
    delete[] c3;
    delete[] c4;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
