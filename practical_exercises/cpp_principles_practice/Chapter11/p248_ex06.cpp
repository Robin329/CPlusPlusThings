//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 7
/*
        Modify the program from the previous exercise so that it replaces don't with
        do not, can't with cannot, etc.; leaves hyphens within words intact (so that
        we get " do not use the as-if rule "); and converts all characters to lower
        case.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

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

// read in contractions into vectors
void setUpContractions(vector<string>& words, vector<string>& contractions) {
    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/contractions.txt").c_str()};
    string temp;
    bool switchVector = true;
    while (getline(readIn, temp)) {
        if (switchVector) {
            words.push_back(temp);
            switchVector = false;
        } else {
            contractions.push_back(temp);
            switchVector = true;
        }
    }
    readIn.close();
}

// -----------------------------------------------------------------------------

void replacePunctuation(string& s) {
    int quotesFound = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '"') ++quotesFound;
        if (ispunct(s[i]) && quotesFound == 0 && s[i] != '-') s[i] = ' ';
        if (quotesFound == 2) quotesFound = 0;
    }
}

// -----------------------------------------------------------------------------

vector<string> v_normalWords, v_contractionWords;

// replace contractions with full words
void replaceContractions(string& s) {
    for (int i = 0; i < v_contractionWords.size(); ++i) {
        if (s == v_contractionWords[i]) {
            s = v_normalWords[i];
            return;
        }
    }
}

// -----------------------------------------------------------------------------

int main() {
    setUpContractions(v_normalWords, v_contractionWords);

    cout << "Please enter strings. Press ctrl+z to stop.\n";
    string temp;
    while (cin >> temp) {
        dealWithHyphens(temp);
        convertStringToLower(temp);
        replaceContractions(temp);
        replacePunctuation(temp);
        cout << temp << " ";
    }

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
