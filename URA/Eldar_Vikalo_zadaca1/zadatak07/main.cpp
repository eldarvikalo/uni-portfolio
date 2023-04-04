#include "ura.hpp"
#include <iostream>
#include <vector>


// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {
  
  // std::vector<int> v{1,4,5,234,32532,314,2,532};
  int a[] = {4,32,5,4325,23,-432,432,52,53,24,325,32};
  int n = sizeof(a)/sizeof(a[0]);

  for(auto i = 0; i<n; i++)
    std::cout<<a[i]<<' ';
  std::cout << std::endl;
  auto it = partition(a, a+n ,[](const auto& elem)
      {return elem>300;});
  // std::cout << *it << std::endl;
  for(auto i = 0; i<n; i++)
    std::cout<<a[i]<<' ';
  std::cout << std::endl;
  

}
