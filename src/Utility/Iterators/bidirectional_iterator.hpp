/*
** Bidirectional iterators are iterators that can be used to access
** the sequence of elements in a range in both directions (towards the end and towards the beginning).
** All random-access iterators are also valid bidirectional iterators.
** There is not a single type of bidirectional iterator: Each container may
** define its own specific iterator type able to iterate through it and access its elements.
*/

# pragma once
# include "./iterator.hpp"
# include "./iterator_traits.hpp"
# include <iterator>

namespace ft
{

template<typename T>
class bidirectional_iterator : public ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >
{
	/* ============================== MEMBER TYPE ============================== */
	public:
		/*
		** Defining member type for the node object
		*/
        typedef typename ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::value_type			value_type;
        typedef typename ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::difference_type	difference_type;
        typedef typename ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::pointer			pointer;
        typedef typename ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::reference			reference;
        typedef typename ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::iterator_category	iterator_category;
		
		/*
		** Defining member type for return value of the node object (AKA: pair<key, value>)
		*/
		typedef typename T::value_type																				pair_value_type;
		typedef typename T::value_type																				&ref_pair_type;
		typedef typename T::value_type																				*pointer_pair_type;
	
	/* ============================== MEMBER ATTRIBUTES ============================== */
	private:
		value_type	*_iter;

	/* ============================== CONSTRUCTOR/DESTRUCTORS ============================== */
	public:
		bidirectional_iterator(pointer ptr = NULL) : _iter(ptr)
		{
		}

		bidirectional_iterator(bidirectional_iterator const &rhs) : _iter(rhs._iter)
		{
		}

		operator bidirectional_iterator<const value_type>()
		{
			return (bidirectional_iterator<const value_type>(this->_iter));
		}

		value_type *base()
		{
			return (this->_iter);
		}
	
	/* ============================== OPERATORS ============================== */
	public:
		bool operator==(bidirectional_iterator const &rhs)
		{
			return (this->_iter == rhs._iter);
		}

		bool operator!=(bidirectional_iterator const &rhs)
		{
			return (this->_iter != rhs._iter);
		}

		ref_pair_type	operator*() const
		{
			return (this->_iter->operator*());
		}
		
		pointer_pair_type	operator->() const
		{
			return &(this->operator*());
		}

		bidirectional_iterator &operator=(bidirectional_iterator const &rhs)
		{
			this->_iter = rhs._iter;

			return ((*this));
		}

		bidirectional_iterator &operator++()
		{
			this->_iter = this->_iter->operator++();

			return (*this);
		}
		
		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp(*this);

			++(*this);
			return (tmp);
		}
		
		bidirectional_iterator &operator--()
		{
			this->_iter = this->_iter->operator--();

			return (*this);
		}

		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp(*this);

			--(*this);
			return (tmp);
		}
};

};