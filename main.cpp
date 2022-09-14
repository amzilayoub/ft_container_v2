
# include "src/containers/Vector.hpp"
# include <iostream>
# include "src/Utility/algorithms.hpp"

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

	std:: cout << "COMPARAISON" << std::endl;
	std::cout << (copy == array) << std::endl;
	std::cout << (copy != array) << std::endl;
	std::cout << (copy < array) << std::endl;
	std::cout << (copy <= array) << std::endl;
	std::cout << (copy > array) << std::endl;
	std::cout << (copy >= array) << std::endl;
}
