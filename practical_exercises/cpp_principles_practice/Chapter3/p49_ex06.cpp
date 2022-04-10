//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    int x,y,z;
    cout << "Please input three numbers:\n";
    cin >> x >> y >> z;
    int min = std::min({x, y, z});
    int max = std::max({x, y, z});
    cout << min << ",";
    
    cout << (x + y + z) - max - min << ",";
    cout << max ;
    return 0;
}