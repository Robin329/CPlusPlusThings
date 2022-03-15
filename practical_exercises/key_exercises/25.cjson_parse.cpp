//
// Created by renbin jiang on 2022/3/16.
//
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::cout << "-------------->>updaterange:" << std::endl;
    // create a JSON array
    json j1 = {"one", "two", 3, 4.5, false};

    // create a copy
    json j2(j1);

    // serialize the JSON array
    std::cout << j1 << " = " << j2 << '\n';
    std::cout << std::boolalpha << (j1 == j2) << '\n';

    std::cout << "-------------->>update:" << std::endl;
    // create two JSON objects
    json o1 = R"( {"color": "red", "price": 17.99} )"_json;
    json o2 = R"( {"color": "blue", "speed": 100} )"_json;

    // add all keys from o2 to o1 (updating "color")
    o1.update(o2);

    // output updated object o1
    std::cout << std::setw(2) << o1 << '\n';
    std::cout << "-------------->>unflatten:" << std::endl;
    // create JSON value
    json j_flattened = {{"/answer/everything", 42},
                        {"/happy", true},
                        {"/list/0", 1},
                        {"/list/1", 0},
                        {"/list/2", 2},
                        {"/name", "Niels"},
                        {"/nothing", nullptr},
                        {"/object/currency", "USD"},
                        {"/object/value", 42.99},
                        {"/pi", 3.141}};

    // call unflatten()
    std::cout << std::setw(4) << j_flattened.unflatten() << '\n';
    std::cout << "-------------->>type_name:" << std::endl;
    // create JSON values
    json j_null;
    json j_boolean = true;
    json j_number_integer = -17;
    json j_number_unsigned = 42u;
    json j_number_float = 23.42;
    json j_object = {{"one", 1}, {"two", 2}};
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";

    // call type_name()
    std::cout << j_null << " is a " << j_null.type_name() << '\n';
    std::cout << j_boolean << " is a " << j_boolean.type_name() << '\n';
    std::cout << j_number_integer << " is a " << j_number_integer.type_name() << '\n';
    std::cout << j_number_unsigned << " is a " << j_number_unsigned.type_name() << '\n';
    std::cout << j_number_float << " is a " << j_number_float.type_name() << '\n';
    std::cout << j_object << " is an " << j_object.type_name() << '\n';
    std::cout << j_array << " is an " << j_array.type_name() << '\n';
    std::cout << j_string << " is a " << j_string.type_name() << '\n';
    std::cout << "-------------->>type_error:" << std::endl;
    try {
        // calling push_back() on a string value
        json j = "string";
        j.push_back("another string");
    } catch (json::type_error& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
    }
    std::cout << "-------------->>to_msgpack:" << std::endl;
    // create a JSON value
    json j = R"({"compact": true, "schema": 0})"_json;

    // serialize it to MessagePack
    std::vector<uint8_t> v = json::to_msgpack(j);

    // print the vector content
    for (auto& byte : v) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
    }
    std::cout << std::endl;
    std::cout << "-------------->>:" << std::endl;

    std::cout << "-------------->>:" << std::endl;
}
