//
// Created by renbin jiang on 2022/5/25.
//
#include "std_lib_facilities.h"

bool is_palindrome(const string &s) {
    int first(0);
    int last = s.length() - 1;
    if (last == first) return false;
    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first;
        --last;
    }
    return true;
}

// s points to the first character of an array of n characters
bool is_palindrome2(const char s[], int n) {
    int first = 0;
    int last = n - 1;
    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first; // move forward
        --last;  // move backward
    }
    return true;
}

// read at most max-1 characters from is into buffer
istream &read_word(istream &is, char *buffer, int max) {
    is.width(max); // read at most max-1 characters in the next
    is >> buffer;  // read whitespace-terminated word.
                  // add zero after the last character read into buffer
    return is;
}

// drill 1
int ga[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

// drill 2
void f(int a[], int n) {
    // 3a
    int la[10];
    // 3b
    for (int i = 0; i < n; ++i) la[i] = ga[i];

    // 3c
    for (int i = 0; i < n; ++i) cout << la[i] << ", ";
    cout << endl;

    // 3d
    int *p = new int[n];
    // 3e
    memcpy(p, a, n * sizeof(int));
    // 3f
    for (int i = 0; i < n; ++i) cout << p[i] << ", ";
    cout << endl;

    // 3g
    delete[] p;
}

// -----------------------------------------------------------------------------

int fac(int n) {
    return n > 1 ? n * (fac(n - 1)) : 1;
}

// -----------------------------------------------------------------------------

int main() {
    cout << "Please input string:";
    //    string input;
    //    cin >> input;
    //    cout << "is palindrome ? " << is_palindrome(input) << endl;
    //    cin.clear();

    char ch[10];
    cin.getline(ch, 10);
    cout << "input :" << ch << endl;
    cout << "is palindrome ? " << is_palindrome(string(ch)) << endl;

    cout << "--------------------------------\n";
    const int max = 128;
    char s[max] = {};
    cout << "Please input string:";
    while (read_word(cin, s, max)) {
        cout << s << "  is  ";
        if (!is_palindrome2(s, strlen(s))) cout << "not";
        cout << "a palindrome\n";
    }

    // 4a
    f(ga, 10);

    // 4b
    int aa[10]{1, fac(2), fac(3), fac(4), fac(5), fac(6), fac(7), fac(8), fac(9), fac(10)};

    // 4c
    f(aa, 10);
    return 0;
}