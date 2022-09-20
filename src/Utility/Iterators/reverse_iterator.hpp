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
	/* ============================== MEMBER TYPE ============================== */
	public:
		typedef	Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	/* ============================== MEMBER ATTRIBUTES ============================== */
	private:
		iterator_type	_iter;

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
		explicit	reverse_iterator (iterator_type it) : _iter(it)
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

		/* ============================== MEMBER FUNCTION ============================== */
		/*
		** Return base iterator
		** Returns a copy of the base iterator.
		** The base iterator is an iterator of the same
		** type as the one used to construct the reverse_iterator,
		** but pointing to the element next to the one the reverse_iterator
		** is currently pointing to (a reverse_iterator has always an offset
		** of -1 with respect to its base iterator).
		** @param none none
		** @return A copy of the base iterator, which iterates in the opposite direction.
		*/
		iterator_type base() const
		{
			return (this->_iter);
		}

		/* ============================== OPERATORS OVERLOADING ============================== */
		/*
		** Dereference iterator
		** Returns a reference to the element pointed to by the iterator.
		** Internally, the function decreases a copy of its base iterator
		** and returns the result of dereferencing it.
		** The iterator shall point to some object in order to be dereferenceable.
		** @param none none
		** @return A reference to the element pointed by the iterator.
		*/
		reference operator*() const
		{
			iterator_type it(this->_iter);

			return (*(--it));
		}

		/*
		** Addition operator
		** Returns a reverse iterator pointing to the element
		** located n positions away from the element the iterator
		** currently points to.
		** Internally, the function applies the binary operator-
		** on the base iterator and returns a reverse iterator
		** constructed with the resulting iterator value.
		** Note that this function requires the base iterator
		** to be a random-access iterator.
		** @param n Number of elements to offset.
		** @return An iterator pointing to the element n positions away.
		*/
		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->_iter - n));
		}

		/*
		** Increment iterator position
		** Advances the reverse_iterator by one position.
		** Internally, the pre-increment
		** decrements the base iterator kept by the object (as if applying operator-- to it).
		** @param none none
		** @return The pre-increment returns *this.
		*/
		reverse_iterator& operator++()
		{
			--this->_iter;

			return (*this);
		}

		/*
		** The post-increment
		** @param int overloads the post-increment operator
		** @return The post-increment returns the value *this had before the call.
		*/
		reverse_iterator  operator++(int)
		{
			reverse_iterator it(*this);

			--this->_iter;
			return (it);
		}

		/*
		** Advance iterator
		** Advances the reverse_iterator by n element positions.
		** Internally, the function decreases by n the base iterator
		** kept by the object (as if applying operator-= to it).
		** Note that this function requires the base iterator to
		** be a random-access iterator.
		** @param n Number of elements to offset.
		** @return The reverse iterator itself (*this).
		*/
		reverse_iterator& operator+= (difference_type n)
		{
			this->_iter -= n;

			return (*this);
		}

		/*
		** Subtraction operator
		** Returns a reverse iterator pointing to the element located n
		** positions before the element the iterator currently points to.
		** Internally, the function applies the binary operator+ on
		** the base iterator and returns a reverse iterator constructed
		** with the resulting iterator value.
		** Note that this function requires the base iterator
		** to be a random-access iterator.
		** @param n Number of elements to offset.
		** @return An iterator pointing to the element n positions before the currently pointed one.
		*/
		reverse_iterator operator- (difference_type n) const
		{
			return (reverse_iterator(this->_iter + n));
		}

		/*
		** Decrease iterator position
		** Decreases the reverse_iterator by one position.
		** Internally, the pre-decrement increments the base
		** iterator kept by the object (as if applying operator++ to it).
		** @param none none
		** return The pre-decrement returns *this.
		*/
		reverse_iterator& operator--()
		{
			++this->_iter;

			return (*this);
		}

		/*
		** The post-decrement
		** @param int the overloads the post-decrement operator
		** return The post-decrement returns the value *this had before the call.
		*/
		reverse_iterator  operator--(int)
		{
			reverse_iterator it((*this));

			++this->_iter;
			return (it);
		}

		/*
		** Retrocede iterator
		** Descreases the reverse_iterator by n element positions.
		** Internally, the function increases by n the base iterator
		** kept by the object (as if applying operator+= to it).
		** Note that this function requires the base iterator
		** to be a random-access iterator.
		** @param n Number of elements to offset.
		** @return The reverse iterator itself (*this).
		*/
		reverse_iterator& operator-= (difference_type n)
		{
			this->_iter += n;

			return (*this);
		}

		/*
		** Dereference iterator
		** Returns a pointer to the element pointed to by the iterator
		** (in order to access one of its members).
		** Internally, the function calls operator* and returns its address
		** @param none none
		** @return A pointer to the element pointed by the iterator.
		*/
		pointer operator->() const
		{
			return (&this->operator*());
		}


		/*
		** Dereference iterator with offset
		** Accesses the element located n positions away
		** from the element currently pointed to by the iterator.
		** If such an element does not exist, it causes undefined behavior.
		** Internally, the function accesses the proper element of
		** its base iterator, returning the same as: base()[-n-1].
		** @param n Number of elements to offset.
		** @return A reference to the element n positions away from the element currently pointed by the iterator
		*/
		reference operator[] (difference_type n) const
		{
			assert(n >= 0);
			return (this->base()[-n - 1]);
		}

		/*
		** Overload
		*/
		reverse_iterator &operator=(reverse_iterator const &rhs)
		{
			this->_iter = rhs.base();
			return (*this);
		}
};

/* ============================== NON-MEMBER FUNCTION OVERLOADING ============================== */
/*
** Addition operator
** Returns a reverse iterator pointing to the element
** located n positions away from the element pointed to by rev_it.
** The function returns the same as: rev_it+n (see reverse_iterator::operator+).
** This operator is also overloaded as a member function to return a reverse
** iterator offset by -n element positions (see reverse_iterator::operator-).
** @param n Number of elements to offset.
** @param rev_it, Reverse iterator.
** @return An iterator pointing to the element n positions away from rev_it.
*/
template <class Iterator>
reverse_iterator<Iterator> operator+ (
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>& rev_it)
{
	return (rev_it + n);
}

/*
** Subtraction operator
** Returns the distance between lhs and rhs.
** The function returns the same as subtracting
** lhs's base iterator from rhs's base iterator
** @param lhs reverse_iterator objects (to the left- and right-hand side of the operator, respectively), having both the same template parameter (Iterator)
** @param rhs reverse_iterator objects (to the left- and right-hand side of the operator, respectively), having both the same template parameter (Iterator).
** @return The number of elements between lhs and rhs.
*/
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs)
{
	return (rhs.base() - lhs.base());
}

/* ============================== RELATIONAL OPERATORS ============================== */

/*
** operator on:
** |--------------------------------------
** | reverse iterators  | base iterators |
** |--------------------------------------
** | ==				    |	==			 |
** | !=				    |	!=			 |
** | <				    |	>			 |
** | <=				    |	>=			 |
** | >				    |	<			 |
** | >=				    |	<=			 |
** |--------------------------------------
*/
template <class Iterator>
bool operator==(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!= (
	const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator< (
	const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<= (
	const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool operator> (
	const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator>= (
	const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

};