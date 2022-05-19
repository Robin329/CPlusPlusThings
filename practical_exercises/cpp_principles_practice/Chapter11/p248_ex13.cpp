//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
//  C11 - Exercise 14
/*
        Write a program that reads a text file and writes out how many characters of
        each character classification are in the file.
*/
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void countCharClassification(string s) {
    int space(0), letter(0), digit(0), hDigit(0), uCase(0), lCase(0), controlC(0), punc(0);
    for (char c : s) {
        if (isspace(c)) ++space;
        if (isalpha(c)) ++letter;
        if (isdigit(c)) ++digit;
        if (isxdigit(c)) ++hDigit;
        if (isupper(c)) ++uCase;
        if (islower(c)) ++lCase;
        if (iscntrl(c)) ++controlC;
        if (ispunct(c)) ++punc;
    }

    cout << "Types of characters in string:" << endl;
    cout << "Spaces: " << space << endl;
    cout << "Letters: " << letter << endl;
    cout << "Decimal Digits: " << digit << endl;
    cout << "Hexadecimal Digits: " << hDigit << endl;
    cout << "Upper Case Characters: " << uCase << endl;
    cout << "Lower Case Characters: " << lCase << endl;
    cout << "Control Characters: " << controlC << endl;
    cout << "Punctuation Characters: " << punc << endl;
}

// -----------------------------------------------------------------------------

int main() {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/newFile.txt")};
    stringstream ss;
    ss << readIn.rdbuf();
    string temp = ss.str();
    countCharClassification(temp);

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
