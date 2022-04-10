//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    string previous = "";
    string current;
    int repeatWord = 0, numWords = 0;
    //She she laughed He He He because what he did did not look very very good good
    while (cin >> current) {
        numWords++;
        if (previous == current) {
            ++repeatWord;
            cout << "word number : " << numWords << " repeate word:" << current << endl;
        }
        previous = current;
    }
    return 0;
}