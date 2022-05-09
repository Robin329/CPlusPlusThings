// -----------------------------------------------------------------------------
//
// C10 - Exercise 3
//
/* Write a program that reads the data from raw_temps.txt created in exercise 2
   into a vector and then calculates the mean and median temperatures in your
   data set.
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
        inFile.close();
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
        outFile.close();
    } else
        cout << "Error opening file " << filename << endl;
}

// -----------------------------------------------------------------------------

bool compareByTemperature(const Reading& r, const Reading& r2) {
    return r.temperature < r2.temperature;
}

// calculate mean and median temps
void meanMedianTemps(const vector<Reading>& readings, double& mean, double& median) {
    vector<Reading> v = readings;
    double sum = 0;
    for (Reading r : v) sum += r.temperature;
    mean += sum / v.size();

    // sort readings by temp
    sort(v.begin(), v.end(), compareByTemperature);

    // return middle value, if no middle value, return middle of middle pair
    if (v.size() == 1)
        mean = median = v[0].temperature;
    else {
        int middle = (v.size() / 2) - 1;
        if (v.size() % 2 == 0)
            // it's even - harder way
            median = v[middle].temperature + ((v[middle + 1].temperature - v[middle].temperature) / 2);
        else
            // it's odd - easy way
            median = v[middle + 1].temperature;
    }
}

// -----------------------------------------------------------------------------

int main() {
    string filename = FileSystem::getPath("practical_exercises/cpp_principles_practice/Chapter10/res/temps.txt").c_str();
    vector<Reading> v_readings = readIn(filename);
    double mean(0), median(0);
    meanMedianTemps(v_readings, mean, median);

    cout << "Mean: " << mean << "\nMedian: " << median << endl;

    char ch;
    cin >> ch;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
