//
// Created by renbin jiang on 2022/5/6.
//
#include "std_lib_facilities.h"

void print(const vector<long long>& v, const string& label)
{
    cout << label << endl;
    //for every int in vector, print that int
    for (int i : v)
        cout << i << endl;
}

void fibonacci(long long x, long long y, vector<long long> &v, int n){
    int temp = 0;
    temp = x + y;
    v.push_back(x);
    v.push_back(y);
    for (int i = v.size(); i < n; i++) {
        v.push_back(v[v.size() - 1] + v[v.size() - 2]);
    }
    print(v, "fibonacci:");
}
int main() {
    vector<long long> fib;
    fibonacci(1, 2, fib, 30);
    return 0;
}