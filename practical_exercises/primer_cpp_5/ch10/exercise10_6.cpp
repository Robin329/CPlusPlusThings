#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::fill_n;
using std::vector;

int main() {
    vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fill_n(vec.begin(), vec.size(), 0);

    for (auto i : vec) cout << i << " ";
    cout << endl;
}