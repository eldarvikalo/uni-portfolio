#include "ura.hpp"
#include <iostream>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {
  int a[] = {14324,32,43,4,32,4,2,34,43,2,4532,4,32,4,32};
  int size_  = sizeof(a)/sizeof(a[0]);
  int minimum = min(a,size_);
  std::cout << minimum << std::endl;
}
