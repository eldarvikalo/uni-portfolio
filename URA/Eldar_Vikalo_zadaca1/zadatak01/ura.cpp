#include "ura.hpp"
#include <stdexcept>

unsigned int divide(unsigned int a, unsigned int b)
{
  if(b == 0) throw std::runtime_error("Ne postoji dijeljenje sa nulom");
  else if(a<b) return 0;
  else if(!(a-b)) return 1;
  else return 1+divide(a-b,b);
}
