//
// Created by renbin jiang on 2022/6/2.
//
#include <iostream>

int test(void) {
//    int a[5] = {1, 2, 3, 4, 5};
//    int *prt1 = (int *)(&a + 1);
//    int *ptr2 = (int *)((int)a + 1);
//    printf("%x,%x", prt1[-1],*ptr2);
    return 0;
}

int checkSystem(void) {
    union check {
        int i;
        char ch;
    } c;
    c.i = 1;
    return (c.ch == 1);
}

int main() {
    printf("Current System is '%s'\n", checkSystem() ? "Little" : "Big" );
    test();
    return 0;
}