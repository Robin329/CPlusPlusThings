#include <cstring>
#include <iostream>

int main() {

  char *sPtr;
  const char *s = "hello";
  sPtr = new char[strlen(s) + 1];
  strncpy(sPtr, s, strlen(s));
  std::cout << "str len s is " << strlen(s) << std::endl;
  std::cout << "str len sPtr is " << strlen(sPtr) << std::endl;
  std::cout << sPtr << std::endl;
  delete sPtr;
  return 0;
}
