/*
 ��һ������Ա��Sales�������ݳ�Ա������name�����֤��id������age��
 ��������/��������ʵ�ֶ�Sales�����ݳ�Ա������������
*/
#include <string.h>

#include <iostream>
using namespace std;
class Sales {
private:
    char name[10];
    char id[18];
    int age;

public:
    Sales(char *Name, char *ID, int Age);

    friend Sales &operator<<(ostream &os, Sales &s); //������������
    friend Sales &operator>>(istream &is, Sales &s); //�������������
};

Sales::Sales(char *Name, char *ID, int Age) {
    strcpy(name, Name);
    strcpy(id, ID);
    age = Age;
}

Sales &operator<<(ostream &os, Sales &s) {
    os << s.name << "\t"; //�������
    os << s.id << "\t";   //������֤��
    os << s.age << endl;  //�������
    return s;
}

Sales &operator>>(istream &is, Sales &s) {
    cout << "Please name,num,years old" << endl;
    is >> s.name >> s.id >> s.age;
    return s;
}

int main() {
    Sales s1((char *)"dukang", (char *)"214198012111711", 40); // L1
    cout << s1;                                                // L2
    cout << endl;                                              // L3
    cin >> s1;                                                 // L4
    cout << s1;                                                // L5

    return 0;
}
