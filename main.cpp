
# include "src/containers/Vector.hpp"
# include <iostream>

int main()
{
    ft::vector<int> array(5);

    array[0] = 1;
    array[1] = 22;
    array[2] = 33;
    ft::vector<int>::iterator it = array.begin();
    for (; it != array.end(); it++)
    {
        std::cout << (*it) << std::endl;
    }
}