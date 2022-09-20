
# include "src/containers/vector.hpp"
# include <iostream>
# include "src/Utility/algorithms.hpp"

# define EQUAL(x) std::cout << (x) << std::endl

# include <vector>

int main()
{
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        ft::Vector<std::string>::iterator ft_it;
        // test for an empty vector
        v.push_back("hello");
        ft_v.push_back("hello");
        ft_it = ft_v.begin();
        ft_it->length();

        z1 = v.size();
        c1 = v.capacity();
        ft_z1 = ft_v.size();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v.at(i);
        /*---------------------------------------------*/
        // test for a vector with capacity >= size + the new element
        v.reserve(30);
        ft_v.reserve(30);
        v.push_back("string");
        ft_v.push_back("string");
        v.push_back("string");
        ft_v.push_back("string");

        z2 = v.size();
        c2 = v.capacity();
        ft_z2 = ft_v.size();
        ft_c2 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s2 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s2 += ft_v.at(i);
        /*---------------------------------------------------------*/
        // test for a vector with capactiy < size + the new element
        for (size_t i = 0; i < 100; ++i)
            v.push_back("string");

        for (size_t i = 0; i < 100; ++i)
            ft_v.push_back("string");

        z3 = v.size();
        c3 = v.capacity();
        ft_z3 = ft_v.size();
        ft_c3 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s3 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s3 += ft_v.at(i);

        EQUAL((s1 == ft_s1 && c1 == ft_c1));
    }
}
