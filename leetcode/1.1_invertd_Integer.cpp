//
// Created by renbin jiang on 2021/4/5.
//

#include <iostream>

using namespace std;

//题目：
//
//给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
//
//如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回
// 0。假设环境不允许存储 64 位整数（有符号或无符号）。
//
//示例 1：
//
//输入：x = 123 输出：321
//
//示例 2：
//
//输入：x = -123 输出：-321

//
//题解：
//
//直接采用long强制转换与int数进行比较，判断是否越界。
//

//判断是否出界
class Solution1 {
public:
    int reverse(int x) {
        long n = 0;
        while (x) {
            n = n * 10 + x % 10;
            x /= 10;
        }
        return (int)n == n ? int(n) : 0;
    }
};

// int范围[-2^31,2^31-1]，即[-2147483648,2147483647]。
//
//在计算过程中，根据公式：n = n*10+yu，如果n>214748364 或者
// n=214748364并且余数大于7，返回0；同样对于负数，如果n<-214748364 或者
// n=-214748364并且余数小于8，返回0.
class Solution2 {
public:
    int reverse(int x) {
        int n = 0;
        while (x) {
            int yu = x % 10;
            if (n > 214748364 || (n == 214748364 && yu > 7)) return 0;
            if (n < -214748364 || (n == -214748364 && yu < -8)) return 0;
            n = n * 10 + yu;
            x /= 10;
        }
        return n;
    }
};

int main(int argc, char **argv) {
    Solution1 sol1;
    Solution2 sol2;
    int a = 12345;
    cout << "a is    " << a << endl;
    cout << "sol1 is " << sol1.reverse(a) << endl;
    cout << "sol2 is " << sol2.reverse(a) << endl;
    cout << __cplusplus << endl;
    return 0;
}