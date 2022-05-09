//
// Created by renbin jiang on 2022/5/9.
//
#include <fstream>

#include "std_lib_facilities.h"

struct Reading {
    int hour;           // a temperature reading
    double temperature; // hour after midnight [0:23]
    Reading(int h, double t) : hour(h), temperature(t) {
        cout << "hour:" << hour << " temperature:" << temperature << endl;
    }
};

int main() {
    cout << "Please enter input file name:";
    string name;
    cin >> name;
    ifstream ist(name.c_str());
    if (!ist) error("can't open input file ", name);
    // cout << "Please enter name of output file:";
    // cin >> name;
    // ofstream ost(name.c_str());
    // if (!ost) error("can't open output file ", name);
    // ost.close();

    Vector<Reading> temps;
    int hour;
    double temperature;
    while (ist >> hour >> temperature) {
        if (hour < 0 || 23 < hour) error("hour out of range");
        temps.push_back(Reading(hour, temperature));
    }
    ist.close();
    return 0;
}