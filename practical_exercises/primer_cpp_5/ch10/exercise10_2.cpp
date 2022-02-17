#include <algorithm>
#include <iostream>
#include <list>
#include <string>

int main() {
    std::list<std::string> l = {"aa", "aaa", "aa", "cc"};
    std::cout << std::count(l.cbegin(), l.cend(), "aa") << std::endl;

    return 0;
}