#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

int main() {
    ifstream ifs("E:/code/cpp_primer_answer/Cpp_Primer_Answers/data/books.txt");
    if (!ifs) {
        cerr << "No data?" << endl;
        return -1;
    }

    vector<string> vecLine;
    string line;
    while (getline(ifs, line)) vecLine.push_back(line);

    for (auto &s : vecLine) {
        istringstream iss(s);
        string word;
        while (iss >> word) cout << word << ", ";
        cout << endl;
    }

    return 0;
}