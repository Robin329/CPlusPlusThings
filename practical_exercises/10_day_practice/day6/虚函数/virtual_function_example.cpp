
// Eg7-1.cpp
//基类指针或引用指向派生类对象时,虚函数与非虚函数区别:
//声明Employee的print为虚函数，则可访问到Manager的print函数，非虚函数，则只能访问到Employee的print
#include <iostream>
#include <string>
using namespace std;
class Employee {
public:
    Employee(string name, string id);
    string getName();
    string getId();
    float getSalary();
    virtual void print();

private:
    string Name;
    string Id;
};
Employee::Employee(string name, string id) {
    Name = name;
    Id = id;
}
string Employee::getName() {
    return Name;
}
string Employee::getId() {
    return Id;
}
float Employee::getSalary() {
    return 0.0;
}
void Employee::print() {
    cout << "name:" << Name << "\t"
         << "num:" << Id << endl;
}

class Manager : public Employee {
public:
    Manager(string name, string id, float s = 0.0) : Employee(name, id) { weeklySalary = s; }
    void setSalary(float s) { weeklySalary = s; } //设置经理的周薪
    float getSalary() { return weeklySalary; }    //获取经理的周薪
    void print() {                                //打印经理姓名、身份证、周薪
        cout << "jingli:" << getName() << "\t\t number:" << getId()
             << "\t\t weekgongzi: " << getSalary() << endl;
    }

private:
    float weeklySalary; //周薪
};

/*
不论哪种赋值方式，都只能通过基类对象（或基类对象的指针或引用）访问到派生类对象从基类中继承到的成员，
不能借此访问派生类定义的成员。而虚函数使得可以通过基类对象的指针或引用访问派生类定义的成员。
*/
int main() {
    Employee e("Xiaomi", "NO0001"), *pM;
    Manager m("xiaowang", "NO0002", 128);
    m.print();
    pM = &m;
    pM->print();
    Employee &rM = m;
    rM.print();
    //    system("pause");
    return 0;
}
// Virtual关键字其实质是告知编译系统，被指定为virtual的函数采用动态联编的形式编译。
