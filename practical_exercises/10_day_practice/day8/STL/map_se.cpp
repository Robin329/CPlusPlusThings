#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
    string name[] = {"ZhangSan", "Lisi", "WangMaZi"};
    double salary[] = {1200, 2000, 1450};
    map<string, double> sal;
    map<string, double>::iterator p;
    for (int i = 0; i < 3; i++) {
        sal.insert(make_pair(name[i], salary[i]));
    }
    sal["tom"] = 6156;
    sal["bob"] = 5999;
    for (p = sal.begin(); p != sal.end(); p++) {
        cout << p->first << "\t" << p->second << endl;
    }
    string person;
    cout << "Enter the name of the person looking for:";
    cin >> person;
    int flag = 1;
    for (p = sal.begin(); p != sal.end(); p++)
        if (p->first == person) {
            cout << p->second << endl;
            flag = 0;
        }
    if (flag) cout << "No matching results were found!" << endl;

    cout << "Enter the name of the person to delete:";
    cin >> person;
    map<string, double>::iterator it;
    it = sal.find(person);
    if (it != sal.end()) {
        cout << "Find success:" << (*it).first << ":" << (*it).second << endl;
        sal.erase(it);
        cout << "successfully deleted!" << endl;
    }
    cout << "The result after deletion is:" << endl;
    for (p = sal.begin(); p != sal.end(); p++) {
        cout << p->first << p->second << endl;
    }

    //    system("pause");
    return 0;
}
