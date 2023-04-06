#pragma once

#include <algorithm>
#include <string>

// U ovoj datoteci se nalazi potpis funkcije koju trebate implementirati
// Smijete prosiriti implementaciju i dodati dodatne funkcije koje su vam
// potrebne.
// Potrebno je dodati implementaciju algoritama sortiranja koje cete koristiti.
// U potpisu tim algoritama uzeti lambda izraz kao relaciju poredenja.
// U funkciji complicated_sort pozovite algoritme soritranja koje smatrate
// da su potrebni sa odgovarajucim lambda izrazima.

struct Tim {
  std::string naziv;
  int bodovi;
  int primljeniGolovi;
  int postignutiGolovi;
};

template <typename It, typename P>
void merge_pom(It first,It middle, It second, P pred) {
  while (middle != second && first != middle) {
    if (pred(*first, *middle))
      ++first;
    else {
      if (middle - 1 == first)  std::swap(*first, *middle);

      else {
        auto temp = *first;
        *first = *middle;
        for (auto it = middle; it - 1 != first; --it){ 
          *it = *(it - 1);
        }

        *(first + 1) = temp;
      }
      ++first;
      ++middle;
    }
  }
}

template <typename It, typename P>
void mergesort(It begin, It end, P pred) {
  int razlika=end-begin;
  if (razlika== 1) return;
  auto middle = begin+(end - begin)/2;
  mergesort(begin,middle,pred);
  mergesort(middle,end,pred);
  merge_pom(begin,middle,end,pred);
}


template <typename It, typename P>
void quicksort(It begin, It end, P pred) {
  if(end<=begin) return;
  auto middle = begin + (end-begin)/2;
  std::swap(*middle, *(end-1));
  auto part=std::partition(begin,end-1,[&](const auto& el){return pred(el, *(end-1)); });
  std::swap(*(end-1), *part);
  quicksort(begin,part,pred);
  quicksort(part+1,end,pred);
}


template <typename It>
void complicated_sort(It begin, It end) {

  quicksort(begin, end,[](const auto& tim1, const auto& tim2){
    return tim1.naziv<=tim2.naziv;});
  
  mergesort(begin, end,[](const auto& tim1, const auto& tim2){
    return tim1.postignutiGolovi<=tim2.postignutiGolovi;});

  mergesort(begin, end,[](const auto& tim1, const auto& tim2){
    int razlika1=tim1.postignutiGolovi-tim1.primljeniGolovi;
    int razlika2=tim2.postignutiGolovi-tim2.primljeniGolovi;
    return razlika1>=razlika2;});

  mergesort(begin, end,[](const auto& tim1, const auto& tim2){
    return tim1.bodovi>=tim2.bodovi;});


}

