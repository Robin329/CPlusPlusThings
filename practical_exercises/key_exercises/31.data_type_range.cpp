#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bitset>
#include <iostream>

#include "base.h"
/**  clang-formats off
 *  char(S8)       : -128 —— 1(127)
 *  unsigned char(U8): 0 —— 255
 *
 *  short(S16)         : -32768 —— 32767
 *  unsigned short(U16): 0 —— 65535
 *
 *  int(S32)         : -2147483648 —— 2147483647
 *  unsigned int(U32): 0 —— 4294967295
 *
 *  long(S32)         : -9223372036854775808 —— 9223372036854775807
 *  unsigned long(U32): 0 —— 18446744073709551615
 *
 *  long long(S64)         : -9223372036854775808 —— 9223372036854775807
 *  unsigned long long(U64): 0 —— 18446744073709551615
 *
 *  Range of float       : 1.175494e-38 -- 3.402823e+38
 *  Range of double      : 2.225074e-308 -- 1.797693e+308
 *  Range of long double : 0.000000e+00 -- 0.000000e+00
 *  sizeof(a) = 8
 *  sizeof(int) = 8
 *  0000000000000000000000000000000000000000000000000000000000000100b
 *  1111111111111111111111111111111111111111111111111111111111111101b
 *  0000000000000000000000000000000000000000000000000000000000000011b
 *  0000000000000000000000000000000000000000000000000000000000000011b
 *  integer b = 4
 *
 *  7
 *  7
 */
// 使用bitset 将 int 转换二进制
template <typename T>
void BinaryBitset(T n) {
    std::cout << bitset<sizeof(T) * 8>(n) << "b" << std::endl;
}

int main() {
    printf("\nchar(S8)       : %d —— %d(%d)\n", SCHAR_MIN, sizeof(unsigned char), SCHAR_MAX);
    printf("unsigned char(U8): %u —— %u\n\n", 0, UCHAR_MAX);

    printf("short(S16)         : %hd —— %hd  [%#lx - %#lx]\n", SHRT_MIN, SHRT_MAX, SHRT_MIN, SHRT_MAX);
    printf("unsigned short(U16): %hu —— %hu  [%#lx - %#lx]\n\n", 0, USHRT_MAX, 0, USHRT_MAX);

    printf("int(S32)         : %ld —— %ld  [%#lx - %#lx]\n", INT_MIN, INT_MAX, INT_MIN, INT_MAX);
    printf("unsigned int(U32): %lu —— %lu  [%#lx - %#lx]\n\n", 0, UINT_MAX, 0, UINT_MAX);

    printf("long(S32)         : %ld —— %ld  [%#lx - %#lx]\n", LONG_MIN, LONG_MAX, LONG_MIN, LONG_MAX);
    printf("unsigned long(U32): %lu —— %lu  [%#lx - %#lx]\n\n", 0, ULONG_MAX, 0, ULONG_MAX);

    printf("long long(S64)         : %lld —— %lld  [%#llx - %#llx]\n", LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MAX);
    printf("unsigned long long(U64): %llu —— %llu  [%#llx - %#llx]\n\n", 0, ULLONG_MAX, 0, ULLONG_MAX);

    printf("Range of float       : %e -- %e\n", FLT_MIN, FLT_MAX);
    printf("Range of double      : %e -- %e\n", DBL_MIN, DBL_MAX);
    printf("Range of long double : %e -- %e\n", LDBL_MIN, LDBL_MAX);

    // data type out of range
    U64 a = 18446744073709551615;
    U64 b = 0, c = 0;

    b = a + 5;
    c = a - 2;
    printf("sizeof(a) = %d\n", sizeof a);
    printf("sizeof(int) = %d\n", sizeof b);
    BinaryBitset<u64>(b);
    BinaryBitset<u64>(c);
    BinaryBitset<S64>(-c);
    // 负数表示为原码的补码 = 对该数的原码(正数的原码是本身，负数是绝对值最高位加1)除符号位外各位取反，然后最后一位加1
    // 0000000000000000000000000000000000000000000000000000000000000100b b
    // 1111111111111111111111111111111111111111111111111111111111111101b c
    // c 原码：
    // 0111111111111111111111111111111111111111111111111111111111111101b
    // c 补码：
    // 0000000000000000000000000000000000000000000000000000000000000011b -c
    BinaryBitset<u64>(-c);
    printf("integer b = %d\n\n", b);
    std::cout << (b - c) << std::endl;
    std::cout << (s64)(b - c) << std::endl;
    return 0;
}