//
// Created by renbin jiang on 2021/7/4.
//
#include <iostream>

using namespace std;

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    //  circle(string name = nullptr) : name_(move(name)) {
    //    cout << "name: " << name << "name_: " << name_ << endl;
    //  }
    string name_;
    ~circle() { puts("~circle()"); }
};

void foo(const shape &) {
    puts("foo(const shape&)");
}

void foo(shape &&) {
    puts("foo(shape&&)");
}

void bar(const shape &s) {
    puts("bar(const shape&)");
    foo(s);
}

void bar(shape &&s) {
    puts("bar(shape&&)");
    foo(s);
}

int main() {
    bar(circle());
    shape s;
    foo(move(s));
    foo(static_cast<shape &&>(s));
}