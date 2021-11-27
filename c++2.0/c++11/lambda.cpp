//
// Created by renbin jiang on 2021/11/27.
//
// even_lambda.cpp
// compile with: cl /EHsc /nologo /W4 /MTd
#include <algorithm>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"
using namespace std;

int for_each_test() {
    // Create a vector object that contains 9 elements.
    vector<int> v;
    for (int i = 1; i < 10; ++i) {
        v.push_back(i);
    }

    // Count the number of even numbers in the vector by
    // using the for_each function and a lambda.
    int evenCount = 0;
    for_each(v.begin(), v.end(), [&evenCount](int n) {
        cout << n;
        if (n % 2 == 0) {
            cout << " is even " << endl;
            ++evenCount;
        } else {
            cout << " is odd " << endl;
        }
    });

    // Print the count of even numbers to the console.
    cout << "There are " << evenCount << " even numbers in the vector." << endl;
    return 0;
}
#include <algorithm>
#include <cmath>

bool abssort(float* x, unsigned n) {
    std::sort(x, x + n,
              // Lambda expression begins
              [](float a, float b) {
                  return (std::abs(a) < std::abs(b));
              } // end of lambda expression
    );
    return true;
}
#include <algorithm> // std::sort
#include <iostream>  // std::cout
#include <vector>    // std::vector
//以普通函数的方式实现自定义排序规则
bool mycomp(int i, int j) {
    return (i < j);
}
//以函数对象的方式实现自定义排序规则
class mycomp2 {
public:
    bool operator()(int i, int j) { return (i < j); }
};
int lambda3_test() {
    std::vector<int> myvector{32, 71, 12, 45, 26, 80, 53, 33};
    //调用第一种语法格式，对 32、71、12、45 进行排序
    //    std::sort(myvector.begin(), myvector.begin() + 4); //(12 32 45 71) 26 80 53 33
    //    //调用第二种语法格式，利用STL标准库提供的其它比较规则（比如 greater<T>）进行排序
    //    std::sort(myvector.begin(), myvector.begin() + 4,
    //              std::greater<int>()); //(71 45 32 12) 26 80 53 33
    //
    //    //调用第二种语法格式，通过自定义比较规则进行排序
    //    std::sort(myvector.begin(), myvector.end(), mycomp2()); // 12 26 32 33 45 53 71 80
    std::sort(myvector.begin(), myvector.end(), [](int i, int j) { return i > j; });
    //输出 myvector 容器中的元素
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
        std::cout << *it << ' ' << std::endl;
    }
    return 0;
}
TEST(FOREACH, FOREACH_demo) {
    EXPECT_EQ(0, for_each_test());
    float x = 2.33333;
    EXPECT_TRUE(abssort(&x, 4));
    EXPECT_EQ(0, lambda3_test());
}