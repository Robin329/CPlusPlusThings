#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    vector<string> scores = {"F", "D", "C", "B", "A", "A++"};

    int grade = 0;
    while (cin >> grade) {
        string lettergrade = grade < 60 ? scores[0] : scores[(grade - 50) / 10];
        lettergrade += (grade == 100 || grade < 60) ? ""
                : (grade % 10 > 7)                  ? "+"
                : (grade % 10 < 3)                  ? "-"
                                                    : "";
        cout << lettergrade << endl;
    }

    return 0;
}