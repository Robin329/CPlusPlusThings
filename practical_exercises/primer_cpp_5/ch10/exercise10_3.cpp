#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    std::cout << std::accumulate(v.cbegin(), v.cend(), 0) << std::endl;

    return 0;
}