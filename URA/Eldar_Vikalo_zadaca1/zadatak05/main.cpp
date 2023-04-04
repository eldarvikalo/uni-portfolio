#include "ura.hpp"
#include <iostream>
#include <vector>
// #include <algorithm>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {

  // std::vector<int> v{42,4,32,45,5,4,3,5,5,3,5,43435,425};
  // bool x = all_of(v.begin(), v.end(), [](const auto& el){
  //     return el>0;});
  // std::cout << x << std::endl;

  int a[] = {4,32,5,4325,23,-432,432,52,53,24,325,32};
  int n = sizeof(a)/sizeof(a[0]);
  bool b = all_of(a,a+n, [](const auto el){return el%2 == 0;});
  std::cout << b << std::endl;
}
