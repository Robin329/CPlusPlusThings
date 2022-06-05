//
// Created by renbin jiang on 2022/6/4.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 2
/*
        Write a template function that takes a vector<T> vt  and a vector<U> vu as
        arguments and returns the sum of all vt[i]*vu[i]s.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <type_traits>

#include "std_lib_facilities.h"

typedef uint32_t uint32;

// -----------------------------------------------------------------------------

template <typename T1, typename T2>
typename common_type<T1, T2>::type f2(vector<T1>& vt, vector<T2>& vu) {
    uint32 s = (vt.size() <= vu.size()) ? vt.size() : vu.size();
    typename common_type<T1, T2>::type sum = 0;

    for (uint32 i = 0; i < s; ++i) sum += vt[i] * vu[i];

    return sum;
}

// -----------------------------------------------------------------------------
#pragma warning(disable:37)
int b[100];
void fun(int b[100]) {
    cout << "fun -- sizeof(b):" << sizeof(b) << endl;
}

int main() {
    vector<int> v1{10, 1, 24, 50, 98, 4, 345, 10};
    vector<int> v2(8, 10);

    vector<double> v3{10.1, 100.1, 73.5, 9.765, 8, 9001, 86.5, 78.3, 9.2, 11};
    vector<double> v4(9, 10.5);

    vector<char> v5{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<char> v6{11, 'z'};

    // will not compile as strings cannot be multiplied together
    // vector<string> v7{ "apple", "banana", "cantaloupe", "dingleberry" };
    // vector<string> v8{ 10, "-smoothie" };

    cout << "Sum: " << f2(v1, v4);
    cout << endl;

    cout << "Sum: " << f2(v3, v6);
    cout << endl;

    cout << "Sum: " << f2(v5, v2);
    cout << endl;

    int* p = NULL;
    cout << "sizeof(p):" << sizeof(p) << endl;   // 8
    cout << "sizeof(*p):" << sizeof(*p) << endl; // 4
    int a[100];
    cout << "sizeof(a):" << sizeof(a) << endl;           // 400
    cout << "sizeof(a[100]):" << sizeof(a[100]) << endl; // 4
    cout << "sizeof(&a):" << sizeof(&a) << endl;         // 8
    cout << "sizeof(&a[0]:" << sizeof(&a[0]) << endl;    // 8
#pragma message(" func eneter")
    fun(b);
    cout << "sizeof(b):" << sizeof(b) << endl;
    cout << "line:" << __LINE__ <<endl;
    cout << "file:" << __FILE__ <<endl;
    cout << "date:" << __DATE__ <<endl;
    cout << "time:" << __TIME__ << endl;
    cout << "stdc:" << __STDC__ << endl;
    cout << "";
    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
