//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 15
/*
        Write a program that reads a file of whitespace-separated numbers and outputs
        a file of numbers using scientific format and precision 8 in four fields of
        20 characters per line.
*/
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int main() {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/numbers.txt")};
    stringstream ss;
    ss << readIn.rdbuf();
    string temp = ss.str();
    string temp2;

    ofstream readOut{FileSystem::getPath(CURRENT_PATH "Chapter11/res/scientificNumbers.txt")};
    int fields = 0;
    while (ss >> temp2) {
        if (fields == 4) {
            readOut << endl;
            fields = 0;
        }
        readOut << scientific << setprecision(8) << setw(20) << temp2;
        ++fields;
    }

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
