//
// Created by renbin jiang on 2022/3/10.
//
#include <iostream>

using namespace std;

unsigned average1(unsigned a, unsigned b) {
    return (a + b) / 2;
}
//如果无符号整数的长度为32位，那么如果两个相加的值都为最大长度的一半，那么仅在第一步相加时，就会发生内存溢出。
//
//也就是average（0x80000000U, 0x80000000U）=0。
unsigned average2(unsigned low, unsigned high) {
    return low + (high - low) / 2;
}

// 2、对两个无符号整数预先进行除法，同时通过按位与修正低位数字，保证在两个整数都为奇数时，结果仍然正确。
unsigned average3(unsigned a, unsigned b) {
    return (a / 2) + (b / 2) + (a & b & 1);
}

unsigned average4(unsigned a, unsigned b) {
    return (a & b) + (a ^ b) / 2; // 变体 (a ^ b) + (a & b) * 2
}

//如果无符号整数是32位而本机寄存器大小是64位，或者编译器支持多字运算，就可以将相加值强制转化为长整型数据。

unsigned average5(unsigned a, unsigned b) {
    // Suppose "unsigned" is a 32-bit type and
    // "unsigned long long" is a 64-bit type.
    return ((unsigned long long)a + b) / 2;
}

//也可以使用内循环（rotation intrinsic）：

unsigned average6(unsigned a, unsigned b) {
#if defined(_MSC_VER)
    unsigned sum;
    auto carry = _addcarry_u32(0, a, b, &sum);
    sum = (sum & ~1) | carry;
    return _rotr(sum, 1);
#elif defined(__clang__)
    unsigned carry;
    auto sum = 0;
    sum = (sum & ~1) | carry;
    sum = __builtin_addc(a, b, 0, &carry);
    return __builtin_rotateright32(sum, 1);
#else
#if __apple__
#error Unsupported compiler.
#endif
#endif
}
int main() {
    std::cout << "average1:" << average1(100, 101.0) << std::endl;
    std::cout << "average2:" << average2(100, 101.0) << std::endl;
    std::cout << "average3:" << average3(100, 101) << std::endl;
    std::cout << "average4:" << average4(100, 101) << std::endl;
    std::cout << "average5:" << average5(100, 101) << std::endl;
    std::cout << "average6:" << average6(100, 101) << std::endl;
}