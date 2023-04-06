#include "ura.hpp"
#include <iostream>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {
  int a[] = {4,32,5,4325,23,432,432,52,53,24,325,32};
  int n = sizeof(a)/sizeof(a[0]);
  bool b = none_of(a,a+n, [](const auto el){return el<0;});
  std::cout << b << std::endl;
}
