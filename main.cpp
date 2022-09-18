
# include "src/containers/Vector.hpp"
# include <iostream>
# include "src/Utility/algorithms.hpp"

# include <vector>

int main()
{
    ft::Vector<int> v(4, 5);
    ft::Vector<int>::reverse_iterator my_rit2(v.end());
    ft::Vector<int>::const_reverse_iterator c_it, c_ob(v.end());
    c_it = my_rit2;
}
