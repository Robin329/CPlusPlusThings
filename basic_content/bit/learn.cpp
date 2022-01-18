#include <string.h>

#include <iostream>

using namespace std;
struct stuff {
    unsigned int field1 : 30;
    unsigned int : 2;
    unsigned int field2 : 4;
    unsigned int : 0;
    unsigned int field3 : 3;
};

float f[5] = {2.0, 3.2};
double d[3]{1.2, 3.1, 4.3};

void foo(void) {
    float f1[5] = {3.0, 4.3};
    char name[10];
    cout << "f1[]" << f1[0] << " "
         << " " << f1[1] << " " << f1[3] << endl;
    cin >> name;
    cout << "name is :" << name << endl;
}

void func(void) {
    string str[]{"robin", "hello", "world"};
    char buf[32];
    for (int i = 0; i < sizeof(str) / sizeof(string); i++) {
        //    cout << " sizeof buf :" << sizeof(buf) << endl;
        memset(buf, 0, sizeof(buf));
        snprintf(buf, 32, "%-5s", str[i].c_str());
        cout << "buf is :" << buf << endl;
    }
}

int main() {
    struct stuff s = {1, 3, 5};
    cout << s.field1 << endl;
    cout << s.field2 << endl;
    cout << s.field3 << endl;
    cout << sizeof(s) << endl;

    cout << "f[]:" << f[1] << " " << f[3] << endl;

    foo();
    func();
    return 0;
}
