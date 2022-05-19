//
// Created by renbin jiang on 2022/5/19.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 3
/*
        Write a program that removes all vowels from a file ("disemvowels"). For example,
        Once upon a time! becomes nc pn tm!. Surprisingly often, the result is still
        readable; try it on your friends. (I would if I had any)

  The resulting file will read like a text message from 2003. Horrendous.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

string disemvowel(string s) {
    size_t pos = s.find_first_of("aeiouAEIOU");
    while (pos != string::npos) {
        s.erase(pos, 1);
        pos = s.find_first_of("aeiouAEIOU");
    }

    return s;
}

// -----------------------------------------------------------------------------

int main() {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/inputFile_2.txt").c_str()};
    stringstream ss;
    ss << readIn.rdbuf();    // read entire file into stringstream in one go
    string file1 = ss.str(); // convert stringstream to string

    file1 = disemvowel(file1);
    cout << file1;

    cout << endl;
    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
