#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::cout << json::meta() << std::endl;
}
