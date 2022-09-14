# pragma once

/*
** Here's some helper functions that are used in the parameter
** of some other function to compare element like equal(version 2) or lexographical_compare(version 2)
*/

namespace ft
{

template<typename T>
bool	is_great_than_or_equal(T lhs, T rhs)
{
	return (lhs >= rhs);
}

template<typename T>
bool	is_less_than_or_equal(T lhs, T rhs)
{
	return (lhs <= rhs);
}

};