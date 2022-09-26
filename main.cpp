
# include "src/containers/vector.hpp"
# include "src/containers/stack.hpp"
# include <iostream>
# include "src/Utility/algorithms.hpp"
# include <stack>

# define EQUAL(x) std::cout << (x) << std::endl
#define TIME_FAC 20
# include <vector>
#include <sys/time.h>

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

int main()
{
    bool cond(false);
    std::vector<int>	vec(100, 2);
    std::vector<int>	vec1(100, 2);

    ft::Stack<int, std::vector<int> > mystack1(vec);
    ft::Stack<int, std::vector<int> > mystack(vec1);
    std::stack<int, std::vector<int> > stack1(vec);
    std::stack<int, std::vector<int> > stack(vec1);
    cond = (mystack ==  mystack1) == (stack == stack1);
}
