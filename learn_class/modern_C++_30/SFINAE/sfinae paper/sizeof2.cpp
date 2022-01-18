#include <iostream>

//
// Created by light on 20-1-6.
//

typedef char yes;  // Size: 1 byte.
typedef yes no[2]; // Size: 2 bytes.

// Two functions using our type with different size.
yes &f1() {
    char y = 5;
    return y;
}
no &f2() {
    char n[2] = {};
    return n;
}

int main() {
    std::cout << sizeof(f1()) << std::endl;
    std::cout << sizeof(f2()) << std::endl;
    std::cout << (sizeof(f1()) == sizeof(f2())) << std::endl; // Output 0.
}