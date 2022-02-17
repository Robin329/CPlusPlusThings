#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::endl;
using std::multimap;
using std::string;

int main() {
    multimap<string, string> families;
    for (string lname, cname; cin >> cname >> lname; families.emplace(lname, cname))
        ;
    for (auto const& family : families) std::cout << family.second << " " << family.first << endl;
}