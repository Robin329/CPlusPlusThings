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

void checkEndian1(void)
{
	unsigned int value = 0x11223344;
	char *r = (char *)&value;
	int i;

	for (i = 0; i < 4; i++) {
		printf("Address of 0x%x = %d \n", r[i], &r[i]);
	}
}

void checkEndian2(void)
{
	unsigned int value = 0x1;
	char *r = (char *)&value;

	if (*r == 1)
		printf("Your system is Little Endian\n");
	else
		printf("Your system is Big Endian\n");
}
int checkSystem(void) {
    union check {
        int i;
        char ch;
    } c;
    c.i = 1;
    return (c.ch == 1);
}

int convertEndian1(void)
{
	int value = 0x11223344;
	int converted = 0;

	printf("Value Before Converting = 0x%x\n", value);

	converted |= ((0xff & value) << 24);
	converted |= (((0xff << 8) & value) << 8);
	converted |= (((0xff << 16) & value) >> 8);
	converted |= (((0xff << 24) & value) >> 24);

	printf("Value After Converting = 0x%x\n", converted);

	return 0;
}

int convertEndian2(void)
{
	int value = 0x11223344;
	int converted = 0;

	printf("Value Before Converting = 0x%x\n", value);

	converted |= ((0x000000ff & value) << 24);
	converted |= ((0x0000ff00 & value) << 8);
	converted |= ((0x00ff0000 & value) >> 8);
	converted |= ((0xff000000 & value) >> 24);

	printf("Value After Converting = 0x%x\n", converted);

	return 0;
}
#define convert(value)                                                         \
	((0x000000ff & value) << 24) | ((0x0000ff00 & value) << 8) |           \
		((0x00ff0000 & value) >> 8) | ((0xff000000 & value) >> 24)

int convertEndian3(void)
{
	int value = 0x11223344;
	int converted = 0;
	printf("Value Before Converting = 0x%x\n", value);
	converted = convert(value);
	printf("Value After Converting = 0x%x\n", converted);
	return 0;
}
int main()
{
	printf("Current System is '%s'\n", checkSystem() ? "Little" : "Big");
	test();
	printf("---------------------------------\n");
	// If you see the output, 0x44 (LSB) in the Lowest Address and 0x11 (MSB) in the Highest Address.
	// So this system is the Little Endian System.
	checkEndian1();
	printf("---------------------------------\n");
	checkEndian2();
	printf("---------------------------------\n");
	convertEndian1();
	printf("---------------------------------\n");
	convertEndian2();
	printf("---------------------------------\n");
	convertEndian3();
    return 0;
}