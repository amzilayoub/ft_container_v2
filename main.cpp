
# include "src/containers/Vector.hpp"
# include <iostream>

int main()
{
    ft::vector<int> array(5);

    array[0] = 1;
    array[1] = 22;
    array[2] = 33;
    array.insert(array.begin(), 50);
    array.push_back(array[0]);
    ft::vector<int>::iterator it = array.begin();
    for (; it != array.end(); it++)
    {
        std::cout << (*it) << std::endl;
    }
}

// # include <vector>

// int main()
// {
//     std::vector<int> list;

//     list.insert(list.end() + 2, 1);
// }