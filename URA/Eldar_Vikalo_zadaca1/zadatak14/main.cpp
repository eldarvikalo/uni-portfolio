#include "ura.hpp"
#include <iostream>
#include <vector>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {

  std::vector<int> v{1,23,42,34,345,32,52,4,13,53,25,1,321};
  for(auto e:v)
    std::cout <<e<< ' ';
  std::cout  << std::endl;
  quicksort(v.begin(), v.end());
  for(auto e:v)
    std::cout <<e<< ' ';
  std::cout  << std::endl;
}
