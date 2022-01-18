//
// Created by renbin jiang on 2021/4/4.
//

#include <iostream>
#include <map>

using namespace std;

// 比较函数（用于后面的函数指针定义）
bool fncomp(char lhs, char rhs) {
    return lhs < rhs;
}

// 定义一个 Compare 对象，且内部对运算符 () 进行重载
struct classcomp {
    bool operator()(const char &lhs, const char &rhs) { return lhs < rhs; }
};

int main(int argc, char *argv[]) {
    //=========================
    //  map 的多种构造函数
    //=========================

    // 1. 直接定义
    map<char, int> mymap;
    mymap['a'] = 10;
    mymap['b'] = 60;
    mymap['c'] = 30;
    mymap['d'] = 90;
    mymap['e'] = 50;

    // 2. 复制
    map<char, int> second(mymap);

    // 3. 通过迭代器
    map<char, int> third(mymap.begin(), mymap.end());

    // 4. 重新定义 Compare 对象，该对象内部对运算符 () 进行重载
    map<char, int, classcomp> fourth;

    // 5. 通过函数指针
    bool (*fn_pt)(char, char) = fncomp;
    map<char, int, bool (*)(char, char)> fifth(fn_pt);

    //=========================
    //  以最初定义的mymap 为例，讲解 map 的使用
    //=========================
    map<char, int>::key_compare key_comp;
    map<char, int>::iterator it;
    it = mymap.begin();

    //=========================
    //  1. 输出所有 Pair 元素
    //=========================
    // 迭代器遍历 map
    for (; it != mymap.end(); it++) {
        // map的迭代器，可以用 first 访问std::pair的第一个成员(Type1)，second
        // 访问第二个成员 (Type2)
        cout << it->first << ":" << it->second << endl;
    }
    cout << "=================================" << endl;

    //=========================
    //  2. 修改映射值
    //=========================
    second.clear();
    second['a'] = 1002;
    second['b'] = 10023;
    while (!second.empty()) {
        cout << second.begin()->first << " => ";
        cout << second.begin()->second << endl;
        second.erase(second.begin());
    }
    cout << "=================================" << endl;

    //=========================
    //  3. 插入
    //=========================
    mymap.insert(pair<char, int>('f', 100));
    mymap.insert(pair<char, int>('g', 200));
    mymap.insert(pair<char, int>('h', 300));
    cout << "f => " << mymap.find('f')->second << endl;
    cout << "g => " << mymap.find('g')->second << endl;
    cout << "h => " << mymap.find('h')->first << endl;
    cout << "h => " << mymap.find('h')->second << endl;

    cout << "=================================" << endl;

    //=========================
    //  4. Compare 参数的使用
    //=========================
    key_comp = mymap.key_comp();
    cout << "mymap contains:\n";

    // 迭代器反向遍历的起始位置
    char highest = mymap.rbegin()->first; // key value of last element
    it = mymap.begin();
    do {
        cout << (*it).first << " => " << (*it).second << endl;
        cout << "highest = " << highest << endl;
    } while (key_comp((*it++).first, highest));

    cout << endl;
    return 0;
}
