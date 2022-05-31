//
// Created by renbin jiang on 2022/5/29.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 9
/*
        Consider the memory layout in section 17.4. Write a program that tells the
        order in which static storage, the stack, and the free store are laid out in
        memory. In which direction does the stack grow: upward toward higher addresses
        or downward toward lower addresses? In an array on the free store, are
        with higher indices allocated at higher or lower addresses?

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// static data?
int gN1 = 0;
int gN2 = 0;
int gN3 = 0;
int gN4 = 0;
int gN5 = 0;

// -----------------------------------------------------------------------------

int aSize(const char* c) {
    char* temp = const_cast<char*>(c);
    int size = 0;
    for (; *temp != 0; ++temp) ++size;

    return size + 1;
}

// -----------------------------------------------------------------------------

bool is_palindrome1(const string& s) {
    string backwards;
    for (int i = s.size() - 1; i >= 0; --i) backwards += s[i];

    if (backwards == s) return true;

    return false;
}

// -----------------------------------------------------------------------------

bool is_palindrome2(const char s[], int n) {
    char* backwards = new char[n];

    int tempN = n - 1;
    for (int i = 0; i < n; ++i) backwards[i] = s[--tempN];
    backwards[n - 1] = 0;

    if (strcmp(backwards, s) == 0) return true;

    delete[] backwards;

    return false;
}

// -----------------------------------------------------------------------------

bool is_palindrome3(const char* first, const char* last) {
    return is_palindrome2(first, aSize(first));
}

// -----------------------------------------------------------------------------

int main() {
    // print addresses of global variables
    cout << &gN1 << endl;
    cout << &gN2 << endl;
    cout << &gN3 << endl;
    cout << &gN4 << endl;
    cout << &gN5 << endl;
    cout << "Global ints are growing";
    cout << ((&gN1 > &gN5) ? " downwards." : " upwards.") << endl << endl;

    // print addresses of functions?
    cout << aSize << endl;
    cout << is_palindrome1 << endl;
    cout << is_palindrome2 << endl;
    cout << is_palindrome3 << endl << endl;

    // free store allocated
    const char* c1 = "pineapple";
    const char* c2 = "industries";
    const char* c3 = "notes";
    const char* c4 = "allocation";
    const char* c5 = "heap";
    cout << &c1 << endl;
    cout << &c2 << endl;
    cout << &c3 << endl;
    cout << &c4 << endl;
    cout << &c5 << endl;
    cout << "char pointers are growing";
    cout << ((&c1 > &c5) ? " downwards." : " upwards.") << endl << endl;

    char* c6 = new char[10];
    memcpy(c6, c1, sizeof(char) * 10);
    cout << &c6 << endl;
    char* c7 = new char[11];
    memcpy(c7, c2, sizeof(char) * 11);
    cout << &c7 << endl;
    char* c8 = new char[6];
    memcpy(c8, c3, sizeof(char) * 6);
    cout << &c8 << endl;
    char* c9 = new char[11];
    memcpy(c9, c4, sizeof(char) * 11);
    cout << &c9 << endl;
    char* c10 = new char[5];
    memcpy(c10, c5, sizeof(char) * 5);
    cout << &c10 << endl;
    cout << "[new]char's are growing";
    cout << ((&c1 > &c5) ? " downwards." : " upwards.") << endl << endl;
    delete[] c6;
    delete[] c7;
    delete[] c8;
    delete[] c9;
    delete[] c10;

    double* pd = new double[5];
    for (int i = 0; i < 5; ++i) {
        pd[i] = 5 * 1 * i;
        cout << &pd[i] << endl;
    }
    cout << "[new]doubles are growing";
    cout << ((&pd[0] > &pd[4]) ? " downwards." : " upwards.") << endl << endl;
    delete[] pd;

    double* pd2 = new double[5];
    for (int i = 0; i < 5; ++i) {
        pd2[i] = 1000 - (5 * i * 1);
        cout << &pd2[i] << endl;
    }
    cout << "[new]doubles are growing";
    cout << ((&pd2[0] > &pd2[4]) ? " downwards." : " upwards.") << endl << endl;
    delete[] pd2;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
