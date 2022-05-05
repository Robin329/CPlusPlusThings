//
// Created by renbin jiang on 2022/5/6.
//
// -----------------------------------------------------------------------------
//
//	C8 - Exercise 13
//
// -----------------------------------------------------------------------------

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

vector<int> getStringLengths(const vector<string>& v) {
    vector<int> stringLengths;

    for (string s : v) stringLengths.push_back(s.size());

    return stringLengths;
}

// -----------------------------------------------------------------------------

struct stringInfo {
    vector<string> longWords, shortWords;
    string longest, shortest;
    string first, last;
};

stringInfo getStringInfo(const vector<string>& v) {
    vector<string> temp = v;
    stringInfo si;

    sort(temp.begin(), temp.end());
    si.first = si.shortest = si.longest = temp[0];
    si.last = temp.back(); // returns the last element of a vector...very handy, I was sick of
                           // typing vector.size() - 1

    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i].size() < si.shortest.size()) si.shortest = temp[i];
        if (temp[i].size() > si.longest.size()) si.longest = temp[i];
    }

    for (string s : v) {
        if (s.size() == si.shortest.size()) si.shortWords.push_back(s);
        if (s.size() == si.longest.size()) si.longWords.push_back(s);
    }

    return si;
}

// -----------------------------------------------------------------------------

int main() {
    vector<string> words{"this",    "is",   "the",  "ultimate", "showdown", "of",  "ultimate",
                         "destiny", "good", "guys", "bad",      "guys",     "and", "explosions",
                         "as",      "far",  "as",   "the",      "eye",      "can", "see"};

    vector<int> stringLengths = getStringLengths(words);
    stringInfo si = getStringInfo(words);

    cout << "\nString Lengths: ";
    for (int i : stringLengths) cout << i << ", ";

    cout << "\nLongest Word(s): ";
    for (string s : si.longWords) cout << s << ", ";
    cout << "\nShortest Word(s): ";
    for (string s : si.shortWords) cout << s << ", ";
    cout << "\nFirst Word: " << si.first << endl;
    cout << "Last Word: " << si.last << endl;

    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
