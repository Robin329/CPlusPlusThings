#include <iostream>
using namespace std;
int main() {
    const int num = 10;
    const int *const ptr = &num; // error! const int* -> int*
    cout << *ptr << endl;

    int num1 = 20;
    const int *ptr1 = &num1;
    const int *ptr2 = NULL;
    cout << *ptr1 << endl;
    cout << "output :" << endl;
    cout << "*ptr2 :" << *ptr2 << endl;
}
