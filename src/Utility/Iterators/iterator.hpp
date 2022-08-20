/*
** An iterator is an object that points to an element inside a container.
** Like a pointer, an iterator can be used to access the element it points
** to and can be moved through the content of the container. Each container
** in the C++ Standard Library provides its own iterator, as well as some methods to retrieve it.
** Using iterators is quite easy: obtain an instance from a container,
** move it around where needed and then get the pointed element.
** 
** Concretely, an iterator is a simple class that provides a bunch of operators:
** increment ++, dereference * and few others which make it very similar to a pointer
** and the arithmetic operations you can perform on it. In fact, iterators are a generalization
** of pointers, which are often used as a foundation when writing the iterator itself.
** 
** Iterators are one of the building blocks of the Standard Library containers,
** but they are also useful when you want to provide the ability to iterate
** over elements of a custom container that you wrote yourself:
** this is what I want to investigate in the present article.
** Adding iterators to your containers will make them compatible
** with the range-based for loops and the C++ Algorithms library:
** a collection of functions for searching, sorting,
** counting and manipulating containers, based on iterators.
*/


# pragma once

namespace ft
{

template <
		class Category,              // iterator::iterator_category
        class T,                     // iterator::value_type
        class Distance = ptrdiff_t,  // iterator::difference_type
        class Pointer = T*,          // iterator::pointer
        class Reference = T&         // iterator::reference
        >
class iterator
{

	/* ============================== MEMBER TYPE ============================== */
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };


};