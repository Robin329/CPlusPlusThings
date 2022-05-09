// -----------------------------------------------------------------------------
//
// C10 - Drill 2 + 3
/*
    Using the code and discussion in 10.4, prompt the user to input seven (x,y)
    pairs. As the data is entered, store it in a vector of Points called original
    points. Print the data in original_points to see what it looks like.
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

int main() {
    vector<Point> v_originalPoints;
    getPoints(7, v_originalPoints);

    // Drill 3 - print the points
    cout << "-----------------------------------------------------------------------------" << endl;
    for (uint32_t i = 0; i < v_originalPoints.size(); ++i)
        cout << "[" << i << "] = " << v_originalPoints[i].x << ", " << v_originalPoints[i].y << endl;

    char ch;
    cin >> ch;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
