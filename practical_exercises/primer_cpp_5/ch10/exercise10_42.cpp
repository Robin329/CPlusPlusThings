#include <iostream>
#include <list>
#include <string>

using std::list;
using std::string;

void elimDups(list<string>& words) {
    words.sort();
    words.unique();
}

int main() {
    list<string> l = {"aa", "aa", "aa", "aa", "aasss", "aa"};
    elimDups(l);
    for (const auto& e : l) std::cout << e << " ";
    std::cout << std::endl;
}