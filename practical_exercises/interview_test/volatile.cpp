//
// Created by renbin jiang on 2022/3/21.
//
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

// 当表达式中存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型。
void foo(void) {
    unsigned int a = 6;
    int b = -20;
    printf("a + b = %u\n", (a + b));
    (a + b > 6) ? puts("> 6") : puts("<= 6");
}

int main() {
    volatile int i = 10;
    int a = i;

    printf("i = %d\n", a);

    int b = i;
    printf("i = %d\n", b);
    std::cout << "int = " << sizeof(int) <<endl;
    
    std::cout << "unsigned int = " << sizeof(unsigned int) <<endl;
    foo();
    string str("robin");
    std::cout  << "str:" << str << endl;
    return 0;
}