#include <iostream>

using namespace std;
extern "C" {
#include "add.h"
}

int main() {
    cout << add(2, 3);
    return 0;
}
