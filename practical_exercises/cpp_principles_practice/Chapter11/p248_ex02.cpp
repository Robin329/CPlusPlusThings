//
// Created by renbin jiang on 2022/5/17.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 2
/*
        Write a program that given a file name and a word outputs each line that
        contains that word together with the line number. Hint: getline().
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void wordToLower(string& s) {
    for (int i = 0; i < s.size(); ++i) s[i] = tolower(s[i]);
}

// -----------------------------------------------------------------------------

int main() {
    string s1, s2, s3, chosenWord;
    int lineNumber = 0;
    //    ifstream readIn{"inputFile.txt"};
    ifstream readIn(FileSystem::getPath(CURRENT_PATH "Chapter11/res/inputFile.txt"), ios_base::binary);
//    ofstream ofs(FileSystem::getPath(CURRENT_PATH "Chapter11/res/output.txt"), ios_base::binary);

    cout << "What word do you want to find? >> ";
    cin >> chosenWord;
    wordToLower(chosenWord);
    bool chosenFound = false;

    while (getline(readIn, s1)) {
        ++lineNumber;
        stringstream ss(s1);
        while (ss >> s2) {
            for (char c : s2) {
                // what if word is end of sentence or apostrophe, allow . && '
                if (isalpha(c) || c == '\'') s3 += c;
            }
            wordToLower(s3);
            if (s3 == chosenWord) {
                chosenFound = true;
                cout << "Line: " << lineNumber << " - " << s1 << endl;
            }
            s3 = "";
        }
    }

    if (!chosenFound) cout << "Sorry that word is not in the file." << endl;

    cout << endl;
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
