#include <cstring>
#include <iostream>

using namespace std;

class Person {
public:
    typedef enum { BOY = 0, GIRL } SexType;

    Person(char *n, int a, SexType s) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        age = a;
        sex = s;
    }

    int get_age() const { return this->age; }

    Person &add_age(int a) {
        age += a;
        return *this;
    }

    ~Person() { delete[] name; }

private:
    char *name;
    int age;
    SexType sex;
};

int main() {
    Person p((char *)("zhangsan"), 20, Person::BOY);
    cout << p.get_age() << endl;
    //    Person p1("lisi", 1, Person::GIRL);
    //    Person p2 = p1.add_age(2);
    p.add_age(3);
    cout << p.get_age() << endl;
    return 0;
}
