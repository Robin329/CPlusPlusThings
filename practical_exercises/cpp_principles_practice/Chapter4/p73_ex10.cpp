//
// Created by renbin jiang on 2022/4/14.
//
#include "std_lib_facilities.h"
#include <cstdlib>
int main() {
    int rdom = rand() % 3;
    vector<string> str= {"s", "j", "b"};
    string in;
    int index = 0;
    while (cin >> in) {
        for (int i = 0;i < str.size();++i) {
            if (str[i]  == in) {
                index = i;
            }
        }
        rdom = rand() % 3;
        cout << "Computer : " << str[rdom] << endl;
        switch (index) {
            case 0:
                if (rdom == 0) cout << " Continue!\n";
                if (rdom == 1) cout << " You WIN!\n";
                if (rdom == 2) cout << " Computer WIN!\n";
                
                break;
            case 1:
                if (rdom == 1) cout << " Continue!\n";
                if (rdom == 2) cout << " You WIN!\n";
                if (rdom == 0) cout << " Computer WIN!\n";
                break;
            case 2:
                if (rdom == 2) cout << " Continue!\n";
                if (rdom == 0) cout << " You WIN!\n";
                if (rdom == 1) cout << " Computer WIN!\n";
                break;
            default:
                break;
        }
    }
    
    return 0;
}