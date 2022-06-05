//
// Created by renbin jiang on 2022/6/4.
//
#include "std_lib_facilities.h"

template <typename T>
struct S {
    S() {}
    S(T t) : val(t) {}

    istream operator>>(T t) { cin >> val; }
    const T& get() const { return val; }
    void set(T t) {val = t;}
    
    T val;
};

template <typename T>
const T& get(S<T>& s) {
    return s.val;
}

int main() {
    S<double> sd(3.0f);
    cout << "sd.val:" << sd.val << endl;
    S<string> ss("jiang");
    cout << "ss.val:" << ss.val << endl;
    // drill 03
    S<int> si(1);
    cout << "si.val:" << si.val << endl;
    S<char> sc('r');
    cout << "sc.val:" << sc.val << endl;
    S<string> sstr("robin.jiang");
    cout << "sstr.val:" << sstr.val << endl;
    S<vector<int>> sv(vector<int>(10, 100));
    for (const auto tmp : sv.val) {
        cout << "sv.val:" << tmp << endl;
    }

    // drill 04
    cout << "Please input 10 ints:\n";
    for (int i = 0; i < 10; ++i) {
        cin >> sv.val[i];
    }
    for (const auto i : sv.val) {
        cout << "sv.val:" << i << endl;
    }
    cout << "-------------------------\n";
    // drill 05
    for (const auto i : sv.get()) cout << "sv.get:" << i << endl;

    // drill 06
    for (const auto tmp : get(sv))
        cout << "tmp:" << tmp << endl;
    
    // drill 09
    sv.set(vector<int>(10,23));
    for (int i : get(sv))
        cout << i << ", ";
    return 0;
}