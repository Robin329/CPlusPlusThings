//
// Created by renbin jiang on 2022/6/4.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 1
/*
        Write a template function f() that adds the elements of one vector<T> to
        elements of another; for example, f(v1, v2) should do v1[i] += v2[i] for
        each element of v1.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

typedef uint32_t uint32;

// -----------------------------------------------------------------------------

template <typename T>
void f(vector<T>& v1, vector<T>& v2) {
    if (v1.size() > v2.size()) {
        for (uint32 i = 0; i < v2.size(); ++i) v1[i] += v2[i];
    } else if (v1.size() <= v2.size()) {
        for (uint32 i = 0; i < v1.size(); ++i) v1[i] += v2[i];
    } else {
        cout << "weird vectors..." << endl;
    }
}

// -----------------------------------------------------------------------------

int main() {
    vector<int> v1{10, 1, 24, 50, 98, 4, 345, 10};
    vector<int> v2(8, 10);
    f(v1, v2);

    for (uint32 i = 0; i < (v1.size() < v2.size() ? v1.size() : v2.size()); ++i)
        cout << v1[i] << ", ";
    cout << endl;

    vector<double> v3{10.1, 100.1, 73.5, 9.765, 8, 9001, 86.5, 78.3, 9.2, 11};
    vector<double> v4(9, 10.5);
    f(v3, v4);

    for (uint32 i = 0; i < v3.size(); ++i) cout << v3[i] << ", ";
    cout << endl;

    vector<char> v5{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<char> v6{11, 'z'};
    f(v5, v6);

    for (uint32 i = 0; i < v5.size(); ++i) cout << v5[i] << ", ";
    cout << endl;

    vector<string> v7{"apple", "banana", "cantaloupe", "dingleberry"};
    vector<string> v8{10, "-smoothie"};
    f(v7, v8);

    for (uint32 i = 0; i < v7.size(); ++i) cout << v7[i] << ", ";
    cout << endl;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
