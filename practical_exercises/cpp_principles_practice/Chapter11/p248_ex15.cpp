//
// Created by renbin jiang on 2022/5/20.
//
// -----------------------------------------------------------------------------
//
// C11 - Exercise 16
/*
        Write a program to read a file of whitespace-separated numbers and output
        them in order (lowest value first), one value per line. Write a value only
        once, and if it occurs more than once write the count of it's occurrences on
        it's line. For example, 7 5 5 7 3 117 5 should give
        3
        5	3
        7	2
        117
*/
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct countNum {
    countNum() : num(0), count(1) {}
    double num;
    int count;
};

bool sortCN(const countNum& a, const countNum& b) {
    return a.num < b.num;
}

// -----------------------------------------------------------------------------

void getCount(vector<countNum>& v) {
    for (int i = 0; i < v.size(); ++i) {
        for (int n = i + 1; n < v.size(); ++n) {
            if (v[i].num == v[n].num) {
                v.erase(v.begin() + n);
                ++v[i].count;
                --i;
            }
            break;
        }
    }
}

// -----------------------------------------------------------------------------

int main() {
    vector<countNum> v;

    ifstream readIn{FileSystem::getPath(CURRENT_PATH "Chapter11/res/numbers.txt")};
    countNum temp;

    while (readIn >> temp.num) v.push_back(temp);

    sort(v.begin(), v.end(), sortCN);
    getCount(v);

    for (countNum cn : v) {
        cout << cn.num << "\t";
        if (cn.count != 1) cout << cn.count;
        cout << endl;
    }

    cout << endl;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
