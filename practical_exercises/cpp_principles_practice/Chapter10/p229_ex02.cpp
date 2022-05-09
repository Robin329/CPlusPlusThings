// -----------------------------------------------------------------------------
//
// C10 - Exercise 2
//
/* Write a program that creates a file of data in the form of the temperature Reading
   type defined in 10.5. For testing, fill the file with at least 50 "temperature
   readings". Call this program store_temps.cpp and the file it creates raw_temps.txt
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Reading {
    int hour;
    double temperature;
};

// -----------------------------------------------------------------------------

// check that the value being read in is a number
bool isNumber(string value) {
    size_t found = value.find_first_not_of("0123456789.");
    if (found != string::npos) {
        cout << value << " is not a number and will be skipped." << endl;
        return false;
    }

    return true;
}

// -----------------------------------------------------------------------------

// read in numbers from file (I'm being lazy as I cannot be bothered to type in 50 readings,
// so I'm reading in from a file that I copypasta'd)
vector<Reading> readIn(string filename) {
    vector<Reading> readings;
    if (ifstream inFile{filename}) {
        string hour, temp;
        while (!inFile.eof()) {
            inFile >> hour >> temp;
            if (isNumber(hour) && isNumber(temp)) readings.push_back(Reading{stoi(hour), stod(temp)});
        }
    } else
        cout << "Error opening file " << filename << endl;
    return readings;
}

// -----------------------------------------------------------------------------

// create a file using the data from readIn
void createFile(string filename) {
    if (ofstream outFile{filename}) {
        vector<Reading> readings =
                readIn(FileSystem::getPath("practical_exercises/cpp_principles_practice/Chapter10/res/temps.txt").c_str());
        for (Reading r : readings) outFile << r.hour << " " << r.temperature << endl;
        outFile.close();
    } else
        cout << "Error opening file " << filename << endl;
}

// -----------------------------------------------------------------------------

// create a file by asking for info
void createFile2(string filename) {
    if (ofstream outFile{filename}) {
        string hour, temp;
        cout << "Please enter hours and temperatures in the following format: hour24 temperatureF (00 10.1)" << endl;
        cout << "Enter ctrl + z to stop." << endl;
        while (cin >> hour) {
            while (!isNumber(hour)) {
                cout << "\nTry again: ";
                cin >> hour;
            }
            cin >> temp;
            while (!isNumber(temp)) {
                cout << "\nTry again: ";
                cin >> temp;
            }
            outFile << hour << " " << temp << endl;
        }
    } else
        cout << "Error opening file " << filename << endl;
}

// -----------------------------------------------------------------------------

int main() {
    string filename =
            FileSystem::getPath("practical_exercises/cpp_principles_practice/Chapter10/res/raw_temps.txt").c_str();
    // createFile(filename);
    createFile2(filename);

    char ch;
    cin >> ch;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------