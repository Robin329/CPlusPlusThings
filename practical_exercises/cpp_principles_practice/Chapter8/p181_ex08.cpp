//
// Created by renbin jiang on 2022/5/6.
//
#include "std_lib_facilities.h"

#pragma pack(4)//表示它后面的代码都按照n个字节对齐
struct fooo {
    int a;
    char *c;
};
#pragma pack()//取消按照n个字节对齐，是对#pragma pack(n)的一个反向操作
static struct fooo *foo(void) {
    struct fooo *aa;
    char *str = "robin";
    aa = (fooo*)malloc(sizeof(fooo));
    aa->c = str;
    aa->a = 5;
    return aa;
}

int main() {
    struct fooo *f=foo();
    cout << randint(1, 100) << endl;
    cout << "foo: a = " << f->a << endl;
    cout << "foo: c = " << f->c << endl;
    if (f) {
        free(f);
    }
    cout << "sizeof fooo:" << sizeof(fooo) << endl;
    cout << "sizeof *f:" << sizeof(*f) << endl;
    cout << "sizeof f->a:" << sizeof(f->a) << endl;
    cout << "sizeof f->c:" << sizeof(f->c) << endl;
    cout << "sizeof f:" << sizeof(f) << endl;
    return 0;
}