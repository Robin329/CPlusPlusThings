//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 12
/*
        Reverse the order of characters in a text file. For example, asdfghjkl becomes
        lkjhgfdsa. Warning: There is no really good, portable, and efficient way of
        reading a file backward.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int main() {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/inputFile.txt")};
    stringstream ss;
    ss << readIn.rdbuf();
    string temp = ss.str();
    string temp2;

    for (int i = temp.size() - 1; i >= 0; --i) temp2 += temp[i];

    ofstream readOut{FileSystem::getPath(CURRENT_PATH "Chapter11/res/inputFile.txt")};
    readOut << temp2;

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
