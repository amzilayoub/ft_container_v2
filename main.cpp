
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

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

int main()
{
	ft::map<int, int> tree;

	tree[80];
	for (int i = 1; i <= 10; i++)
		tree.insert(ft::make_pair(i, i * 10));


	ft::map<int, int> tree1(tree.begin(), tree.end());

	for (int i = -10; i < 0; i++)
		tree.insert(ft::make_pair(i, i * 10));

	// tree1 = tree;
	ft::map<int, int>::iterator it = tree1.begin();
	for (; it != tree1.end();)
	{
		std::cout << it->first << " | " << it->second << std::endl;
		++it;
	}

	std::cout << "==========" << std::endl;


	it = tree.end();
	for (; it != tree.begin();)
	{
		--it;
		std::cout << it->first << " | " << it->second << std::endl;
	}
}
