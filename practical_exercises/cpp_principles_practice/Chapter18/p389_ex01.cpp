//
// Created by renbin jiang on 2022/5/28.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 1
/*
        Write a function, char* strdup(const char*), that copies a C-style string
        into memory it allocates on the free store. Do not use any standard library
        functions. Do not use subscripting; use the dereference operator * instead.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int arrayLength(const char* c) {
    char* temp = const_cast<char*>(
            c); // oh dear. one day I'll re-write this without using const_cast....sigh
    int size = 0;
    for (; *temp != 0; ++temp) ++size;

    return size + 1;
}

// -----------------------------------------------------------------------------

char* my_strdup(const char* c) {
    // need to know the length of c to allocate the array on the heap
    int arraySize = arrayLength(c);

    char* arrayCopy = new char[arraySize];

    // copy the values
    char* start = arrayCopy;

    for (int i = 0; i < arraySize; ++i) {
        *arrayCopy = *c;
        ++arrayCopy;
        ++c;
    }

    return start;
}

// -----------------------------------------------------------------------------

// drill4
int main() {
    const char* hello = "hello, world!";
    const char* hello2 = my_strdup(hello);

    cout << hello << endl;
    cout << hello2 << endl;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
