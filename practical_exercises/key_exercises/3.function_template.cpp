#include <cstring>
#include <iostream>

using namespace std;

template <class T>
T compareMax(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

template <>
char *compareMax<char *>(char *s1, char *s2) {
    if (strcmp(s1, s2) >= 0) {
        cout << s1 << " >= " << s2 << endl;
    } else {
        cout << s1 << " < " << s2 << endl;
    }

    return strcmp(s1, s2) >= 0 ? s1 : s2; // s1 >= s2 return s1
}

int main(int argc, char const *argv[]) {
    const char *s1 = "b";
    const char *s2 = "b";
    cout << compareMax(1, 1) << endl;
    cout << compareMax(123, 12341234) << endl;
    cout << compareMax("asda", "qweq") << endl;

    cout << strcmp(s1, s2) << endl;
    system("df -h");
    return 0;
}
