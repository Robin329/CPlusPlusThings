//
// Created by renbin jiang on 2022/5/29.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 8
/*
        Rewrite all the functions in section 18.7 to use the approach of making a
        backward copy of the string and then comparing; for example, take "home",
        generate "emoh", and compare those two strings to see that they are different,
        so home isn't a palindrome.

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

bool is_palindrome(const string& s) {
    string backwards;
    for (int i = s.size() - 1; i >= 0; --i) backwards += s[i];

    if (backwards == s) return true;

    return false;
}

// -----------------------------------------------------------------------------

bool is_palindrome(const char s[], int n) {
    char* backwards = new char[n];

    int tempN = n - 1;
    for (int i = 0; i < n; ++i) backwards[i] = s[--tempN];
    backwards[n - 1] = 0;

    if (strcmp(backwards, s) == 0) return true;

    delete[] backwards;

    return false;
}

// -----------------------------------------------------------------------------

bool is_palindrome(const char* first, const char* last) {
    return is_palindrome(first, aSize(first));
}

// -----------------------------------------------------------------------------

int main() {
    string home = "home";
    string banana = "banana";
    string kayak = "kayak";
    string racecar = "racecar";
    cout << "Home: " << is_palindrome(home) << endl;
    cout << "Banana: " << is_palindrome(banana) << endl;
    cout << "Kayak: " << is_palindrome(kayak) << endl;
    cout << "Racecar: " << is_palindrome(racecar) << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    char cHome[] = "home";
    char cBanana[] = "banana";
    char cKayak[] = "kayak";
    char cRacecar[] = "racecar";
    cout << "Home: " << is_palindrome(cHome, 5) << endl;
    cout << "Banana: " << is_palindrome(cBanana, 7) << endl;
    cout << "Kayak: " << is_palindrome(cKayak, 6) << endl;
    cout << "Racecar: " << is_palindrome(cRacecar, 8) << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    const char* pHome = "home";
    const char* pBanana = "banana";
    const char* pKayak = "kayak";
    const char* pRacecar = "racecar";
    cout << "Home: " << is_palindrome(pHome, &pHome[3]) << endl;
    cout << "Banana: " << is_palindrome(pBanana, &pBanana[5]) << endl;
    cout << "Kayak: " << is_palindrome(pKayak, &pKayak[4]) << endl;
    cout << "Racecar: " << is_palindrome(pRacecar, &pKayak[6]) << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
