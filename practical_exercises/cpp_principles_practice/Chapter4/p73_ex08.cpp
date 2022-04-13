//
// Created by renbin jiang on 2022/4/14.
//
#include "std_lib_facilities.h"

int main()
{
    // Number of rice per square
    int square = 1;
    long long rice = 1;
    long long target = 0;
    
    cout << "How many grains do you want?\n";
    cin >> target;
    
    while (rice < target) {
        rice *= 2;
        square += 1;
    }
    
    cout << "# of grains of rice: " << rice
         << " chess square #: " << square << '\n';
}