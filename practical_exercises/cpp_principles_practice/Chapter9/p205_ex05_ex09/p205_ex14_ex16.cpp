#include <iostream>

#include "Money.h"

int main() {
    Money m1{"$199.999"};
    std::cout << m1.get_cents() << '\n';

    Money m2{"$5123.5689"};
    std::cout << m2.get_cents() << '\n';

    Money m3{"$0.005"};
    std::cout << m3.get_cents() << '\n';

    Money m4{"$0.004"};
    std::cout << m4.get_cents() << '\n';

    Money m5{"$1"};
    std::cout << m5.get_cents() << '\n';

    Money m6{"$.995"};
    std::cout << m6.get_cents() << '\n';

    //// missing currency type
    // Money m7{".995"};
    // std::cout << m7.get_cents() << '\n';

    //// malformed currency
    // Money m8{"$..995"};
    // std::cout << m8.get_cents() << '\n';

    //// malformed currency
    // Money m9{"$10.995D"};
    // std::cout << m9.get_cents() << '\n';
    std::cout << "\n-------------------------------\n";
    Money m9{"USD104.995"};
    std::cout << m9.get_cents() << '\n';

    Money m10{"DKK109.995"};
    std::cout << m10.get_cents() << '\n';

    Money m11{"Kr129.995"};
    std::cout << m11.get_cents() << '\n';

    Money m12 = m5 + Money{"DKK6.8"};
    std::cout << m12.get_cents() << '\n';

    Money m13 = Money{"DKK8.5"} + m5;
    std::cout << m13.get_cents() << '\n';
    std::cout << "\n-------------------------------\n";
    std::cout << "Enter a monitory amount prefixed by currency code (USD or DKK)\n";
    Money m8, m00;
    std::cin >> m8 >> m00;
    std::cout << "m8 = " << m8 << '\n';
    std::cout << "m00 = " << m00 << '\n';

    std::cout << "m8 + m00 = " << m8 + m00 << "\n";
}
