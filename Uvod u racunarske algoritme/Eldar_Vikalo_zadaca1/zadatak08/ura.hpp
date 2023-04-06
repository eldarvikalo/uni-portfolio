#pragma once

#include <algorithm>

// U ovoj datoteci se nalazi funkcija koju trebate implementirati

// TODO Vas kod ovdje
template <typename It>
It unique(It begin, It end) {

    if (begin == end)
        return end;
 
    It beg = begin;
    while (begin != end) {
        if ((*beg != *begin) && ++beg != begin) {
            std::swap(*beg,*begin);
        }
        begin++;
    }
    return ++beg;
}


