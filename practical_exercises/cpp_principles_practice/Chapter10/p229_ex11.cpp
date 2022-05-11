//
// Created by renbin jiang on 2022/5/12.
//
// -----------------------------------------------------------------------------
//
// C10 - Exercise 11
/*
        Write a program that produces the sum of all the whitespace separated integers
        in a text file. For example, bears: 17 elephants 9 end should output 26.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// check that the value being read in is a number
bool isNumber(string value) {
    size_t found = value.find_first_not_of("0123456789");
    if (found != string::npos) return false;

    return true;
}

// -----------------------------------------------------------------------------

int main() {
    ifstream readIn{FileSystem::getPath(string(CURRENT_PATH "Chapter10/res/inputFile.txt")
                                                .c_str())}; // replace this with your own file
    vector<string> v_words;
    double number = 0;

    string temp;
    while (readIn >> temp) v_words.push_back(temp);

    sort(v_words);

    for (string s : v_words) {
        if (isNumber(s))
            number += stoi(s);
        else
            break;
    }

    cout << "Sum of whitespace separated integers: " << number;

    cout << endl;
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
