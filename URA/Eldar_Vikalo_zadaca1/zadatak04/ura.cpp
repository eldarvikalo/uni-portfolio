#include "ura.hpp"
#include <stdexcept>

int min(const int* array, int n) {
  if(n==0) throw std::runtime_error("Prazan niz");
  if(n == 1)  return array[0];
  int minimum=array[0];
  if (minimum<min(array+1,n-1))
    return minimum;
  else 
    return min(array+1,n-1);
}
