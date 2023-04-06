#include "ura.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {

  std::vector<int> v{1,2,3,3,3,4,5,6,6,7,8,9};
  for(auto e:v)
    std::cout<<e<<' ';
  std::cout << std::endl;
  std::unique(v.begin(), v.end());
  for(auto e:v)
    std::cout<<e<<' ';
  std::cout << std::endl;
}
