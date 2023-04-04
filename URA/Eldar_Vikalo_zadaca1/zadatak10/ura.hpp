#pragma once

#include <algorithm>
// #include <iostream>
// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It>
void bubblesort(It begin, It end) {
  for(auto i = begin; i!=end; ++i)
  {

    for(auto j = begin; j!=i; ++j)
    {
      // std::cout<<"i:" << *i << " j: " <<*j <<std::endl;
      if(*i < *j){
        std::swap(*i, *j);
        // std::cout<<"i:" << *i << " j: " <<*j <<std::endl;
      }
    }
  }
}


