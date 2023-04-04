#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

template <typename It>
void insertionsort_var(It begin, It end,int inkrement) {
  int n=end-begin;
  for(int i=inkrement;i<n;i+=inkrement){
  int j=i;
  while(j>=inkrement && *(begin+j)<*(begin+j-inkrement)){
    std::swap(*(begin+j),*(begin+j-inkrement));
    j=j-inkrement;
  }
  }
}

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
void shellsort(It begin, It end) {
int n=end-begin;
for(int inkrement=n/2;inkrement>2;inkrement/=2){
  for(int i=0;i<inkrement;++i){
  insertionsort_var(begin+1,end-1,inkrement);
  }
}
insertionsort_var(begin,end,1);
}
