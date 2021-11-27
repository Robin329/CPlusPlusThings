//
// Created by renbin jiang on 2021/4/29.
//
#include <array>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char **argv) {
    cout << "1.------------------------" << endl;
    ofstream outFile;
    outFile.open("test.txt");
    outFile << fixed;
    outFile.precision(2);
    outFile.setf(ios_base::showpoint);
    outFile << "   robin add:"
            << "\n";
    outFile << "           1:"
            << "\n";
    outFile << "aaabbbbcccc" << endl;
    outFile.close();

    cout << "2.------------------------" << endl;
    ifstream ifFile;
    ifFile.open("demo.txt");
    if (!ifFile.is_open()) {
        return EXIT_FAILURE;
    }
    int count = 0;
    unsigned int value;
    ifFile >> value;
    while (ifFile.good()) {
        cout << "count :" << count << "value:" << value << endl;

        count += value;
        ifFile >> value;
    }
    if (ifFile.eof()) {
        cout << "End of file readched.\n" << endl;
    }
    cout << "value :" << value << endl;
    ifFile.close();
    return 0;
}