#include <iostream>

#include "exercise14_24.h"

int main() {
    Date lhs(9999999), rhs(1);

    std::cout << (lhs -= 12000) << "\n";

    return 0;
}