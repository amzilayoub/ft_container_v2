
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
  ft::Map<int, char> my_m;
	for (int i = 0; i < 1e2; i++)
		my_m.insert(ft::make_pair(i, 'A'));

	ft::Map<int, char>::reverse_iterator my_rit2(my_m.end());
	ft::Map<int, char>::const_reverse_iterator c_it, c_ob(my_m.end());
	c_it = my_rit2;
	std::cout << (*(*my_rit2)).first << std::endl;
	// EQUAL(my_rit2->first == c_it->first && my_rit2->first == c_ob->first);
}