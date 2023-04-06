#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It, typename P>
It partition(It begin, It end, P p) {

  while(begin!=end)
  {
    if(!p(*begin)){
      std::swap(*begin,*(end-1));
      end--;
    }else
      begin++;
  }

  return begin;
}

