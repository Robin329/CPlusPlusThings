// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 17 - Exercise 3
/*
        3. Write a function, void to_lower(char* s), that replaces all uppercase
        characters in the C-style string s with their lowercase equivalents. For
        example, Hello, World! becomes hello, world!. Do not use any standard library
        functions. A C-style string is a zero-terminated array of characters. So if you
        find a char with the value 0 you are at the end.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void to_lower(char* s) {
    if (s == nullptr) return;
    for (; *s != '\0'; ++s) // start at address 1 and increment by addresses until null is reached
        *s |= (1 << 5);     // set bit number 5 of character to 1, this will flip upper to lower
}

// -----------------------------------------------------------------------------

char* my_strdup(const char* c) {
    if (c == nullptr) return nullptr;
    int length = 0;
    while (c[length] != 0) ++length;

    char* newC = new char[length + 1]; // +1 for terminating 0
    for (int i = 0; i <= length; ++i) newC[i] = c[i];

    return newC;
}

// -----------------------------------------------------------------------------

char* findx(const char* s, const char* x) {
    if (!s || !x) return nullptr;
    char* start = const_cast<char*>(s);
    for (; *start != 0; ++start) {
        if (*start == *x) return start;
    }
    return 0;
}

// -----------------------------------------------------------------------------
int main() {
    char hello[] = "HeLlO, WoRlD!";
    to_lower(hello);

    cout << hello << endl;

    // examples of bit flipping

    // flips to capital, does nothing if it's already capital
    char e = 'e';
    char c = e &= ~(1 << 5);
    cout << "c:" << c << endl;

    // will keep lowercase. Change 1 to 0 to flip it
    char c2 = e |= (1 << 5);
    cout << "c2:" << c2 << endl;
    // will not change punctuation
    char p = ',';
    char c3 = p |= (1 << 5);
    cout << "c3:" << c3 << endl;

    // ex04
    char hello4[] = "hello, world";
    char* helloPtr = my_strdup(hello4);
    cout << "helloPtr:" << helloPtr << endl;

    // ex05
    string s = "hello, world";
    const char* c05;
    c05 = findx(s.c_str(), "o");

    cout << "c05:" << c05 << endl;

    // 7
    char* cstr = new char[256];
    cout << ">> ";
    cin.get(cstr, 256, '!');
    cout << endl << cstr << endl;

    cin.clear();
    cin.ignore(256, '\n');

    // 8
    string str;
    cout << ">> ";
    getline(cin, str, '!');

    // 09
    // stack
    int nn1 = 1;
    int nn2 = 1;
    int nn3 = 1;
    int nn4 = 1;
    int nn5 = 1;
    cout << "Addresses1: " << &nn1 << ", " << &nn2 << ", " << &nn3 << ", " << &nn4 << ", " << &nn5
         << endl;
    if ((&nn5 - &nn1) > 0)
        
        // 向上
        cout << "stack grows upwards" << endl;
    else
        // 向下
        cout << "stack grows downwards" << endl;

    double dd1 = 1;
    double dd2 = 1;
    double dd3 = 1;
    double dd4 = 1;
    double dd5 = 1;
    cout << "Addresses2: " << &dd1 << ", " << &dd2 << ", " << &dd3 << ", " << &dd4 << ", " << &dd5
         << endl;
    if ((&dd5 - &dd1) > 0)
        cout << "stack grows upwards" << endl;
    else
        cout << "stack grows downwards" << endl;

    // free store
    int* n1 = new int(10);
    int* n2 = new int(12);
    int* n3 = new int(20);
    int* n4 = new int(55);
    int* n5 = new int(4);
    cout << "Addresses3: " << n1 << ", " << n2 << ", " << n3 << ", " << n4 << ", " << n5 << endl;
    if ((n5 - n1) > 0)
        cout << "stack grows upwards" << endl;
    else
        cout << "stack grows downwards" << endl;

    double* d1 = new double(10);
    double* d2 = new double(10);
    double* d3 = new double(10);
    double* d4 = new double(10);
    double* d5 = new double(10);
    cout << "Addresses4: " << d1 << ", " << d2 << ", " << d3 << ", " << d4 << ", " << d5 << endl;
    if ((d5 - d1) > 0)
        cout << "stack grows upwards" << endl;
    else
        cout << "stack grows downwards" << endl;

    char* c1 = new char('a');
    char* c02 = new char('a');
    char* c03 = new char('a');
    char* c4 = new char('a');
    char* c5 = new char('a');
    cout << "Addresses5: " << (void*)&c1 << ", " << (void*)&c02 << ", " << (void*)&c03 << ", "
         << (void*)&c4 << ", " << (void*)&c5 << endl;
    if ((c5 - c1) > 0)
        cout << "stack grows upwards" << endl;
    else
        cout << "stack grows downwards" << endl;
    cout << endl << str << endl;
    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
