#include "ura.hpp"
#include <numeric>

int sum(const int* array, int n) {
    
  if(n<=0) return 0;
  return sum(array, n-1) + array[n-1];

  return 0;
}
