/*
** Iterator traits
** Traits class defining properties of iterators.
** Standard algorithms determine certain properties of the iterators
** passed to them and the range they represent by using the members of
** the corresponding iterator_traits instantiation.
** For every iterator type, a corresponding specialization of iterator_traits class template
** shall be defined.
** 
** Note: For output iterators that are not at least forward iterators,
** any of these member types (except for iterator_category) may be defined as void.
** The iterator_traits class template comes with a default definition
** that obtains these types from the iterator type itself (see below).
** It is also specialized for pointers (T*) and pointers to const (const T*).
** Note that any custom class will have a valid instantiation of iterator_traits
** if it publicly inherits the base class std::iterator.
*/

# pragma once

namespace ft
{

template <class T>
struct iterator_traits {
	typedef typename T::value_type value_type;
	typedef typename T::difference_type difference_type;
	typedef typename T::iterator_category iterator_category;
	typedef typename T::pointer pointer;
	typedef typename T::reference reference;
};

};
