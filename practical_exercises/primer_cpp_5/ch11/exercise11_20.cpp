#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::string;

int main() {
    map<string, size_t> counts;
    for (string word; cin >> word;) {
        auto result = counts.insert({word, 1});
        if (!result.second) ++result.first->second;
    }
    for (auto const& count : counts)
        cout << count.first << " " << count.second << ((count.second > 1) ? " times\n" : " time\n");

    return 0;
}