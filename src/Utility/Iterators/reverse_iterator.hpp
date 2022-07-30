/*
** reverse_iterator is an iterator adaptor that reverses
** the direction of a given iterator, which must be at least
** a LegacyBidirectionalIterator or model bidirectional_iterator (since C++20).
** In other words, when provided with a bidirectional iterator,
** std::reverse_iterator produces a new iterator that moves from
** the end to the beginning of the sequence defined by the underlying bidirectional iterator.
** For a reverse iterator r constructed from an iterator i,
** the relationship &*r == &*(i-1) is always true (as long as r is dereferenceable);
** thus a reverse iterator constructed from a one-past-the-end iterator
** dereferences to the last element in a sequence.
** This is the iterator returned by member functions
** rbegin() and rend() of the standard library containers.
*/

# pragma once

#  include "./iterator_traits.hpp"
namespace ft
{

template <class Iterator>
class reverse_iterator
{
	/* ============================== MEMBER ATTRIBUTES ============================== */
	private:
		Iterator	_iter;

	/* ============================== MEMBER TYPE ============================== */
	public:
		typedef	Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	/* ============================== CONSTRUCTOR/DESTRUCTOR ============================== */
	public:
		/*
		** default constructor:
		** Constructs a reverse iterator that points to no object.
		** The internal base iterator is value-initialized.
		*/
					reverse_iterator() : _iter() {}
		
		/*
		** initalization constructor
		** Constructs a reverse iterator from some original iterator it.
		** The behavior of the constructed object replicates the original,
		** except that it iterates through its pointed elements in the reverse order.
		** @param it An iterator, whose sense of iteration is inverted in the constructed object.
		*/
		explicit	reverse_iterator (iterator_type it) : _iter(--it)
		{
		}

		/*
		** copy / type-cast constructor
		** Constructs a reverse iterator from some other reverse iterator.
		** The constructed object keeps the same sense of iteration as rev_it.
		** @param rev_t An iterator of a reverse_iterator type, whose sense of iteration is preserved.
		*/
		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iter(rev_it.base())
		{
		}
};

};