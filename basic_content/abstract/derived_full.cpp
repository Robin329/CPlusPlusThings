/**
 * @file derived_full.cpp
 * @brief 完整示例！抽象类由派生类继承实现！
 * @author 光城
 * @version v1
 * @date 2019-07-20
 */

#include <iostream>
#include <vector>
#include <complex>

using namespace std;

class Base {
    int x;

public:
    
    //    virtual void fun();
    int getX(int a) {
        cout << "getX(int a)" << endl;
        return a;
    }
    static int factorial(int n) { return 0; };
    Base(double r = 0, double i = 0) : re(r), im(i) { cout << "Constructor: Base" << endl; }
    Base() : re(0), im(0) { cout << "Constructor: Base2" << endl; }
    virtual ~Base() { cout << "Destructor : Base" << endl; }
    double real() const { return re; }
    double imag() const { return im; }

private:
    double re, im;
};

// class Derived : public Base {
//    int y;
//
// public:
//    Derived() { cout << "Constructor: Derived" << endl; }
//    int getX(int a, int b = 1) {
//        cout << "getX(int a, int b) is called" << endl;
//        return a + b;
//    }
//    ~Derived() { cout << "Destructor : Derived" << endl; }
//    void fun() { cout << "fun() called \n"; } // 实现了fun()函数
//    // You can use "dbg(..)" in expressions:
//    static int factorial(int n) {
//        if (n <= 1) {
//            return 1;
//        } else {
//            return n * factorial(n - 1);
//        }
//    }
//    static string ll;
//};

int main(void) {
    //    Derived d;
    //    d.fun();
    //    static constexpr const char *str[] = {"abc", "bda", "ad3", "qer"};
    //    for (const auto &c : str) {
    //        cout << "c:" << c << endl;
    //    }
    const Base b(1.1);
    cout << b.real() << endl;
    cout << b.imag() << endl;
    return 0;
}
