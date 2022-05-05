//
// Created by renbin jiang on 2022/5/6.
//
//-------------------------------//
// Chapter 8 - Drill 3
//-------------------------------//

#include "std_lib_facilities.h"

//-------------------------------------------------------------

namespace X {
int var = 0;
void print() {
    cout << "Namespace X - Var: " << var << endl;
}
} // namespace X

//-------------------------------------------------------------

namespace Y {
int var = 0;
void print() {
    cout << "Namespace Y - Var: " << var << endl;
}
} // namespace Y

//-------------------------------------------------------------

namespace Z {
int var = 0;
void print() {
    cout << "Namespace Z - Var: " << var << endl;
}
} // namespace Z

//-------------------------------------------------------------
int main() {
    X::var = 7;
    X::print();

    using namespace Y;
    var = 9;
    print();
    {
        using Z::print;
        using Z::var;
        var = 11;
        print();
    }
//    using Z::print;
    print();
    Z::print();
    X::print();

    keep_window_open();

    return 0;
}

//-------------------------------------------------------------
//-------------------------------------------------------------
