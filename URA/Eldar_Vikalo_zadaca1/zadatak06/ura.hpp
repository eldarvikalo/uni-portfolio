#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It, typename P>
bool none_of(It begin, It end, P p) {

  while(begin!=end)
  {
    if(p(*begin))
      return false;
    begin++;
  }

  return true;
}

