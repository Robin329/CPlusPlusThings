
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Person {
public:
    Person() {}
    Person(char *name, char *id, int math, int chinese, int english) {
        strcpy(Name, name);
        strcpy(Id, id);
        Math = math;
        Chinese = chinese;
        English = english;
        Sum = Math + Chinese + English;
    }

    void display() {
        cout << Name << "\t" << Id << "\t" << Math << "\t" << Chinese << "\t" << English << "\t"
             << Sum << endl;
    }

private:
    char Name[20];
    char Id[20];
    int Math;
    int Chinese;
    int English;
    int Sum;
};

int main(int argc, char const *argv[]) {
    char ch;
    char Name[20], Id[20];
    int Math, Chinese, English;
    fstream ioFile;
    ioFile.open("/Users/renbinjiang/workspace/project/c_c++/CPlusPlusThings/practical_exercises/"
                "\"\n"
                "                \"key_exercises/per.dat",
                ios::out | ios::app);
    cout << "---------Create student profile information----------\n";
    do {
        cout << "Please enter your name:";
        cin >> Name;
        cout << "Please enter identification number:";
        cin >> Id;
        cout << "Please enter your Math score:";
        cin >> Math;
        cout << "Please enter your Chinese score:";
        cin >> Chinese;
        cout << "Please enter your English score:";
        cin >> English;
        Person per(Name, Id, Math, Chinese, English);
        ioFile.write((char *)&per, sizeof(per));
        cout << "Do you want to continue to file?(Y/y)  ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    ioFile.close();
    ioFile.open("/Users/renbinjiang/workspace/project/c_c++/CPlusPlusThings/practical_exercises/"
                "key_exercises/per.dat",
                ios::in);
    Person p;
    ioFile.read((char *)&p, sizeof(p));
    vector<Person> v;
    vector<Person>::iterator vt;
    while (!ioFile.eof()) {
        v.push_back(p);
        ioFile.read((char *)&p, sizeof(p));
    }
    ioFile.close();
    cout << "---------output file information-----------" << endl;
    for (vt = v.begin(); vt != v.end(); vt++) {
        (*vt).display();
    }
    system("pause");
    return 0;
}
