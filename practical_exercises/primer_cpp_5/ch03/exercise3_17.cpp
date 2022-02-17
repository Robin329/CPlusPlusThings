#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    vector<string> v;
    string s;

    while (cin >> s) {
        v.push_back(s);
    }

    for (auto &str : v) {
        for (auto &c : str) {
            c = toupper(c);
        }
    }

    for (auto i : v) {
        cout << i << endl;
    }
    return 0;
}