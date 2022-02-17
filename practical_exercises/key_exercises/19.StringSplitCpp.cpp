//
// Created by robin.jiang on 2022/2/9.
//

#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
// Method 1
// stringstream和getline配合使用
std::vector<std::string> stringSplit1(const std::string &str, char delim) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}
// Method 2
//使用std::string::find
std::vector<std::string> stringSplit2(const std::string &str, char delim) {
    std::size_t previous = 0;
    std::size_t current = str.find(delim);
    std::vector<std::string> elems;
    while (current != std::string::npos) {
        if (current > previous) {
            elems.push_back(str.substr(previous, current - previous));
        }
        previous = current + 1;
        current = str.find(delim, previous);
    }
    if (previous != str.size()) {
        elems.push_back(str.substr(previous));
    }
    return elems;
}

// Method 3
// 使用std::string::find_first_of
std::vector<std::string> stringSplit3(const std::string &str, char delim) {
    std::size_t previous = 0;
    std::size_t current = str.find_first_of(delim);
    std::vector<std::string> elems;
    while (current != std::string::npos) {
        if (current > previous) {
            elems.push_back(str.substr(previous, current - previous));
        }
        previous = current + 1;
        current = str.find_first_of(delim, previous);
    }
    if (previous != str.size()) {
        elems.push_back(str.substr(previous));
    }
    return elems;
}
// Method 4
//使用C语言的strtok方法
std::vector<std::string> stringSplit4(const std::string &strIn, char delim) {
    char *str = const_cast<char *>(strIn.c_str());
    std::string s;
    s.append(1, delim);
    std::vector<std::string> elems;
    char *splitted = strtok(str, s.c_str());
    while (splitted != NULL) {
        elems.push_back(std::string(splitted));
        splitted = strtok(NULL, s.c_str());
    }
    return elems;
}

// Method 5
// std::string::find_first_of和std::string::find_first_not_of配合使用

std::vector<std::string> stringSplit5(const std::string &str, char delim) {
    std::vector<std::string> elems;
    auto lastPos = str.find_first_not_of(delim, 0);
    auto pos = str.find_first_of(delim, lastPos);
    while (pos != std::string::npos || lastPos != std::string::npos) {
        elems.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delim, pos);
        pos = str.find_first_of(delim, lastPos);
    }
    return elems;
}
// Method 6
// 使用正则表达式
std::vector<std::string> stringSplit6(const std::string &str, char delim) {
    std::string s;
    s.append(1, delim);
    std::regex reg(s);
    std::vector<std::string> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
                                   std::sregex_token_iterator());
    return elems;
}
int main() {
    std::string str("hello,world!");
    std::vector<std::string> elems1 = stringSplit1(str, ',');
    std::cout << "stringSplit1:" << std::endl;
    //  for(auto i = elems1.begin();i != elems1.end();i++) {
    //    std::cout << *i << std::endl;
    //  }
    for (auto i : elems1) {
        //    hello
        //    world!
        std::cout << i << std::endl;
    }
    std::vector<std::string> elems2 = stringSplit2(str, ',');
    std::cout << "stringSplit2:" << std::endl;
    for (auto i = elems2.begin(); i != elems2.end(); i++) {
        //    hello
        //    world!
        std::cout << *i << std::endl;
    }
    std::vector<std::string> elems3 = stringSplit3(str, ',');
    std::cout << "stringSplit3:" << std::endl;
    for (auto i : elems3) {
        //    hello
        //    world!
        std::cout << i << std::endl;
    }
    std::vector<std::string> elems4 = stringSplit4(str, ',');
    std::cout << "stringSplit4:" << std::endl;
    for (auto i : elems4) {
        //    hello
        //    world!
        std::cout << i << std::endl;
    }
    std::vector<std::string> elems5 = stringSplit5(str, ',');
    std::cout << "stringSplit5:" << std::endl;
    for (auto i : elems5) {
        std::cout << i << std::endl; // hello world!
    }
    std::vector<std::string> elems6 = stringSplit6(str, ',');
    std::cout << "stringSplit6:" << std::endl;
    for (auto i : elems6) {
        std::cout << i << std::endl; // hello world!
    }
}