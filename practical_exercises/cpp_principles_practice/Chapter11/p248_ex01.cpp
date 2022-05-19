//
// Created by renbin jiang on 2022/5/17.
//
#include "std_lib_facilities.h"

int main() {
    ifstream ifs(FileSystem::getPath(CURRENT_PATH "Chapter11/res/input.txt"), ios_base::binary);
    ofstream ofs(FileSystem::getPath(CURRENT_PATH "Chapter11/res/output.txt"), ios_base::binary);

    if (!ifs) error("can't open input file !");
    // method 1
    while (!ifs.eof()) {
        string str;
        ifs >> str;
        // string 大写转小写，小写转大写： toupper
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        ofs << str << endl;
    }
    // method 2
    char c;
    while (ifs.get(c)) {
        if (isalpha(c)) c = tolower(c);
        cout << "c:" << c << endl;
        ofs << c;
    }

    ifs.close();
    ofs.close();
    return 0;
}