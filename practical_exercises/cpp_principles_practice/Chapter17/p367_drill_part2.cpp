//
// Created by renbin jiang on 2022/5/23.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 17 - Part 2 Drills
/*
        1. Allocate an int, intialise it to 7, and assign its address to a variable p1.
        2. Print out the value of p1 and of the int it points to.
        3. Allocate an array of seven ints ; initialise it to 1, 2, 3, 4, 8, etc.; and
           assign its address to a variable p2.
        4. Print out the value of p2 and of the array it points to.
        5. Declare an int* called p3 and initialise it with p2.
        6. Assign p1 to p2.
        7. Assign p3 to p2.
        8. Print out the values of p1 and p2 and of what they point to.
        9. Deallocate all the memory you allocated from the free store.
        10. Allocate an array of ten ints; intialise it to 1, 2, 4, 8, etc.; and assign
                its address to a variable p1.
        11. Allocate an array of ten ints, and assign its address to a variable p2.
        12. Copy the values from the array pointed to by p1 into the array pointed to by p2.
        13. Repeat 10-12 using a vector rather than an array.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void printArray(ostream& os, int* a, int n) {
    if (!a) return;
    for (int i = 0; i < n; ++i) {
        os << "Int " << i << ": " << *a << "	Addr: " << a << endl;
        ++a; // increment the address by int size
    }
    cout << endl;
}

// -----------------------------------------------------------------------------

int main() {
    // drill 1
    int n = 7;
    int* p1 = &n;
    *p1 = 5;
    // drill 2
    cout << "n: " << n << "	p1: " << p1 << endl;

    // drill 3
    int sevenInts[7] = {1, 2, 4, 8, 16, 32, 64};
    int* p2 = sevenInts;
    int* p22 = sevenInts;
    // drill 4
    cout << "-----------------------------------" << endl;

    p22[0] = 3;
    printArray(cout, p2, 7);
    printArray(cout, sevenInts, 7);
    printArray(cout, p22, 7);
    cout << "p2: " << p2 << endl;

    // drill 5
    int* p3 = p2;

    // drill 6
    p2 = p1;

    // drill 7
    p2 = p3;

    // drill 8
    cout << "-----------------------------------" << endl;
    cout << "p1: " << p1 << "/" << *p1 << endl;
    printArray(cout, p2, 7);

    // drill 9
    // we haven't allocated anything to the free store, they are all local variables;
    // therefore they are allocated on the stack

    // drill 10
    int tenInts[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    p1 = tenInts;

    // drill 11
    int tenInts2[10] = {10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120};
    p2 = tenInts2;

    // drill 12
    for (int i = 0; i < 10; ++i) p2[i] = p1[i];

    // drill 13
    vector<int> v_tenInts{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    p1 = &v_tenInts[0];
    vector<int> v_tenInts2{10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120};
    p2 = &v_tenInts2[0];
    for (int i = 0; i < 10; ++i) p2[i] = p1[i];

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
