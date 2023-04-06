#include "ura.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.


int main(void)
{
  
  // int n[] = {1,435,131,543,1,543,2643,1,3534,53,2,543,2};
  // int vel = sizeof(n)/sizeof(n[0]);
  // for(int i = 0; i<vel; i++)
  //   std::cout << n[i]<<' ';
  // std::cout << std::endl;
  // merge(n,vel);
  // for(int i = 0; i<vel; i++)
  //   std::cout << n[i]<<' ';
  // std::cout << std::endl;

  // int* x = {};
  // srand(time(NULL));
  // for(int i = 0; i<100;i++)
  //   x[i] = rand()%100;
  // int v = sizeof(x)/sizeof(x[0]);
  // shell(x,v);
  
  const int array_size = 10;
  std::vector<int> v;
  v.resize(array_size);
  for(int i = 0; i<v.size(); i++)
    v.at(i) = i;

  std::cout << "------------------------------" << std::endl;
  
  std::random_shuffle(v.begin() , v.end());
  for(auto i = 0; i< v.size(); i++)
    std::cout<<v.at(i) << ' ';
  std::cout << std::endl;
  // for(auto e: v)
  //   std::cout << e<<' ';
  // std::cout << std::endl;

  
  mergesort(v.begin(), v.end());

  for(auto i = 0; i< v.size(); i++)
    std::cout<<v.at(i) << ' ';
  std::cout << std::endl;
  // for(auto e: v)
  //   std::cout << e<<' ';
  // std::cout << std::endl;
  
  return 0;
}
