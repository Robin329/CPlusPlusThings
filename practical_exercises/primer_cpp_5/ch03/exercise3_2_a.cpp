#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

int main() {
    string s;
    while (getline(cin, s)) {
        cout << s << endl;
    }
    return 0;
}