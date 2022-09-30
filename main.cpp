
# include "src/containers/vector.hpp"
# include "src/containers/stack.hpp"
# include <iostream>
# include "src/Utility/algorithms.hpp"
# include "src/Utility/avl.hpp"
# include <stack>

# define EQUAL(x) std::cout << (x) << std::endl
#define TIME_FAC 20
# include <vector>
#include <sys/time.h>
# include <map>

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

int main()
{
    // ft::AVL<int, int> tree;
	// tree.root = tree.insert(tree.root, ft::make_pair(30, 10));
	// tree.root = tree.insert(tree.root, ft::make_pair(10, 10));
	// tree.root = tree.insert(tree.root, ft::make_pair(100, 10));
	// tree.root = tree.insert(tree.root, ft::make_pair(999, 10));
	// tree.root = tree.insert(tree.root, ft::make_pair(999, 999));

	// tree.print(tree.root);
	// std::cout << "==========" << std::endl;
	// tree.root = tree.left_rotation(tree.root);
	// tree.print(tree.root);
}
