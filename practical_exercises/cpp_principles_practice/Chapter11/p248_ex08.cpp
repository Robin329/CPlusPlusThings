//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 9
/*
        Split the binary I/O program from section 11.3.2 into two; one program that
        converts an ordinary text file into binary and one program that reads binary
        and converts it to text. Test these programs by comparing a text file with
        what you get by converting it to binary and back.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void txtToBinary(vector<char>& v) {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/inputFile.txt"), ios_base::binary};
    // read from binary file
    for (char c; readIn.read(as_bytes(c), sizeof(char));) v.push_back(c);
}

// -----------------------------------------------------------------------------

void BinaryToTxt(vector<char>& v) {
    ofstream readOut{FileSystem::getPath(CURRENT_PATH "Chapter11/res/converted.txt"), ios_base::binary};
    // write to binary file
    for (char c : v) readOut.write(as_bytes(c), sizeof(char));
}

// -----------------------------------------------------------------------------

int main() {
    vector<char> v;
    txtToBinary(v);
    BinaryToTxt(v);

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
