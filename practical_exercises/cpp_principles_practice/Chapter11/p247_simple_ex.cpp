//
// Created by renbin jiang on 2022/5/15.
//
#include "std_lib_facilities.h"

Time *Time::m_stTime = nullptr;
int main() {
    int birth_year{};

    cout << "Please input your's birth year:";
    cin >> birth_year;
    cout << "birth year:" << '\t' << birth_year << endl;
    // ex02
    cout << "birth year:" << '\t' << std::showbase << std::hex << birth_year << endl << std::dec;
    cout << "birth year:" << '\t' << std::oct << birth_year << endl;

    cout << "Your years old:" << std::dec << base::Time::getTime()->getYear() - birth_year << endl;
    
    cout << "Output:\n";
    cout << general << 1234567.89 << endl;
    cout << fixed << 1234567.89 << endl;
    cout << scientific << 1234567.89 << endl;
    return 0;
}