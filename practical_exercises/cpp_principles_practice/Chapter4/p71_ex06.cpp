//
// Created by renbin jiang on 2022/4/13.
//
#include "std_lib_facilities.h"
#define MIN(x, y) ((x) > (y) ? (y) : (x))

int main() {
    vector<double> x;
    vector<string> s = {"cm", "in", "ft", "m"};
    map<double, string> input;
    double a, m, in, cm, ft;
    string str;
    double sum = 0;
    int index = 0;
    while (cin >> a >> str) {
        cout << "input value : " << a << str << endl;
        for (index = 0; index < s.size(); index++) {
            if (s[index] == str) break;
        }
        if (index > 3) {
            cout << "Error, Illgal input!\n";
            return -1;
        }
        switch (index) {
            case 0: // cm
                m = a / 100.0;
                break;

            case 1: // in
                cm = a * 2.54;
                m = cm / 100.0;
                cout << a << str << " = " << cm << " cm" << endl;
                break;

            case 2: // ft
                in = a * 12;
                m = in * 2.54 / 100.0;
                cout << a << str << " = " << in << " in" << endl;
                break;
            case 3: // m
                cm = a * 100;
                m = a;
                cout << a << str << " = " << cm << " cm" << endl;
                break;
            default:
                break;
        }
        x.push_back(a);
        input.insert(pair<double, string>(a, str));
        sum += m;
    }
    sort(x.begin(), x.end());

    for (int i = 0; i < x.size(); ++i) {
        if (a == x[(x.size() - 1)])
            cout << "the largest so far : " << x[(x.size() - 1)] << endl;
        else if (a == x[0])
            cout << "the smallest so far : " << x[0] << endl;
    }

    cout << "Input numbers:" << x.size() << endl;
    cout << "Sum is :" << sum << "m " << endl;
    cout << endl;
    for (const auto& [key, value] : input) {
        std::cout << '[' << key << "] = " << value << ";";
    }
    cout << endl;
    map<double, string>::reverse_iterator iter;
    for (iter = input.rbegin(); iter != input.rend(); ++iter) {
        cout << iter->first << " " << iter->second << endl;
    }
    cout << "----------------\n";
    map<double, string>::iterator iter1;
    for (iter1 = input.begin(); iter1 != input.end(); iter1++) {
        cout << iter1->first << " " << iter1->second << endl;
    }
    cout << "----------------\n";
    for (const auto &n : input) {
        cout << n.first << " " << n.second << endl;
    }
    return 0;
}