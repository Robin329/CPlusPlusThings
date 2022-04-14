//
// Created by renbin jiang on 2022/4/15.
//
#include <cstdio>
#include <fstream>
#include <string>

#include "base.h"
int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Please input more param!!" << endl;
        return 0;
    }
    if (!argv) {
        cout << " Param is NULL" << endl;
        return -1;
    }
    char readfile[64];
    char dumpfile[64];
    for (int i = 0; i < atoi(argv[1]); i++) {
        cout << "i:" << i << endl;
        snprintf(readfile, sizeof(readfile),
                 "practical_exercises/key_exercises/res/read_uniform_%d.txt", i);
        snprintf(dumpfile, sizeof(dumpfile),
                 "practical_exercises/key_exercises/res/dump_uniform_%d.txt", i);
        cout << FileSystem::getPath(readfile) << endl;
        cout << FileSystem::getPath(dumpfile) << endl;

        ifstream op_read(FileSystem::getPath(readfile).c_str());
        ifstream op_dump(FileSystem::getPath(dumpfile).c_str());
        string s2;
        string s1;
        //    while (getline(op_read, s1)) {
        //        if (getline(op_dump, s2)) {
        //            if (s1 == s2) {
        //                cout << "s1:" <<s1 <<", s2:" << s2 << "       YES" << endl;
        //            } else {
        //                cout << "NO" << endl;
        //            }
        //        } else {
        //            break;
        //        }
        //    }
        while (!op_read.eof()) {
            s1 += op_read.get();
        }
        op_read.close();

        while (!op_dump.eof()) {
            s2 += op_dump.get();
        }
        op_dump.close();
        if (s1 == s2) {
            cout << "result --> YES" << endl;
        } else {
            cout << "result --> NO" << endl;
        }
    }
    return 0;
}