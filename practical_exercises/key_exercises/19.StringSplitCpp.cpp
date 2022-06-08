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
// Method 7
//    constexpr const char *ch1 = "12,1,3,12";
//    int ret[1024];
//    int num = 0;
//    split(ret, ch1, ",", strlen(ch1), &num);
static int split(int *ret, const char *src, const char *separator, int len, int *num) {
    if (!ret || !src || !separator || !num) {
        printf("ERR, param is NULL!\n");
        return -1;
    }
    if (!len) {
        printf("ERR, len is wrong!\n");
        return -1;
    }

    char *pch;
    char *pSaveStr;
    int index = 0;
    int count = 0;
    char splitStr[len + 1];
    memset(splitStr, 0, len + 1);
    memcpy(splitStr, src, len);
    pch = strtok_r(splitStr, separator, &pSaveStr);
    while (pch != NULL) {
        ret[index] = atoi(pch);
        ++count;
        printf("ret= %d pch:%d\n", ret[index], atoi(pch));
        pch = strtok_r(NULL, separator, &pSaveStr);
        index++;
    }
    *num = count;
    return 0;
}

static int split8(char dst[][128], const char *src, const char *delim, int len) {
    if (!src || !delim || !dst) return -1;
    char *p = NULL;
    char *rest = const_cast<char*> (src);
    int index = 0;
    char splitStr[len + 1] = {0};
    memcpy(splitStr, src, len);
    p = strtok_r(splitStr, delim, &rest);
    while (p != NULL) {
        std::cout << "p:" << p  << std::endl;
        strncpy(&dst[index][128], p, strlen(p) + 1);
        p = strtok_r(NULL, delim, &rest);
        std::cout << "dst:" << &dst[index][128] << std::endl;
        index++;
    }

    return index;
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

    // Method 7
    constexpr const char *ch1 = "12,1,3,12";
    int ret[1024];
    int num = 0;
    split(ret, ch1, ",", strlen(ch1), &num);

    // Method 8
    constexpr const char *ch8 = "hello ni hao robin";
    char ret8[128][128] = {0};
    // std::cout << "sizeof ch8:" << sizeof(ch8);
    split8(ret8, ch8, " ", strlen(ch8));
    return 0;
}
