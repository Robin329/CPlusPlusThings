//
// Created by renbin jiang on 2022/5/5.
//
#include "std_lib_facilities.h"

void swap_v(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_r(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// this function will not compile because const
// also, you cannot return more than 1 value and the values passed in
// will always be const and therefore cannot be changed
// void swap_cr(const int& a, const int& b)
//{
//	int temp;
//	temp = a, a = b;
//	b = temp;
//
// }
int main() {
    int x = 7;
    int y = 9;
    swap_r(x, y);
    cout << "1. x:" << x << " y:" << y << endl;
    swap_r(x, y);
    cout << "2. x:" << x << " y:" << y << endl;
    const int cx = 7;
    const int cy = 9;
    swap_v(cx, cy);
    // swap_r(cx, cy);	//cannot swap addresses of const values,
    //  I think you can with a non-const pointer though...
    cout << "3. cx:" << cx << " cy:" << cy << endl;
    swap_v(7.7, 9.9);
    // swap_r(7, 9);		//does not compile because there is no address to pass in
    cout << "4. cx:" << cx << " cy:" << cy << endl;
    double dx = 7.7;
    double dy = 9.9;
    std::swap(dx, dy);
    cout << "5. dx:" << dx << " dy:" << dy << endl;
    // swap_r(dx, dy);	//does not compile because the address is not an int value
    // swap_cr(dx, dy);	//does not compile
    swap_v(dx, dy);
    cout << "6. dx:" << dx << " dy:" << dy << endl;
    return 0;
}