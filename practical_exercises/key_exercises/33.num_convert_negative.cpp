#include <stdio.h>

#include <iostream>

using namespace std;

int change(int num) {
    if (num < 0) {
        num = ~(num - 1);
    } else if (num > 0) {
        num = ~num + 1;
    }
    return num;
}
int main() {
    printf("%d\n", change(5));
    printf("%d\n", change(-5));
    printf("%d\n", change(0));
    char c[8];
    c[1] = 1;
    c[2] = 2;
    uint8_t *cc = new uint8_t[8];
    printf("%d %d\n", c[1], c[2]);
    cc[1] = 1;
    cc[2] = 2;
    printf("%d %d\n", cc[1], cc[2]);
    delete[] cc;
    cout << sizeof(unsigned int) << endl;
    return 0;
}