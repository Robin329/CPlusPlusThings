#include "exercise15_3.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>

double print_total(std::ostream& os, const Quote& item, size_t n);

int main() {
    return 0;
}

double print_total(std::ostream& os, const Quote& item, size_t n) {
    double ret = item.net_price(n);

    os << "ISBN:" << item.isbn() << "# sold: " << n << " total due: " << ret << std::endl;

    return ret;
}