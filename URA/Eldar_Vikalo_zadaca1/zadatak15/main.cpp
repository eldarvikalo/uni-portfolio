#include "ura.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {

  std::vector<Tim> v{  
  {"City", 99, 34, 921},{"Ars", 33, 77, 432},{"Liv", 98, 44, 432}, {"Che", 88, 55, 322}, {"Tot", 88, 55, 322}};

  for(auto e:v){
    std::cout<<"naziv ekipe: " << e.naziv << " Bodovi " <<e.bodovi << " Prim. golovi: "<<e.primljeniGolovi << " Postignuti: "<<e.postignutiGolovi << ' ';
    std::cout << std::endl;
  }

  complicated_sort(v.begin(), v.end());
  std::cout << "Sortitana tabela: " << std::endl;  
  for(auto e:v){
    std::cout<<"naziv ekipe: " << e.naziv << " Bodovi " <<e.bodovi << " Prim. golovi: "<<e.primljeniGolovi << " Postignuti: "<<e.postignutiGolovi << ' ';
    std::cout << std::endl;
  }

}
