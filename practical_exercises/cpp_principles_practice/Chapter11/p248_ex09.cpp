//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 10
/*
        Write a function vector<string> split(const string& s) that returns a vector
        of whitespace-separated substrings from the argument s.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

vector<string> split(const string& s) {
    vector<string> v;
    stringstream ss(s);
    string temp;
    while (ss >> temp) {
        v.push_back(temp);
        v.push_back(" ");
    }

    return v;
}

// -----------------------------------------------------------------------------

vector<string> split1(const string& s, const string& w)
{
    vector<string> v;
    stringstream ss(s);
    string temp;
    while (ss >> temp)
    {
        if (temp != w)
        {
            v.push_back(temp);
            v.push_back(" ");
        }
    }
    
    return v;
}
int main() {
    vector<string> v;
    string temp;
    cout << "\n>>";
    while (getline(cin, temp)) {
        v = split(temp);
        for (string s : v) cout << s;
        cout << "\n>>";
    }

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
