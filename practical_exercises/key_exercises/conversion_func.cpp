//
// Created by renbin jiang on 2021/4/7.
//
#include <iostream>

using namespace std;

class fraction {
public:
  fraction(int num, int den = 1)
      : m_num(num), m_den(den) operator double() const {
    return (double)(m_num / m_den)
  }

private:
  int m_num;
  int m_den;
};
int main(int argc, char **argv) {
  fraction f(3.5);
  double d = 4 + f;
  cout << "d is " << d << endl;

  return 0;
}