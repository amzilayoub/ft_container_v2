#include <iostream>     // std::cout, std::boolalpha
#include <algorithm>    // std::lexicographical_compare
#include <cctype>       // std::tolower

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1) == std::tolower(c2); }

int main () {
  char foo[]="aaaa";
  char bar[]="baaa";


  std::cout << std::boolalpha;

  std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";
  std::cout << "Using default comparison (operator<): ";
  std::cout << std::lexicographical_compare(foo,foo+4,bar,bar+4);
  std::cout << '\n';

  std::cout << "Using mycomp as comparison object: ";
  std::cout << std::lexicographical_compare(foo,foo+4,bar,bar+4,mycomp);
  std::cout << '\n';

  return 0;
}