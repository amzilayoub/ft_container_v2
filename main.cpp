
# include "src/containers/Vector.hpp"
# include <iostream>

# include <vector>

int main()
{
    ft::vector<int> array(5);
    ft::vector<int> copy;

    array[0] = 11;
    array[1] = 22;
    array[2] = 33;

    copy.push_back(1);
    copy.push_back(2);
    copy.push_back(3);

	copy.swap(array);
	copy.clear();
	std::cout << "BEGIN = " << (*copy.begin()) << std::endl;
    std::cout << "=======COPY=========" << std::endl;
    ft::vector<int>::iterator it = copy.begin();
	it = copy.begin();
    for (; it != copy.end(); it++)
    {
        std::cout << (*it) << std::endl;
    }

    it = array.begin();
    std::cout << "=======BEFORE ARRAY=========" << std::endl;
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