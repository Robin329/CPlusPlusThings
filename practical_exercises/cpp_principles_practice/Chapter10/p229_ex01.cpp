// -----------------------------------------------------------------------------
//
// C10 - Exercise 1
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// check that the value being read in is a number
bool isNumber(string value) {
    size_t found = value.find_first_not_of("0123456789");
    if (found != string::npos) {
        cout << value << " is not a number and will be skipped." << endl;
        return false;
    }

    return true;
}

// -----------------------------------------------------------------------------

// read in numbers from file
vector<int> readIn(string filename) {
    vector<int> integers;
    if (ifstream inFile{filename}) {
        string temp;
        while (!inFile.eof()) {
            inFile >> temp;
            if (isNumber(temp)) integers.push_back(stoi(temp));
        }
    } else
        cout << "Error opening file " << filename << endl;

    return integers;
}

// -----------------------------------------------------------------------------

// create a file with whitespace separated integers
void createFile(string filename) {
    if (ofstream outFile{filename, std::ios::out | std::ios::app}) {
        string temp;
        cout << "Please enter a list of whitespace separated integers: \n>>";
        getline(cin, temp);
        outFile << temp;
        outFile.close();
    } else
        cout << "Error opening file " << filename << endl;
}

// -----------------------------------------------------------------------------

// add numbers together
int sumOfIntegers(const vector<int>& v) {
    int sum = 0;
    for (int i : v) sum += i;
    return sum;
}

// -----------------------------------------------------------------------------

int main() {
    string filename = FileSystem::getPath("practical_exercises/cpp_principles_practice/Chapter10/res/integers.txt").c_str();
    createFile(filename);

    vector<int> v_integers = readIn(filename);
    int sum = sumOfIntegers(v_integers);

    cout << "Integers: ";
    for (int i : v_integers) cout << i << " ";

    cout << "\nSum: " << sum << endl;

    char ch;
    cin >> ch;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
