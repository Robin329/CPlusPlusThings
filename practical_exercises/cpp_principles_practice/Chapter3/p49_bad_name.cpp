//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    //    int ridic = 0.273;      // only a warning!
    //    char $ = "w";           // error: double quotes is const char?
    //    double int = 17;        // error: tries to combine int with double
    int len1, len2;
    char buf[] = "25,142,33.0,Smith,J,239,4123";
    len1 = strspn(buf, "0123456789");
    len2 = strspn(buf, ",0123456789");
    cout << "len1:" << len1 << " len2:" << len2 << endl;
    dbg(dbg::time(), buf);
    return 0;
}