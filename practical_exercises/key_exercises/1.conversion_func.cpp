//
// Created by renbin jiang on 2021/4/7.
//

#include <time.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class fraction {
public:
    fraction(int num, int den = 1) : m_num(num), m_den(den) {}
    operator double() const { return (double)(m_num / m_den); }

private:
    double m_num;
    double m_den;
};

class fraction_explicit {
public:
    explicit fraction_explicit(int num, int den = 1) : m_num(num), m_den(den) {}
    fraction_explicit operator+(const fraction_explicit &f) {
        return fraction_explicit(m_num, m_den);
    }

private:
    double m_num;
    double m_den;
};

template <typename T>
class string_cast {
public:
    string_cast(const std::string &from) : m_from(from) {}
    operator T() const {
        std::stringstream sstr(m_from);
        T ret;
        cout << "ret is " << ret << endl;
        try {
            sstr >> ret;
        } catch (std::exception &e) {
            return T(0);
        }
        return ret;
    }

private:
    const std::string &m_from;
};
int main(int argc, char **argv) {
    struct timespec start_ts, end_ts;
    bool check_time = true;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_ts);
    fraction f(3, 5);
    cout << "f is " << f << endl;
    cout << "(double(3.0 / 5)) is " << (double(3.0 / 5)) << endl;
    double d = 4 + f;
    const int b = string_cast<int>("0x5");
    cout << "d is " << d << endl;
    cout << string_cast<int>("12345") << endl;
    cout << "b is " << b << endl;

    fraction_explicit f1(4, 5);
    fraction_explicit f2(3, 5);
    fraction_explicit e = f2 + f1;
    cout << "e is " << endl;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_ts);
    int64_t cost = (end_ts.tv_sec - start_ts.tv_sec) * 1000000 +
            (end_ts.tv_nsec - start_ts.tv_nsec) / 1000;
    cout << "cost:" << cost << endl;

    return 0;
}