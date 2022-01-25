// 12-6.cpp
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
    fstream ioFile;
    ioFile.open("./a.dat", ios::out);
    ioFile << "zhangsan"
           << "  " << 76 << " " << 98 << " " << 67 << endl; // L3
    ioFile << "LiSi"
           << "  " << 89 << " " << 70 << " " << 60 << endl;
    ioFile << "Wangshi"
           << "  " << 91 << " " << 88 << " " << 77 << endl;
    ioFile << "huanger"
           << "  " << 62 << " " << 81 << " " << 75 << endl;
    ioFile << "liuliu"
           << "  " << 90 << " " << 78 << " " << 67 << endl;
    ioFile.close();
    ioFile.open("./a.dat", ios::in | ios::binary);
    char name[10];
    int chinese, math, computer;
    cout << "Name\t"
         << "English\t"
         << "Math\t"
         << "Computor\t"
         << "Total" << endl;
    ioFile >> name;
    while (!ioFile.eof()) {
        ioFile >> chinese >> math >> computer;
        cout << name << "\t" << chinese << "\t" << math << "\t" << computer << "\t"
             << chinese + math + computer << endl;
        ioFile >> name;
    }
    ioFile.close();
    //    system("pause");
    return 0;
}
