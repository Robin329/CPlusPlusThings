// -----------------------------------------------------------------------------
//
// C10 - Drill 5 + 6
/*
    Close the ofstream and then open an ifstream for mydata.txt. Read the data
    from mydata.txt and store it in a new vector called processed_points. Print
    the data elements from both vectors.

    I've done this exercise 3 times, and all the previous times I changed it so
    I didn't have to parse the weird file format. This time I challenged myself
    to parse it and I learnt a few things. Substr is extremely useful, wish I'd
    done this sooner.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Point {
    double x, y;
};

// -----------------------------------------------------------------------------

double getNumber() {
    double d;
    // clears up cin if NaN was entered, taken from http://www.cplusplus.com/forum/beginner/21595/
    while (!(cin >> d)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
    }
    return d;
}

// -----------------------------------------------------------------------------

void getPoints(int loop, vector<Point>& points) {
    Point p;
    for (int i = 0; i < loop; ++i) {
        cout << "Please enter " << loop << " pair(s) of points." << endl;
        cout << "Points " << i + 1 << endl;
        cout << "X: ";
        p.x = getNumber();
        cout << "Y: ";
        p.y = getNumber();
        points.push_back(p);
    }
}

// -----------------------------------------------------------------------------

// please be aware that ofstream << has only 6 digits of precision, so it will truncate
// if a number like 1.23456789 is entered. I have decided to not increase the precision.
// however the program will print that somethings wrong when comparing vectors.
void outputPointsToFile(string filename, const vector<Point>& points) {
    if (ofstream outFile{filename}) {
        for (Point p : points) outFile << '(' << p.x << ',' << p.y << ")\n";
        outFile.close();
    } else {
        cout << "Error, can't open output file " << filename << endl;
    }
}

// -----------------------------------------------------------------------------

void inputPointsToFile(string filename, vector<Point>& points) {
    string line, num1, num2;
    Point p;
    if (ifstream inFile{filename}) {
        while (getline(inFile, line)) {
            // find where the comma is
            size_t found = line.find_first_of(",");

            // get first number (from after '(' until ',' )
            num1 = line.substr(1, found - 1);
            // get second number (from after ',' until ')' )
            num2 = line.substr(found + 1, line.size() - 2);

            p.x = stod(num1);
            p.y = stod(num2);
            points.push_back(p);
        }
    } else
        cout << "Error, can't open input file " << filename << endl;
}

// -----------------------------------------------------------------------------

int main() {
    vector<Point> v_originalPoints;
    vector<Point> v_processedPoints;
    getPoints(2, v_originalPoints);
    constexpr const char* path = "practical_exercises/cpp_principles_practice/Chapter10/res/mydata.txt";
    outputPointsToFile(FileSystem::getPath(path).c_str(), v_originalPoints);
    inputPointsToFile(FileSystem::getPath(path).c_str(), v_processedPoints);

    // drill 6
    cout << "[original Points]----------------------------------------" << endl;
    for (uint32_t i = 0; i < v_originalPoints.size(); ++i)
        cout << v_originalPoints[i].x << ", " << v_originalPoints[i].y << endl;

    cout << "[processed Points]----------------------------------------" << endl;
    for (uint32_t i = 0; i < v_processedPoints.size(); ++i)
        cout << v_processedPoints[i].x << ", " << v_processedPoints[i].y << endl;

    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
