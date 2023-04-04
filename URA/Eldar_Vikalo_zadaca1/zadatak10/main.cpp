#include "ura.hpp"
#include <iostream>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {
  int a[] = {3,5,4,2,6,1,43,25,43,5,32,5,43,65,2,5,2,52};
  int n = sizeof(a)/sizeof(a[0]);
  for(auto i = 0; i<n;i++)
    std::cout<<a[i]<<' ';
  std::cout << std::endl;
  bubblesort(a,a+n);
  for(auto i = 0; i<n;i++)
    std::cout<<a[i]<<' ';
  std::cout << std::endl;


}
