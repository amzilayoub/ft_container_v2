
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
{
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, char> m;
            ft::Map<int, char> my_m;

            for (size_t i = 0; i < 1e3; i++)
            {
                m.insert(std::make_pair(i, 'X'));
                my_m.insert(ft::make_pair(i, 'X'));
            }

            std::map<int, char> copy_m(m);
            diff = end - start;
            diff = (diff) ? (diff * 20) : 20;

            ft::Map<int, char> my_copy_m(my_m);
        }
        /*---------------------------------------------------------------------------------------------*/
        /*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
        ft::Map<int, char> m1;
        for (int i = 0; i < 10; i++)
            m1.insert(ft::make_pair(i, 'a'));
        ft::Map<int, char> copy_m(m1);
        /*-----------------------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, res1;
        /*--------------------------------------------------------*/
        for (ft::Map<int, char>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::Map<int, char>::iterator it = copy_m.begin(); it != copy_m.end(); ++it) // fill res from copy_m
            res1 += it->second;
        EQUAL(res == res1);
    }
}