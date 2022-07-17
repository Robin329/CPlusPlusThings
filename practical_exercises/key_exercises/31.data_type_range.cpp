#include <iostream>
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>

#include <limits.h>
#include <float.h>

// 使用bitset 将 int 转换二进制
void BinaryBitset(int n)
{
	std::cout << bitset<sizeof(int) * 8>(n) << "b" << std::endl;
}

int main()
{
	printf("\nchar(S8)       : %d —— %d\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char(U8): %u —— %u\n\n", 0, UCHAR_MAX);

	printf("short(S16)         : %hd —— %hd\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short(U16): %hu —— %hu\n\n", 0, USHRT_MAX);

	printf("int(S32)         : %d —— %d\n", INT_MIN, INT_MAX);
	printf("unsigned int(U32): %u —— %u\n\n", 0, UINT_MAX);

	printf("long(S32)         : %ld —— %ld\n", LONG_MIN, LONG_MAX);
	printf("unsigned long(U32): %lu —— %lu\n\n", 0, ULONG_MAX);

	printf("long long(S64)         : %lld —— %lld\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long(U64): %llu —— %llu\n\n", 0, ULLONG_MAX);

	printf("Range of float       : %e -- %e\n", FLT_MIN, FLT_MAX);
	printf("Range of double      : %e -- %e\n", DBL_MIN, DBL_MAX);
	printf("Range of long double : %e -- %e\n", LDBL_MIN, LDBL_MAX);

	// data type out of range
	U64 a = 4294967295;
	U64 b = 0;

	b = a + 5;

	printf("sizeof(a) = %d\n", sizeof a);
	printf("sizeof(int) = %d\n", sizeof b);
	BinaryBitset(b);
	printf("integer b = %d\n\n", b);
	return 0;
}