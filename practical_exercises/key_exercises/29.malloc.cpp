//
// Created by renbin jiang on 2022/6/5.
//
#include <iostream>
#include <string.h>
using namespace std;

void getMemory1(char **p, int num)
{
	*p = (char *)malloc(num * sizeof(char));
}

char *getMemory2(char *p, int num)
{
	p = (char *)malloc(num * sizeof(char));
	return p;
}

char *func(char *p1, char *p2) {
    int i = 0;
    i = strcmp(p1, p2);
    if (0 == i) {
        cout << "p1 == p2\n";
        return p1;
    } else {
        cout << "p1 != p2\n";
        return p2;
    }

}


char *fun1(char *p) {
    cout << __FUNCTION__  <<" p -> " << p<< endl;
    return p;
}

char *fun2(char *p) {
    cout << __FUNCTION__  <<" p -> " << p << endl;

    return p;
}

char *fun3(char *p) {
    cout << __FUNCTION__  <<" p -> " << p<< endl;
    return p;
}
int main() {
    char *str = NULL;
    getMemory1(&str, 10);
    strcpy(str,"robin");
    cout << "str:" << str << endl;
    free(str);
    cout << "str:" << str << endl; // error
    // -------------------
    char *str2 = NULL;
    str2 = getMemory2(str2, 10);
    strcpy(str2, "jiang");
    cout << "str2:" << str2 << endl;
    free(str);
    cout << "str2:" << str2 << endl; // error

    // -------------------
    // function pointer
    // -------------------
    char *(*pf)(char *p1, char *p2);
    pf = &func;
    (*pf)((char *)"aa", (char *)"bb");

    char *(*pf1[3])(char *p);
    pf1[0] = fun1;
    pf1[1] = &fun2;
    pf1[2] = &fun3;

    pf1[0]((char *)"fun1");
    pf1[1]((char *)"fun2");
    pf1[2]((char *)"fun3");

    char *(*(*pf2)[3])(char *p);
    pf2 = &pf1;
    pf2[0][0]((char *)"fun1");
    pf2[0][1]((char *)"fun2");
    pf2[0][2]((char *)("fun3"));
    return 0;
}