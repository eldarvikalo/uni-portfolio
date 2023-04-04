#pragma once

#include <algorithm>


// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It>
void insertionsort(It begin, It end) {
  for (auto i = begin + 1; i != end; ++i) {
    auto element = i;

    for (auto j = i - 1; j >= begin; --j) {
      if (*j > *element) {
        std::swap(*j, *element);
        element--;
      }
    }
  }
}
