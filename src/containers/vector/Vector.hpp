/*
** VECTOR:
** Vectors are sequence containers representing arrays that can change in size.
** Just like arrays, vectors use contiguous storage locations for their elements,
** which means that their elements can also be accessed using offsets on regular pointers to its elements,
** and just as efficiently as in arrays. But unlike arrays, their size can change dynamically,
** with their storage being handled automatically by the container.
** 
** Internally, vectors use a dynamically allocated array to store their elements.
** This array may need to be reallocated in order to grow in size when new elements are inserted,
** which implies allocating a new array and moving all elements to it.
** This is a relatively expensive task in terms of processing time,
** and thus, vectors do not reallocate each time an element is added to the container.
** 
** Instead, vector containers may allocate some extra storage to accommodate for possible growth,
** and thus the container may have an actual capacity greater than the storage strictly needed to
** contain its elements (i.e., its size). Libraries can implement different strategies for growth
** to balance between memory usage and reallocations, but in any case,
** reallocations should only happen at logarithmically growing intervals of size so that
** the insertion of individual elements at the end of the vector can be provided with amortized
** constant time complexity (see push_back).
** 
** Therefore, compared to arrays, vectors consume more memory in exchange for the ability to manage
** storage and grow dynamically in an efficient way.
** 
** Compared to the other dynamic sequence containers
** (deques, lists and forward_lists),
** vectors are very efficient accessing its elements (just like arrays) and
** relatively efficient adding or removing elements from its end.
** For operations that involve inserting or removing elements at positions other than the end,
** they perform worse than the others, and have less consistent iterators and references
** than lists and forward_lists.
** 
*/

# pragma once

# include <memory>

namespace ft
{

template < class T, class Alloc = allocator<T> >
class vector
{
	private:
		value_type		*_v;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	public:
		/* The first template parameter (T) */
		typedef T											value_type;
		
		/* 	The second template parameter (Alloc) */
		typedef Alloc										allocator_type;
	
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		/* a signed integral type, identical to: ptrdiff_t */
		typedef typename allocator_type::difference_type	difference_type;

		/* an unsigned integral type that can represent any non-negative value of difference_type */
		typedef typename allocator_type::size_type	size_type;


	/* ============================== CONSTRUCTORS/DESTRUCTOR ============================== */
	
};

};