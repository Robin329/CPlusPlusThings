#include <cstring>
#include <iostream>
using namespace std;
struct Person { //职工基本信息的结构
    double salary;
    char *name;
};
class SalaryManaege {
private:
    Person *employ; //存放职工信息的数组
    int max;        //数组下标上界
    int n;          //数组中的实际职工人数
public:
    SalaryManaege(int Max = 0) {
        max = Max;
        n = 0;
        employ = new Person[max];
    }
    //返回引用特性是可以直接在放在左值，直接使用
    double &operator[](char *Name) { //重载[]，返回引用
        Person *p;
        for (p = employ; p < employ + n; p++)
            //如果存在处理
            if (strcmp(p->name, Name) == 0) return p->salary;
        //不存在情况处理
        p = employ + n++;
        p->name = new char[strlen(Name) + 1];
        strcpy(p->name, Name);
        p->salary = 0;
        return p->salary;
    }
    friend std::ostream &operator<<(std::ostream &os, const SalaryManaege &s) {
        for (int i = 0; i < s.n; i++) {
            os << "Name: " << s.employ[i].name << endl;
            os << "salary: " << s.employ[i].salary << endl;
        }

        return os;
    }

    void display() {
        cout << "n:" << n << endl;
        for (int i = 0; i < n; i++) cout << employ[i].name << "   " << employ[i].salary << endl;
    }
    ~SalaryManaege() { delete employ; }
};
int main() {
    SalaryManaege s(3);
    s[(char *)"zhangsan"] = 2188.88;
    s[(char *)"lisi"] = 1230.07;
    s[(char *)"wangwu"] = 3200.97;
    cout << s << endl;
    //    cout << "里斯\t" << s[(char *)"里斯"] << endl;
    //    cout << "王无\t" << s[(char *)"王无"] << endl;

    cout << "-------下为display的输出--------\n\n";
    int i = 0, a = 1;
    a = i++ + a;
    cout << "a:" << a << endl;

    s.display();

    return 0;
}
