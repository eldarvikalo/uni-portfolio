#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It>
void selectionsort(It begin, It end) {

  auto indeks = begin;
  for (auto i = begin; i != end; ++i)
  {
    indeks = i;
    for(auto j = i+1; j!=end;++j){
      if(*j < *indeks){
        std::swap(*j, *indeks);
      }
    }
  }
}

