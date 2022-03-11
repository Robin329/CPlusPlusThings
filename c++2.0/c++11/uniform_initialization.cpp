//
// Created by light on 19-11-2.
//

#include <iostream>
#include <vector>

using namespace std;

class stump {
private:
    int root;
    double weight;

public:
    stump(int r, double w) : root(r), weight(w) { cout << "r:" << r << " w:" << w << endl; }
};

int main() {
    int value[]{1, 2, 3}; // initializer_list<T> 会关联一个array<T,n>
                          // 里面元素被编译器逐一分解传给函数
    vector<int> v{2, 3, 5};
    int x = {5};
    cout << "x:" << x << endl;
    double y{3.00};
    cout << "y:" << y << endl;
    short eql[]{1, 2, 3, 4, 5, 6, 7, 8};
    for (auto const &temp : eql) {
        std::cout << "temp:" << temp << endl;
    }
    int *anr = new int[4]{2, 3, 4, 5};
    for (int a = 0; a < sizeof(*anr); a++) {
        std::cout << "anr:" << *anr++ << endl;
    }
    if (anr) {
        delete[] anr;
    }
    stump stump1(1, 2.0);
    stump stump2{2, 3.0};
    stump stump3 = {3, 4.0};

    // 使用初始化列表语法，编译器禁止将值存储到宽度不够的变量中
    //    char c1{1.57e27}; //compile error
    char c2{66};
    double c3{66};

    // std::initializer_list
    vector<int> a1(10);
    vector<int> a2{10};
    vector<int> a3{4, 3, 2};

    // auto

    return 0;
}