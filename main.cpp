
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

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

using namespace std;
int main ()
{
{
        bool cond(false);
        // {
        //     time_t start, end, diff;
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m1;
        //     ft::Map<int, std::string> ft_m1;

        //     for (size_t i = 0; i < 1e6; i++)
        //         m1.insert(std::make_pair(i, "string2"));
        //     diff = end - start;
        //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::Maps ---------------------*/
        //     for (size_t i = 0; i < 1e6; i++)
        //         ft_m1.insert(ft::make_pair(i, "string2"));

        //     /*----------------------------------------------------*/
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m_range;
        //     ft::Map<int, std::string> ft_m_range;

        //     m_range.insert(m1.begin(), m1.end());
        //     diff = end - start;
        //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::Maps ---------------------*/
        //     ft_m_range.insert(ft_m1.begin(), ft_m1.end());
        //     /*----------------------------------------------------*/
        // }

        // {
        //     time_t start, end, diff;
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m1;
        //     ft::Map<int, std::string> ft_m1;

        //     m1.insert(std::make_pair(1e9, "string2"));
        //     diff = end - start;
        //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::Maps ---------------------*/
        //     ft_m1.insert(ft::make_pair(1e9, "string2"));
        //     /*----------------------------------------------------*/
        // }

        std::map<char, int> m;
        ft::Map<char, int> ft_m;

        cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();

        // first insert function version (single parameter):
        m.insert(std::pair<char, int>('a', 100));
        m.insert(std::pair<char, int>('z', 200));

        ft_m.insert(ft::pair<char, int>('a', 100));
        ft_m.insert(ft::pair<char, int>('z', 200));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        std::pair<std::map<char, int>::iterator, bool> ret;
        ft::pair<ft::Map<char, int>::iterator, bool> ft_ret;

        ret = m.insert(std::pair<char, int>('z', 500));
        ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

        cond = cond && ret.second == ft_ret.second;

        // second insert function version (with hint position):
        std::map<char, int>::iterator it = m.begin();
        ft::Map<char, int>::iterator ft_it = ft_m.begin();
        m.insert(it, std::pair<char, int>('b', 300));
        m.insert(it, std::pair<char, int>('c', 400));

        ft_m.insert(ft_it, ft::pair<char, int>('b', 300));
        ft_m.insert(ft_it, ft::pair<char, int>('c', 400));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        // third insert function version (range insertion):
        std::map<char, int> anothermap;
        ft::Map<char, int> ft_anothermap;
        anothermap.insert(m.begin(), m.find('c'));
        ft_anothermap.insert(ft_m.begin(), ft_m.find('c'));
        cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());

        cond = cond && compareMaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && compareMaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
        EQUAL(cond);
    }
}