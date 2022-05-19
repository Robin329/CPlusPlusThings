//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 13
/*
        Reverse the order of words (defined as whitespace-separated strings) in a
        file. For example, Norwegian Blue Parrot becomes parrot Blue Norwegian. You
        are allowed to assume that all the strings from the file will fit into
        memory at once.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int main() {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/newFile.txt")};
    stringstream ss;
    ss << readIn.rdbuf();
    string temp;

    vector<string> v;
    while (ss >> temp) v.push_back(temp);

    string temp2;
    for (int i = v.size() - 1; i >= 0; --i) {
        temp2 += v[i];
        temp2 += " ";
    }

    ofstream readOut{FileSystem::getPath(CURRENT_PATH "Chapter11/res/newFile.txt")};
    readOut << temp2;
    cout << endl;
    if (readIn.is_open())
    readIn.close();
    if (readOut.is_open())
    readOut.close();
    return 0;
}

// -----------------------------------------------------------------------------
