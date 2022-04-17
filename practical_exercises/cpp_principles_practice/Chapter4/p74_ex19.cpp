//
// Created by renbin jiang on 2022/4/17.
//
#include "std_lib_facilities.h"

int main() {
    vector<string> names;
    vector<int> scores;
    int num;
    string str;
    bool same = false;
    while (cin >> str >> num) {
        for (const string tmp : names) {
            if (str == tmp) {
                cout << "Name is same!\n";
                same = true;
                break;
            }
        }
        if (same) break;
        if (!str.compare("No")) {
            cout << "Input END!\n";
            break;
        }
        names.push_back(str);
        scores.push_back(num);
        cout << "Enter a name and a value:\n";
    }
    int i = 0;
    cout << "results:\n";
    for (string a : names) {
        cout << a << " - " << scores[i++] << endl;
    }
    // ex20
    cout << "Who's score would you like to look up?\n";
    string who = "";
    int c = 0;
    bool is_found = false;
    while (cin >> who) {
        for (string b : names) {
            if (who == b) {
                cout << who << "'s scores = " << scores[c] << endl;
                is_found = true;
                break;
            }
            c++;
            if (c > names.size()) {
                cout << "Scores Not found!\n";
                break;
            }
        }
        if (is_found) break;
    }

    // ex21
    int query = 0;
    cout << "Which score would you like to look up?\n";
    c = 0;
    is_found = false;
    while (cin >> query) {
        for (int m : scores) {
            if (m == query) {
                cout << query << " --> " << names[c] << endl;
                is_found = true;
                break;
            }
            c++;
            if (c > scores.size()) {
                cout << "Name not found!\n" << endl;
                break;
            }
        }
        if (is_found) break;
    }
    return 0;
}