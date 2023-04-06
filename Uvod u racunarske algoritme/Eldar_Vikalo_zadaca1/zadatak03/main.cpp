#include "ura.hpp"
#include <iostream>
// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {
  int a[] = {1,2,3,4,5};
 int  size_ = sizeof(a)/sizeof(a[0]);
  std::cout << sum(a,size_) << std::endl;
}
