//
// Created by renbin jiang on 2021/8/28.
//
#include <iostream>

using namespace std;

double betsy(int lns) {
    return 0.05 * lns;
}

double pam(int lns) {
    return 0.03 * lns + 0.0004 * lns * lns;
}

void estimate(int lines, double (*pf)(int)) {
    cout << lines << " line will take ";
    cout << (*pf)(lines) << " hour(s)\n";
}

int g = 0;
void trans(int tmp, int &value) {
    cout << "value:" << value << endl;
    cout << "tmp:" << tmp << endl;
    value = 2;
}
int main() {
    //  int code;
    //  cout << "How many lines of code do you need? ";
    //  cin >> code;
    //  cout << "Here's Betsy's estimate:\n";
    //  estimate(code, betsy);
    //  cout << "Here's Pam's estimate:\n";
    //  estimate(code, pam);
    trans(g, g);
    cout << "-->g:" << g << endl;
    return 0;
}