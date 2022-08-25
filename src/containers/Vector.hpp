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
# include "../Utility/Iterators/random_access_iterator.hpp"
# include "../Utility/Iterators/reverse_iterator.hpp"

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class vector
{

	/* ============================== MEMBER TYPE ============================== */
	public:
		/* The first template parameter (T) */
		typedef T											value_type;
		
		/* 	The second template parameter (Alloc) */
		typedef Alloc													allocator_type;
	
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

		/* a random access iterator to value_type */
		typedef typename ft::random_access_iterator<value_type>			iterator;
		typedef typename ft::random_access_iterator<const value_type>	const_iterator;

		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;

		/* a signed integral type, identical to: ptrdiff_t */
		typedef typename allocator_type::difference_type				difference_type;

		/* an unsigned integral type that can represent any non-negative value of difference_type */
		typedef typename allocator_type::size_type						size_type;


	/* ============================== MEMBER ATTRIBUTES ============================== */
	private:
		value_type		*_v;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	/* ============================== CONSTRUCTORS/DESTRUCTOR ============================== */
	public:
		/*
		** empty container constructor (default constructor)
		** Constructs an empty container, with no elements.
		** @param alloc Allocator object.
		** @return none none
		*/
		explicit vector (const allocator_type& alloc = allocator_type())
		: _v(nullptr), _capacity(0), _size(0), _alloc(alloc)
		{
		}

		/*
		** fill constructor
		** Constructs a container with n elements. Each element is a copy of val.
		** @param n Initial container size
		** @param val Value to fill the container with
		** @param alloc Allocator object.
		** @return none none
		*/
		explicit vector (size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type())
		: _capacity(n), _size(n), _alloc(alloc)
		{
			this->_v = this->_alloc.allocate(n);
			for (int i = 0; i < n; i++)
				this->_alloc.construct(&this->_v[i], val);
		}

		/*
		** range constructor
		** Constructs a container with as many elements as the range [first,last),
		** with each element constructed from its corresponding element in that range,
		** in the same order.
		** @param first Input iterators to the initial positions in a range
		** @param last Input iterators to the final positions in a range
		** @param alloc Allocator object.
		** @return none none
		*/
		template <class InputIterator>
        vector (InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type())
		: _alloc(alloc)
		{
			this->_size = 0;
			this->_capacity = std::distance(first, last);
			this->_alloc.allocate(this->_capacity);
			while (first != last)
			{
				this->_alloc.construct(&this->_v[this->_size], *(first++));
				++this->_size;
			}
		}

		vector (const vector& x) : _alloc(x.get_allocator())
		{
			if (this != &x)
				(*this) = x;
		}

		/*
		** This destroys all container elements, and deallocates
		** all the storage capacity allocated by the vector using its allocator.
		** @param void void
		** @return none
		*/
		~vector(void)
		{
			this->_alloc.deallocate(this->_v, this->_capacity);
		}

		/* ============================== MEMBER FUNCTIONS ============================== */
		/* =================== */
		/* ==== ITERATORS ==== */
		/* =================== */
		/*
		** Return iterator to beginning
		** Returns an iterator pointing to the first element in the vector.
		** Notice that, unlike member vector::front,
		** which returns a reference to the first element,
		** this function returns a random access iterator pointing to it.
		** If the container is empty,
		** the returned iterator value shall not be dereferenced.
		** @param none none
		** @return An iterator to the beginning of the sequence container.
		*/
		iterator begin()
		{
			return (iterator(this->_v));
		}

		/*
		** Return iterator to beginning
		** Returns an iterator pointing to the first element in the vector.
		** Notice that, unlike member vector::front,
		** which returns a reference to the first element,
		** this function returns a random access iterator pointing to it.
		** If the container is empty,
		** the returned iterator value shall not be dereferenced.
		** @param none none
		** @return An iterator to the beginning of the sequence container.
		*/
		const_iterator begin() const
		{
			return (const_iterator(this->_v));
		}

		/*
		** Returns an iterator referring to the past-the-end element in the vector container.
		** The past-the-end element is the theoretical element
		** that would follow the last element in the vector.
		** It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard
		** library do not include the element pointed by their
		** closing iterator, this function is often used in
		** combination with vector::begin to specify a range
		** including all the elements in the container.
		** If the container is empty, this function returns
		** the same as vector::begin.
		** @param void void
		** @return An iterator to the element past the end of the sequence.
		*/
		iterator end()
		{
			return (iterator(&this->_v[this->size()]));
		}

		/*
		** Returns an iterator referring to the past-the-end element in the vector container.
		** The past-the-end element is the theoretical element
		** that would follow the last element in the vector.
		** It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard
		** library do not include the element pointed by their
		** closing iterator, this function is often used in
		** combination with vector::begin to specify a range
		** including all the elements in the container.
		** If the container is empty, this function returns
		** the same as vector::begin.
		** @param void void
		** @return An iterator to the element past the end of the sequence.
		*/
		const_iterator end() const
		{
			return (const_iterator(&this->_v[this->size()]));
		}

		/*
		** Return reverse iterator to reverse beginning
		** Returns a reverse iterator pointing to the last
		** element in the vector (i.e., its reverse beginning).
		** Reverse iterators iterate backwards: increasing them moves
		** them towards the beginning of the container.
		** rbegin points to the element right before the one that would
		** be pointed to by member end.
		** Notice that unlike member vector::back, which returns a reference
		** to this same element, this function returns a reverse random access iterator.
		** @param void void
		** @return A reverse iterator to the reverse beginning of the sequence container.
		*/
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}

		/*
		** Return reverse iterator to reverse beginning
		** Returns a reverse iterator pointing to the last
		** element in the vector (i.e., its reverse beginning).
		** Reverse iterators iterate backwards: increasing them moves
		** them towards the beginning of the container.
		** rbegin points to the element right before the one that would
		** be pointed to by member end.
		** Notice that unlike member vector::back, which returns a reference
		** to this same element, this function returns a reverse random access iterator.
		** @param void void
		** @return A reverse iterator to the reverse beginning of the sequence container.
		*/
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		/*
		** Return reverse iterator to reverse end
		** Returns a reverse iterator pointing to the theoretical element
		** preceding the first element in the vector (which is considered its reverse end).
		** The range between vector::rbegin and vector::rend contains all
		** the elements of the vector (in reverse order).
		** @param void void
		** @return A reverse iterator to the reverse end of the sequence container.
		*/
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}

		/*
		** Return reverse iterator to reverse end
		** Returns a reverse iterator pointing to the theoretical element
		** preceding the first element in the vector (which is considered its reverse end).
		** The range between vector::rbegin and vector::rend contains all
		** the elements of the vector (in reverse order).
		** @param void void
		** @return A reverse iterator to the reverse end of the sequence container.
		*/
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

		/* ================== */
		/* ==== CAPACITY ==== */
		/* ================== */
		/*
		** Returns the number of elements in the vector.
		** This is the number of actual objects held in the vector,
		** which is not necessarily equal to its storage capacity.
		** @param void void
		** @return The number of elements in the container.
		*/
		size_type size() const
		{
			return (this->_size);
		}

		/*
		** Returns the size of the storage space currently allocated for the vector,
		** expressed in terms of elements.
		** This capacity is not necessarily equal to the vector size.
		** It can be equal or greater, with the extra space allowing
		** to accommodate for growth without the need to reallocate on each insertion.
		** Notice that this capacity does not suppose a limit on the size of the vector.
		** When this capacity is exhausted and more is needed,
		** it is automatically expanded by the container (reallocating it storage space).
		** The theoretical limit on the size of a vector is given by member max_size.
		** @param none none
		** @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
		*/
		size_type capacity() const
		{
			return (this->_capacity);
		}

		/*
		** Returns a copy of the allocator object associated with the vector.
		** @param none none
		** @return The allocator.
		*/
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}

		/*
		** Access element
		** Returns a reference to the element at position n in the vector container.
		** A similar member function, vector::at,
		** has the same behavior as this operator function,
		** except that vector::at is bound-checked and signals if the requested position
		** is out of range by throwing an out_of_range exception.
		** Portable programs should never call this function with an argument n
		** that is out of range, since this causes undefined behavior.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the vector.
		*/
		reference operator[] (size_type n)
		{
			return (this->_v[n]);
		}

		/*
		** Access element
		** Returns a reference to the element at position n in the vector container.
		** A similar member function, vector::at,
		** has the same behavior as this operator function,
		** except that vector::at is bound-checked and signals if the requested position
		** is out of range by throwing an out_of_range exception.
		** Portable programs should never call this function with an argument n
		** that is out of range, since this causes undefined behavior.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the vector.
		*/
		const_reference operator[] (size_type n) const
		{
			return (this->_v[n]);
		}


		/* ============================== OPERATORS ============================== */
		/*
		** Assigns new contents to the container,
		** replacing its current contents, and modifying its size accordingly.
		** Copies all the elements from x into the container.
		** The container preserves its current allocator,
		** which is used to allocate storage in case of reallocation.
		** @param x A vector object of the same type
		** @return *this
		*/
		vector& operator= (const vector& x)
		{
			this->_size = x.size();
			this->_capacity = x.capacity();
			for (int i = 0; i < this->_size(); i++)
				this->_alloc.construct(&this->_v[i], x[i]);
		}
};

};