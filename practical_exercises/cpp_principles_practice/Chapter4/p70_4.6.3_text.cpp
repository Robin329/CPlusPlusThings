//
// Created by renbin jiang on 2022/4/12.
//
#include "std_lib_facilities.h"

int main() {
    vector<string> words;
    string temp;
    while(cin >> temp) {
        words.push_back(temp);
    }
    cout << "Number of words : " << words.size() << endl;
    sort(words.begin(), words.end());
    for (int i = 0; i < words.size(); ++i) {
        if (i == 0 || words[i - 1] != words[i]) {
            cout << words[i] << endl;
        }
    }
    return 0;
}