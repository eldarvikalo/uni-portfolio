#include "ura.hpp"
#include <iostream>
#include <vector>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {
  
  std::vector<int> v{1,32,4,32,45,32,4,34,43};
  for(auto e: v)
    std::cout << e<<' ';
  std::cout << std::endl;
  insertionsort(v.begin(), v.end());
  for(auto e: v)
    std::cout << e<<' ';
  std::cout << std::endl;
  
}
