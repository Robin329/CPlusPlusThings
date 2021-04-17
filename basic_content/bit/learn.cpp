#include <iostream>

using namespace std;
struct stuff {
  unsigned int field1 : 30;
  unsigned int : 2;
  unsigned int field2 : 4;
  unsigned int : 0;
  unsigned int field3 : 3;
};

float f[5] = {2.0, 3.2};

void foo(void) {
  float f1[5] = {3.0, 4.3};
  cout << f1[0] << " "
       << " " << f1[1] << " " << f1[3] << endl;
}

int main() {
  struct stuff s = {1, 3, 5};
  cout << s.field1 << endl;
  cout << s.field2 << endl;
  cout << s.field3 << endl;
  cout << sizeof(s) << endl;

  cout << f[1] << " " << f[3] << endl;

  foo();
  return 0;
}
