//
// Created by renbin jiang on 2022/4/16.
//
#include "std_lib_facilities.h"

int main()
{
    // Prime numbers to 100
    vector<int> primes = { 2 };
    
    bool is_prime;
    
    for (int i = 3; i < 100; ++i) {
        is_prime = true;
        for (int prime : primes)
            if (i % prime == 0)
                is_prime = false;
        
        if (is_prime)
            primes.push_back(i);
    }
    
    for (int prime : primes)
        cout << prime << " " << endl;
    
    // ex12
    int inputPrime = 0;
    vector<int> primes_={2};
    cout << "Please input Max numbers:\n";
    while (cin >> inputPrime) {
        for (int i = 3;i < inputPrime;++i) {
            is_prime = true;
            for (const auto tmp : primes_) {
                if ( i % tmp == 0) {
                    is_prime = false;
                }
            }
            
            if (is_prime) {
                primes_.push_back(i);
            }
        }
        break;
    }
    for (const auto p : primes_) {
        cout << p << "  ";
    }
    return 0;
}
