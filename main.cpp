
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

# define SETW(x) "|"

using namespace std;
int main ()
{
	time_t start, end, diff;

	std::map<int, std::string> m;
	ft::Map<int, std::string> ft_m;
	for (size_t i = 0; i < 1e6; ++i)
	{
		m.insert(std::make_pair(i, "value"));
		ft_m.insert(ft::make_pair(i, "value"));
	}
	for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		;
	diff = end - start;
	diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

	for (ft::Map<int, std::string>::iterator it = ft_m.begin(); it != ft_m.end(); ++it)
		;
}