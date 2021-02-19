/**
 * @file derived_full.cpp
 * @brief 完整示例！抽象类由派生类继承实现！
 * @author 光城
 * @version v1
 * @date 2019-07-20
 */

#include <iostream>
#include <dbg.h>

using namespace std; 

class Base 
{ 
    int x; 
public:
    virtual void fun() = 0; 
    int getX() { return x; }
    static int factorial(int n) {return 0;};
    Base(){ cout << "Constructor: Base" << endl; }
    virtual ~Base(){ cout << "Destructor : Base" << endl; }

}; 

class Derived: public Base 
{ 
    int y; 
    public:
    Derived(){ cout << "Constructor: Derived" << endl; }
    ~Derived(){ cout << "Destructor : Derived" << endl;}
    void fun() { cout << "fun() called \n"; }  // 实现了fun()函数
// You can use "dbg(..)" in expressions:
    static int factorial(int n) {
        if (dbg(n <= 1)) {
            return dbg(1);
        } else {
            return dbg(n * factorial(n - 1));
        }
    }
  static string ll;
};


int main(void) 
{ 
    Derived d;
    d.fun();
    dbg("Derived::ll");
    std::string message = "hello";
    dbg(message);  // [example.cpp:15 (main)] message = "hello" (std::string)

    const int a = 2;
    const int b = dbg(3 * a) + 1;  // [example.cpp:18 (main)] 3 * a = 6 (int)

    std::vector<int> numbers{b, 13, 42};
    dbg(numbers);  // [example.cpp:21 (main)] numbers = {7, 13, 42} (size: 3) (std::vector<int>)

    dbg("this line is executed");  // [example.cpp:23 (main)] this line is executed

    Derived::factorial(4);
    return 0; 
} 
