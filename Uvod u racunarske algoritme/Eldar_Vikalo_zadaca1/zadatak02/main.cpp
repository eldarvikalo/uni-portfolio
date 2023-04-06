#include "ura.hpp"
#include <string>
#include <iostream>

// U main datoteci mozete testirati vas kod na proizvoljan nacin.

int main(int argc, char* argv[]) {

  const char* s{"kisik"};
  // int size_ = sizeof(s)/sizeof(s[0]);
  bool p =  palindrome(s, 5);
  std::cout << p<< std::endl;
}
