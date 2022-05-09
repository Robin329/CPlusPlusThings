#include <cctype>

#include "std_lib_facilities.h"

static void skip_to_int() {
    if (cin.fail()) {
        cin.clear();
        char ch;

        while (cin >> ch) {
            if (isdigit(ch)) {
                cin.unget();
                return;
            } else {
                cout << "error, please input a number.\n";
            }
        }
    }
}

int main() {
    cout << "Please enter an interger in the range 1 to 10(inclusive):\n";
    int n = 0;
    while (true) {
        if (cin >> n) {
            if (1 <= n && n <= 10) break;
            cout << "Sorry " << n << "is not in the [1:10] range; please try again\n";
        } else {
            cout << "Sorry, that was not a number;please try again\n";
            skip_to_int();
        }
    }
    cout << "n:" << n << endl;
    return 0;
}