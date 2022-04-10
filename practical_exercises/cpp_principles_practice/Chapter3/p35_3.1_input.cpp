//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Please input your first name:\n";
    string first_name;
    cin >> first_name;
    cout << "Hello, " << first_name << endl;
    
    cout << endl;
    
    cout << "Please input your first name and age:\n";
    string name;
    cin >> name;
    int age;
    cin >> age;
    cout << "Hello, " << name << "(age " << age << ")\n";
    return 0;
}