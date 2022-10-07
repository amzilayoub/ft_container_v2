
# include "src/containers/vector.hpp"
# include "src/containers/stack.hpp"
# include "src/containers/map.hpp"
# include <iostream>
# include "src/Utility/algorithms.hpp"
# include "src/Utility/avl.hpp"
# include <stack>

# define EQUAL(x) std::cout << (x) << std::endl
#define TIME_FAC 20
# include <vector>
#include <sys/time.h>
# include <map>
# include "src/containers/map.hpp"
#include <iostream>
#include <map>

using namespace std;
int main ()
{
  int psize;
  ft::map<char,int> mymap;
  ft::pair<const char,int>* p;

  // allocate an array of 5 elements using mymap's allocator:
  p=mymap.get_allocator().allocate(5);

  // assign some values to array
  psize = sizeof(ft::map<char,int>::value_type)*5;

  std::cout << "The allocated array has a size of " << psize << " bytes.\n";

  mymap.get_allocator().deallocate(p,5);

  return 0;
}