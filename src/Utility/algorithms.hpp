# pragma once

namespace ft
{

/*
** Lexicographical less-than comparison
** Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
** A lexicographical comparison is the kind of comparison generally used to sort words
** alphabetically in dictionaries; It involves comparing sequentially the elements that
** have the same position in both ranges against each other until one element
** is not equivalent to the other. The result of comparing these first non-matching
** elements is the result of the lexicographical comparison.
** If both sequences compare equal until one of them ends,
** the shorter sequence is lexicographically less than the longer one.
** The elements are compared using operator< for the first version,
** and comp for the second. Two elements, a and b are considered equivalent
** if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)).
** @param first1 Input iterators to the initial positions of the first sequence.
** @param last1 Input iterators to the final positions of the first sequence.
** @param first2 Input iterators to the initial positions of the second sequence
** @param last2 Input iterators to the final positions of the second sequence
** @return true if the first range compares lexicographically less than the second. false otherwise
*/
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || (*first2) < (*first1))
			return false;
		else if ((*first1) < (*first2))
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

/*
** Lexicographical less-than comparison
** Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
** A lexicographical comparison is the kind of comparison generally used to sort words
** alphabetically in dictionaries; It involves comparing sequentially the elements that
** have the same position in both ranges against each other until one element
** is not equivalent to the other. The result of comparing these first non-matching
** elements is the result of the lexicographical comparison.
** If both sequences compare equal until one of them ends,
** the shorter sequence is lexicographically less than the longer one.
** The elements are compared using operator< for the first version,
** and comp for the second. Two elements, a and b are considered equivalent
** if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)).
** @param first1 Input iterators to the initial positions of the first sequence.
** @param last1 Input iterators to the final positions of the first sequence.
** @param first2 Input iterators to the initial positions of the second sequence
** @param last2 Input iterators to the final positions of the second sequence
** @param comp Binary function that accepts two arguments of the types pointed by the iterators, and returns a value convertible to bool
** @return true if the first range compares lexicographically less than the second. false otherwise
*/
template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp)
{
	for (; first1 != last1; first1++, first2++)
	{
		if (comp(*first1, *first2))
			return (true);
		else if (comp(*first2, *first1))
			return (false);
	}
	return (first1 == last1) && (first2 != last2);
}

/*
** Test whether the elements in two ranges are equal
** Compares the elements in the range [first1,last1) with
** those in the range beginning at first2, and returns true
** if all of the elements in both ranges match.
** The elements are compared using operator== (or pred, in version (2)).
** @param first1 Input iterators to the initial positions of the first sequence
** @param last1 Input iterators to the final positions of the first sequence
** @param first2 Input iterator to the initial position of the second sequence
** @return	true if all the elements in the range [first1,last1) compare equal
**			to those of the range starting at first2, and false otherwise.
*/
template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
	if (!(*first1 == *first2))
		return false;
	++first1;
	++first2;
	}
	return (true);
}

/*
** Test whether the elements in two ranges are equal
** Compares the elements in the range [first1,last1) with
** those in the range beginning at first2, and returns true
** if all of the elements in both ranges match.
** The elements are compared using operator== (or pred, in version (2)).
** @param first1 Input iterators to the initial positions of the first sequence
** @param last1 Input iterators to the final positions of the first sequence
** @param first2 Input iterator to the initial position of the second sequence
** @param pred	Binary function that accepts two elements as argument (one of each of the two sequences, in the same order),
** 				and returns a value convertible to bool. The value returned indicates whether the elements
**				are considered to match in the context of this function.
** @return	true if all the elements in the range [first1,last1) compare equal
**			to those of the range starting at first2, and false otherwise.
*/
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1)
	{
		if (!pred(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return (true);
}

};