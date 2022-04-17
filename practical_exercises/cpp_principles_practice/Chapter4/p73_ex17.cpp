//
// Created by renbin jiang on 2022/4/16.
//
#include "std_lib_facilities.h"

int main() {
    // Program
    string smallest = "";
    string largest = "";
    string mode = "";
    string test_mode = "";

    int mode_count = 0;
    int test_mode_count = 0;

    vector<string> input_set;

    string input;
    cout << "Fill the set with.. strings!\n";
    while (cin >> input) {
        input_set.push_back(input);

        if (smallest == "" && largest == "") {
            smallest = input;
            largest = input;
        } else {
            if (input < smallest) {
                smallest = input;
                cout << "New smallest:" << smallest << endl;
            }

            if (input > largest) {
                largest = input;
                cout << "New largest:" << largest << endl;
            }
        }
    }

    sort(input_set);

    // Compute
    for (int i = 0; i < input_set.size(); ++i)
        if (i == 0 || input_set[i - 1] == input_set[i]) {
            test_mode = input_set[i];
            ++test_mode_count;
        } else {
            if (test_mode_count > mode_count) {
                mode = test_mode;
                mode_count = test_mode_count;
            }
            test_mode_count = 1;
        }

    // Print
    for (string str : input_set) cout << str << " ";

    cout << '\n';

    cout << "The smallest of this set is: " << smallest << '\n'
         << "The largest of this set is: " << largest << '\n';

    if (mode_count > 1)
        cout << "The mode of this set is: " << mode << " -> " << mode_count << '\n';
    else
        cout << "There were no repeated values." << '\n';
}
