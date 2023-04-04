#include <iostream>

bool palindrome(const char* s, int n)
{
  if(n<2) return true;
  else return s[0] == s[n-1] && palindrome(s+1, n-2);
}


