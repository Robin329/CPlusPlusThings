//
// Created by renbin jiang on 2022/5/28.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 3
/*
        Write a function, int strcmp(const char* s1, const char* s2), that compares
        C-style strings. Let it return a negative number if s1 is lexicographically
        before s2, zero if s1 equals s2, and a positive number if s1 is lexicographically
        after s2. Do not use any standard library functions. Do not use subscripting;
        use the dereference operator * instead.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int arrayLength(const char* c) {
    char* temp = const_cast<char*>(c);
    int size = 0;
    for (; *temp != 0; ++temp) ++size;

    return size + 1;
}

// -----------------------------------------------------------------------------

int my_strcmp(const char* s1, const char* s2) {
    char* s1Start = const_cast<char*>(s1);
    char* s2Start = const_cast<char*>(s2);

    int s1Length = arrayLength(s1);
    int s2Length = arrayLength(s2);

    int shortestLength = (s1Length > s2Length) ? s2Length : s1Length;

    // are they equal?
    if (s1Length == s2Length) {
        int i = 0;
        for (; i < s1Length; ++i) {
            if (*s1 == *s2) {
                ++s1;
                ++s2;
            } else
                break;
        }

        if (i == s1Length) return 0; // s1 is equal to s2
    }
    s1 = s1Start;
    s2 = s2Start;

    bool isBefore = false;
    for (int i = 0; i < shortestLength; ++i) {
        if (*s1 < *s2 || *s1 == *s2) {
            isBefore = true;
            ++s1;
            ++s2;
        } else
            return (isBefore) ? -1 : 1; // 1 means s1 is alphabetically after s2
    }

    return -1; // is s1 alphabetically before s2
}

// -----------------------------------------------------------------------------

// drill4
int main() {
    const char* c1 = "chili";
    const char* c2 = "chilly";
    int n = my_strcmp(c1, c2);
    cout << n << endl;

    const char* c3 = "final";
    const char* c4 = "final";
    int n2 = my_strcmp(c3, c4);
    cout << n2 << endl;

    const char* c5 = "zebra";
    const char* c6 = "blueberries";
    int n3 = my_strcmp(c5, c6);
    cout << n3 << endl;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
