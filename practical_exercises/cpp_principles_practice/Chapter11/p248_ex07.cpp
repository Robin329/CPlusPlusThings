//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 8
/*
        Use the program from the previous exercise to make a dictionary (as an
        alternative to the approach in section 11.7). Run the result on a multi-page
        text file, look at the result, and see if you can improve the program to make
        a better dictionary.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// remove punctuation and numbers
void removePuncAndNumber(string& s) {
    string temp;
    for (int i = 0; i < s.size(); ++i) {
        if (!isdigit(s[i]) && (!ispunct(s[i]) || s[i] == '-' || s[i] == '\'')) temp += s[i];
    }
    s = temp;
}

// -----------------------------------------------------------------------------

// remove quotations at beginning/end of words
void removeNonEssentialQuote(string& s) {
    if (s[0] == '\'') s.erase(s.begin());
    if (s[s.size() - 1] == '\'') s.erase(s.end() - 1);
}

// -----------------------------------------------------------------------------

// checks for a hyphen in a word
void dealWithHyphens(string& s) {
    // if '-' on it's own or '-' either side of word
    if (s.size() == 1)
        s[0] = ' ';
    else if (s[0] == '-')
        s.erase(s.begin());
    else if (s[s.size() - 1] == '-')
        s.erase(s.end() - 1);
}

// -----------------------------------------------------------------------------

// convert to lower
void convertStringToLower(string& s) {
    for (int i = 0; i < s.size(); ++i) s[i] = tolower(s[i]);
}

// -----------------------------------------------------------------------------

// remove duplicate words
void removeDuplicateWords(vector<string>& v) {
    vector<string> temp;
    sort(v);
    for (int i = 0; i < v.size() - 1; ++i) {
        if (v[i] != v[i + 1]) temp.push_back(v[i]);
    }
    v = temp;
}

// -----------------------------------------------------------------------------

int main() {
    ifstream inputFile{FileSystem::getPath(CURRENT_PATH "Chapter11/res/inputFile.txt")};
    vector<string> v_words;
    string temp;
    assert(true);
    while (inputFile >> temp) {
        removePuncAndNumber(temp);
        if (temp.size() != 0) {
            dealWithHyphens(temp);
            convertStringToLower(temp);
            removeNonEssentialQuote(temp);
            if (temp != " ") v_words.push_back(temp);
        }
    }

    removeDuplicateWords(v_words);
    for (string s : v_words) cout << s << endl;

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
