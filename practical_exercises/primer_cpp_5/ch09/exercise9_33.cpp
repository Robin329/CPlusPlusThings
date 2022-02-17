#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto begin = v.begin();
    while (begin != v.end()) {
        ++begin;
        /*begin = */ v.insert(begin, 42);
        ++begin;
    }

    for (auto i : v) cout << i << " ";

    return 0;
}