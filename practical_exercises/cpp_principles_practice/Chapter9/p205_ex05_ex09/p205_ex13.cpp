#include <iostream>

#include "Rational.h"

using std::cerr;
using std::cin;
using std::cout;

int main() try {
    cout << "Enter the integers of two rational numbers:\n";
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    Rational r1{a, b};
    Rational r2{c, d};

    cout << "Add: " << r1 + r2 << '\n'
         << "Sub: " << r1 - r2 << '\n'
         << "Mul: " << r1 * r2 << '\n'
         << "Div: " << r1 / r2 << '\n';
    Rational r11{4, 8};
    std::cout << "r11 = " << r11.get_numerator() << '/' << r11.get_denominator() << '\n';

    Rational r22{3, 12};
    std::cout << "r22 = " << r22.get_numerator() << '/' << r22.get_denominator() << '\n';

    auto r3 = r11 + r22;
    std::cout << "r3 = " << r3.get_numerator() << '/' << r3.get_denominator() << '\n';

    auto r4 = r3 - Rational(2, 7);
    std::cout << "r4 = " << r4.get_numerator() << '/' << r4.get_denominator() << '\n';

    auto r5 = r11 * Rational(1, 2);
    std::cout << "r5 = " << r5.get_numerator() << '/' << r5.get_denominator() << '\n';

    auto r6 = r11 / Rational(3, 16);
    std::cout << "r6 = " << r6.get_numerator() << '/' << r6.get_denominator() << '\n';

    double r7 = r6;
    std::cout << "r7 = " << r7 << '\n';
    return 0;
} catch (std::exception& e) {
    cerr << e.what() << '\n';
} catch (...) {
    cerr << "unknown exception" << '\n';
}