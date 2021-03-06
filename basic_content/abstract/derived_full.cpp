/**
 * @file derived_full.cpp
 * @brief 完整示例！抽象类由派生类继承实现！
 * @author 光城
 * @version v1
 * @date 2019-07-20
 */

#include <iostream>
#include <vector>

using namespace std;

class Base {
  int x;

public:
  virtual void fun() = 0;
  int getX(int a) {
    cout << "getX(int a)" << endl;
    return a;
  }
  static int factorial(int n) { return 0; };
  Base() { cout << "Constructor: Base" << endl; }
  virtual ~Base() { cout << "Destructor : Base" << endl; }
};

class Derived : public Base {
  int y;

public:
  Derived() { cout << "Constructor: Derived" << endl; }
  int getX(int a, int b = 1) {
    cout << "getX(int a, int b) is called" << endl;
    return a + b;
  }
  ~Derived() { cout << "Destructor : Derived" << endl; }
  void fun() { cout << "fun() called \n"; } // 实现了fun()函数
  // You can use "dbg(..)" in expressions:
  static int factorial(int n) {
    if (n <= 1) {
      return 1;
    } else {
      return n * factorial(n - 1);
    }
  }
  static string ll;
};

int main(void) {
  Derived d;
  d.fun();
  return 0;
}
