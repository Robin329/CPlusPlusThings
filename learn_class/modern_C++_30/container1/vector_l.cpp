//
// Created by light on 19-12-16.
//
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Obj1 {
public:
    Obj1() { cout << "Obj1()\n"; }

    Obj1(const Obj1 &) { cout << "Obj1(const Obj1&)\n"; }

    Obj1(Obj1 &&) { cout << "Obj1(Obj1&&)\n"; }
};

class Obj2 {
public:
    Obj2() { cout << "Obj2()\n"; }

    Obj2(const Obj2 &) { cout << "Obj2(const Obj2&)\n"; }

    Obj2(Obj2 &&) noexcept { cout << "Obj2(Obj2&&)\n"; }
};

int hello(int a) {
    if (a) {
        return 0;
    } else {
        return -1;
    }
}

char *hello1(void) {
    char *ret = nullptr;
    int a = -1;
    ret = (char *)&a;
    return ret;
}

string foo(void) {
    //  return to_string(hello(0));
    return hello1();
}

int main() {
    //  vector<int> v;
    //
    //  int nums = 20;
    //  for (int i = 0; i < nums; ++i) {
    //    v.push_back(i + 1);
    //    cout << "v_size: " << v.size() << "\t v_capacity: " << v.capacity() <<
    //    endl;
    //  }
    // 头两个在已有空间上成功构造。第三个时发现空间不足，系统会请求更大的空间，大小由实现决定（比如两倍）。
    // 有了足够的空间后，就会在新空间的第三个的位置构造（第三个obj1），成功之后再把头两个拷贝或移动过来。
    vector<Obj1> v1;
    //    v1.reserve(2);
    v1.emplace_back();
    v1.emplace_back();
    v1.emplace_back();
    v1.emplace_back();

    vector<Obj2> v2;
    v2.reserve(2);
    v2.emplace_back();
    v2.emplace_back();
    cout << "-----------\n";
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    while (!q.empty()) {
        cout << "q:" << q.front() << endl;
        q.pop();
    }
    cout << "+++++++++++++++" << endl;
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (!s.empty()) {
        cout << "s:" << s.top() << endl;
        s.pop();
    }
    cout << "------------" << endl;
    vector<int> v{13, 6, 4, 11, 29};
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    cout << endl;

    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    cout << endl;

    sort(v.begin(), v.end(), greater<int>());
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    cout << endl;
    cout << hex;
    auto hp = hash<int *>();
    cout << "hash(nullptr)  = " << hp(nullptr) << endl;
    cout << "hash(v.data()) = " << hp(v.data()) << endl;
    cout << "v.data()       = " << static_cast<void *>(v.data()) << endl;
    auto hs = hash<string>();
    cout << "hash(\"hello\")  = " << hs(string("hello")) << endl;
    cout << "hash(\"hellp\")  = " << hs(string("hellp")) << endl;
    cout << "----------------" << endl;
    cout << foo() << endl;
    cout << string("0");
}