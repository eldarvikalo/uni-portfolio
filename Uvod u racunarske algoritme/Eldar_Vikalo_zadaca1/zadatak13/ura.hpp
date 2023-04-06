#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje

template<typename It>
void mergesort_pom(It begin, It middle ,It end)
{

  while(begin!= end && middle != end)
  {
    if(*begin <= *middle)  ++begin;
    else if(begin>=middle) ++middle;
    else {
      auto mid = *middle;
      It temp = middle;
      while(temp !=begin){
        *temp = *(temp-1);
        --temp;
      }
      *begin++ = mid;
      middle++;
    }
  }
}

template<typename It>
void mergesort(It begin, It end)
{
  if(end<= begin+1) return;
  It middle = begin+(end-begin)/2;
  mergesort(begin, middle);
  mergesort(middle, end);
  mergesort_pom(begin, middle, end);
}





