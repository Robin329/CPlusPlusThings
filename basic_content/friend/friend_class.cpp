#include <iostream>

using namespace std;

class A {
public:
    A(int _a) : a(_a) {
        cout << "A(int _a)" << endl;
        cout << "a is:" << a << endl;
    };

    friend class B;

private:
    int a = 1;
};

class B {
public:
    int getb(A ca) { return ca.a; };
};

int main() {
    A a(0);
    B b;
    cout << b.getb(a) << endl;
    return 0;
}
