#pragma once

#include <algorithm>
// #include <iostream>
// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It, typename P>
bool all_of(It begin, It end, P p) {
  //if(begin-end == 0) throw std::out_of_range("Prazan niz");
  
  while (begin!=end)
  {
    if(!p(*begin))
      return false;
    ++begin;
  }
    return true;
}

