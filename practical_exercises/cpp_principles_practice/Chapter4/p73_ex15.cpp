//
// Created by renbin jiang on 2022/4/16.
//
#include "std_lib_facilities.h"

int main() {
    // Sieve of Eratosthenes
    vector<int> primes = {2};
    cout << "Please input:\n";
    int count;
    bool isPrime = false;
    cin >>count;
    for (int i = 3;;++i) {
        isPrime = true;
        for (const auto tmp : primes) {
            if (i % tmp == 0)
                isPrime = false;
        }
        if (isPrime)
            primes.push_back(i);
        if (primes.size()==count)
            break;
    }
    
    for (int n : primes)
        cout << n << '\n';
    return 0;
}