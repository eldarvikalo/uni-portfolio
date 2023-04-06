#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It>
void insertionsort(It begin, It end) {

auto beg=begin;
while(beg<end){
  auto iter=beg;
  while(iter>begin && *(iter)<*(iter-1)){
    std::swap(*(iter),*(iter-1));
    --iter;
  }
  ++beg;
}
}

template <typename It>
void quicksort(It begin, It end) {
  int n = end-begin;
  if(n<=10){
    insertionsort(begin,end);
    return;
  }
  It pivot = end-1;
  It middle = begin + n/2;
  std::swap(*pivot, *middle);
  auto partition_point = std::partition(begin, end-1, [&](const auto& elem)
      {return elem< *pivot;});
  std::swap(*pivot, *partition_point);
  quicksort(begin, partition_point);
  quicksort(partition_point+1 , end);
}



