#include "ura.hpp"
#include <iostream>
#include <algorithm>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {

  int a[] = {4,32,5,4325,23,-432,432,52,53,24,325,32};
  int n = sizeof(a)/sizeof(a[0]);

  for(auto i = 0; i<n; i++)
    std::cout << a[i]<< ' ';
  std::cout << std::endl;
  selectionsort(a,a+n);

  for(auto i = 0; i<n; i++)
    std::cout << a[i]<< ' ';
  std::cout << std::endl;
  
}
