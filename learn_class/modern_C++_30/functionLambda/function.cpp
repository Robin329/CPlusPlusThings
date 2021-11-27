//
// Created by light on 20-1-11.
//

#include <cstring>
#include <functional>
#include <iostream>
#include <map>

using namespace std;

/* 返回ch字符在sign数组中的序号 */
int getIndexOfSigns(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    }
    if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    }
    return -1;
}
/* 十六进制数转换为十进制数 */
long hexToDec(char *source) {
    long sum = 0;
    long t = 1;
    int i, len;

    len = strlen(source);
    for (i = len - 1; i >= 0; i--) {
        sum += t * getIndexOfSigns(*(source + i));
        t *= 16;
    }

    return sum;
}
int main() {
    map<string, function<int(int, int)>> op_dict{
            {"+", [](int x, int y) { return x + y; }},
            {"-", [](int x, int y) { return x - y; }},
            {"*", [](int x, int y) { return x * y; }},
            {"/", [](int x, int y) { return x / y; }},
    };
    const char *str = "return_data : {0x00100000 }";
    char ch[256] = {0};
    strncpy(ch, str, strlen(str));
    cout << "ch:" << ch << endl;
    cout << "long int:" << sizeof(long) << endl;
    cout << "long long int:" << sizeof(long long) << endl;
    cout << "int:" << sizeof(int) << endl;
    char *saveptr = nullptr;
    char *pch = nullptr;
    unsigned int result = 0;
    char num[128] = {0};
    pch = strtok_r(ch, "{", &saveptr);
    while (pch != nullptr) {
        pch = strtok_r(NULL, " }", &saveptr);
        cout << "pch:" << pch << " size:" << strlen(pch) << endl;
        result = hexToDec(pch);
        cout << "result:" << result << endl;
        printf("result:0x%08x\n", result);
    }
    printf("result:0x%08x\n", result);
    return 0;
}