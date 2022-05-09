// -----------------------------------------------------------------------------
//
// C10 - Exercise 4
//
/* Modify the program from exercise 2 to include a temperature suffix C for Celsius
   or F for Fahrenheit. Then modify the program in exercise 3 to test each temperature,
   converting the Celsius readings to Fahrenheit before putting them into the vector.

   I combined exercise 2 and 3 when doing them, so this will be one program.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Reading {
    // I've swapped this round due to struct padding. It's not really necessary in
    // this exercise however it's something I think about these days
    double temperature;
    int hour;
    char tempSuffix;
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

// read in numbers from file
vector<Reading> readIn(string filename) {
    vector<Reading> readings;
    if (ifstream inFile{filename}) {
        string hour, temp;
        char suffix;
        while (inFile >> hour) {
            inFile >> temp;
            suffix = temp[temp.size() - 1];
            temp.pop_back(); // remove last character of string
            if (isNumber(hour) && isNumber(temp)) {
                double fTemp = stod(temp);
                if (suffix == 'c') fTemp = (stod(temp) * 9 / 5.0f) + 32;
                readings.push_back(Reading{fTemp, stoi(hour), 'f'});
            }
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
        string hour, temp, suffix;
        cout << "Please enter hours and temperatures in the following format: hour24 temperature Fc (00 10.1 c or 22 "
                "32.4 F)"
             << endl;
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
            cin >> suffix;
            while (suffix != "c" && suffix != "f") {
                cout << "\nCelsius (c) or Fahrenheit(F) only. Try again: ";
                cin >> suffix;
            }
            outFile << hour << " " << temp << suffix << endl;
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
    string filename =
            FileSystem::getPath("practical_exercises/cpp_principles_practice/Chapter10/res/temps.txt").c_str();

    // createFile2(filename);
    vector<Reading> v_readings = readIn(filename);

    for (Reading r : v_readings) cout << r.hour << " " << r.temperature << r.tempSuffix << endl;

    double mean(0), median(0);
    meanMedianTemps(v_readings, mean, median);

    cout << "Mean: " << mean << "\nMedian: " << median << endl;

    char ch;
    cin >> ch;
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
