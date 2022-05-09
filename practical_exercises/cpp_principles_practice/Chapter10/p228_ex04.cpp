// -----------------------------------------------------------------------------
//
// C10 - Drill 4
/*
    Open an ofstream and output each point to a file named mydata.txt.
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

void outputPointsToFile(string filename, const vector<Point>& points) {
    if (ofstream outFile{filename})
        for (Point p : points) outFile << '(' << p.x << ',' << p.y << ")\n";
    else
        cout << "Error, can't open output file " << filename << endl;
}

// -----------------------------------------------------------------------------

int main() {
    vector<Point> v_originalPoints;
    getPoints(7, v_originalPoints);
    outputPointsToFile("mydata.txt", v_originalPoints);

    cout << "-----------------------------------------------------------------------------" << endl;
    for (uint32_t i = 0; i < v_originalPoints.size(); ++i)
        cout << v_originalPoints[i].x << ", " << v_originalPoints[i].y << endl;

    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
