//
// Created by renbin jiang on 2022/5/29.
//
// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 10
/*
        Look at the "array solution" to the palindrome problem in section 18.7.2.
        Fix it to deal with long strings by (a) reporting if an input string was too
        long and (b) allowing an arbitrarily long string. Comment on the complexity
        of the two versions.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// s points to the first character of an array of n characters
bool is_palindrome(const char s[], int n) {
    int first = 0;    // index of first
    int last = n - 1; // index of last

    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first; // move forward 1
        --last;  // move back 1
    }

    return true;
}

// -----------------------------------------------------------------------------

// read at most max-1 characters from is into buffer
istream& read_word(istream& is, char* buffer, int max) {
    is.width(max); // read at most max-1 characters in the next >>
    is >> buffer;  // read whitespace-terminated word,
    // add zero after the last character read into buffer
    return is;
}

// -----------------------------------------------------------------------------

// read at most max-1 characters from is into buffer
istream& read_word2(istream& is, char* buffer, int max) {
    is.getline(buffer, max);

    // check the state of the failbit of cin to see if there were too many characters
    if (is.fail()) {
        cout << "The max string size is " << max
             << ". You have entered too many characters and the sentence has been cut off." << endl;
        is.clear();               // clear the error flag set in is.failbit
        is.ignore(INT_MAX, '\n'); // ignore INT_MAX amount of characters (2147483647) and skip to
                                  // the next line
    }

    return is;
}

// -----------------------------------------------------------------------------

int main() {
    const int max = 10;

    for (char s[max]; read_word2(cin, s, max);) {
        cout << s << " is";
        if (!is_palindrome(s, strlen(s))) cout << " not";
        cout << " a palindrome\n" << endl;
    }

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
