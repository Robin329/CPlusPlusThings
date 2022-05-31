//
// Created by renbin jiang on 2022/5/28.
//
#include "std_lib_facilities.h"

int ga[10] = {1, 2, 4, 6, 18};
vector<int> gv{1, 2, 4, 8, 16};
void f(int *a, int size) {
    if (!a) return;
    if (size < 0) return;
    int la[10] = {};
    memcpy(la, ga, sizeof(ga));
    for (int i = 0; i < 10; ++i) {
        cout << "out " << i << " : " << la[i] << endl;
    }
    int *p = (int *)malloc(sizeof(int) * size);
    *p = *a;
    free(p);
}

void f1(vector<int> gv) {
    vector<int> lv(5);
    lv = gv;
    for (const auto tmp : lv) {
        cout << "tmp:" << tmp << endl;
    }
}

char *func(void) {
    char str[2] = {1, 2};
//    char *ch;
    char *ch = (char *)malloc(sizeof(char) * 2);
    memcpy(ch, str, 2);
    //    ch = str;
    printf("str:%d\n", str[0]);
    cout << "str:" << (int)str[0] << endl;
    cout << "ch0:" << (int)ch[0] << endl;
    return ch;
}
int main() {
    int a[10] = {};
    int aa[10] = {1, 2 * 1, 3 * 2 * 1, 4 * 3 * 2 * 1};
    f(aa, 10);
    cout << "--------------\n";
    f1(gv);

    int c = 12;
    cout << "c : " << (c % 5) << endl;
    cout << "c : " << (c & 4) << endl;
    //    int r[0];
    //    cout << "sizeof:" << sizeof r << endl;
    //    int m = - 20;
    //    unsigned  j = 10;
    //    cout  << (int)(j + m) << endl;
    //    cout << "sizeof unsigned:" << sizeof(unsigned ) << std::dec << endl;
    //    for(unsigned i = 9; i >=0;i--)
    //        printf("%u\n", i);
    char *ret = func();
    for (int i{}; i < 2; ++i) {
        cout << " i : " << i << ", ret: " << (int)ret[i] << endl;
    }
    return 0;
}