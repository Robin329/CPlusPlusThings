//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {

    
    cout << "Please input your first name and age:\n";
    string name("???");
    int age = -1;
    cin >> name >> age;
    cout << "Hello, " << name << "(age " << age << ")\n";
    
    cout << endl;
    cout << endl;
    cout << "Please input your first and second names:\n";
    string first;
    string second;
    int age1;
    cin >> first >> second;
    cin >> age1;
    age1 *=12;
    cout << "Hello, " << first << " " << second << " (age " << age1 << ") " << endl;
    
    return 0;
}