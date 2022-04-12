//
// Created by renbin jiang on 2022/4/13.
//
#include "std_lib_facilities.h"
#define MIN(x, y) ((x) > (y) ? (y) : (x))

int main() {
    vector<double> x;
    vector<string> s = {"cm", "in" , "ft", "m"};
    double a,m,in,cm,ft;
    string str;
    int index = 0;
    while (cin >> a >> str) {
        cout << "input value : " << a <<  str << endl;
        for (;index < s.size();index++) {
            if (s[index] == str)
                break;
        }
        switch (index) {
            case 0://cm
                
                break;
                
            case 1://in
                cm = a * 2.54;
                cout << a << str << " = " << cm << " cm" << endl;
                break;
                
            case 2://ft
                in = a * 12;
                cout << a << str << " = " << in << " in" << endl;
                break;
            case 3://m
                cm = a * 100;
                cout << a << str << " = " << cm << " cm" << endl;
                break;
            default:
                break;
            
        }
        x.push_back(a);
        sort(x.begin(), x.end());
        for (int i = 0; i < x.size(); ++i) {
            if (a == x[(x.size() - 1)])
                cout << "the largest so far : " << x[(x.size() - 1)] << endl;
            else if (a == x[0])
                cout << "the smallest so far : " << x[0] << endl;
        }
    }

    return 0;
}