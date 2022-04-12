//
// Created by renbin jiang on 2022/4/12.
//
#include "std_lib_facilities.h"

int main() {
    vector<string> philosopher(3);
    vector<int> vd(1000, 2); // vector of 1000 int initialises to 2
    for (int i = 0;i < vd.size();i++) {
//        cout << " vd[" << i << "] = " << vd[i] << endl;
    }
    vector<double> temps;
    double temp;
    cout << "Please input temps:\n";
    while(cin >> temp) {
        temps.push_back(temp);
    }
    double sum = {};
    for (int i = 0; i < temps.size();++i) sum += temps[i];
    cout << "Average temps is " << sum / temps.size() << endl;
    
    sort(temps.begin(), temps.end());
    cout << "temps[0] = " << temps[0] << endl;
    cout << "Medium temps is " << temps[temps.size()/2] << endl;
    return 0;
}