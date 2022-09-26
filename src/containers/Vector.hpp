/*
** VECTOR:
** Vectors are sequence containers representing arrays that can change in size.
** Just like arrays, Vectors use contiguous storage locations for their elements,
** which means that their elements can also be accessed using offsets on regular pointers to its elements,
** and just as efficiently as in arrays. But unlike arrays, their size can change dynamically,
** with their storage being handled automatically by the container.
** 
** Internally, Vectors use a dynamically allocated array to store their elements.
** This array may need to be reallocated in order to grow in size when new elements are inserted,
** which implies allocating a new array and moving all elements to it.
** This is a relatively expensive task in terms of processing time,
** and thus, Vectors do not reallocate each time an element is added to the container.
** 
** Instead, Vector containers may allocate some extra storage to accommodate for possible growth,
** and thus the container may have an actual capacity greater than the storage strictly needed to
** contain its elements (i.e., its size). Libraries can implement different strategies for growth
** to balance between memory usage and reallocations, but in any case,
** reallocations should only happen at logarithmically growing intervals of size so that
** the insertion of individual elements at the end of the Vector can be provided with amortized
** constant time complexity (see push_back).
** 
** Therefore, compared to arrays, Vectors consume more memory in exchange for the ability to manage
** storage and grow dynamically in an efficient way.
** 
** Compared to the other dynamic sequence containers
** (deques, lists and forward_lists),
** Vectors are very efficient accessing its elements (just like arrays) and
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
# include "../Utility/enable_if.hpp"
# include "../Utility/is_integral.hpp"
# include "../Utility/comparison_helper_functions.hpp"
# include "../Utility/algorithms.hpp"

# include <stdexcept>

# define __VECTOR_GROWTH_SIZE__ 2
# define __EPSILON_SIZE__ 1

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class Vector
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
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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
		explicit Vector(const allocator_type& alloc = allocator_type())
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
		explicit Vector(size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type())
		: _capacity(n), _size(0), _alloc(alloc)
		{
			this->_v = this->_alloc.allocate(n);
			this->assign(n, val);
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
        Vector(InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		: _capacity(0), _size(0), _alloc(alloc)
		{
			this->_size = 0;
			this->assign(first, last);
		}

		Vector(const Vector& x)
        : _capacity(0), _size(0), _alloc(x.get_allocator())
		{
			(*this) = x;
		}

		/*
		** This destroys all container elements, and deallocates
		** all the storage capacity allocated by the Vector using its allocator.
		** @param void void
		** @return none
		*/
		~Vector(void)
		{
            for (size_type i = 0; i < this->size(); i++)
                this->_alloc.destroy(&this->_v[i]);
			this->_alloc.deallocate(this->_v, this->capacity());
		}

		/* ============================== MEMBER FUNCTIONS ============================== */
		/* =================== */
		/* ==== ITERATORS ==== */
		/* =================== */
		/*
		** Return iterator to beginning
		** Returns an iterator pointing to the first element in the Vector.
		** Notice that, unlike member Vector::front,
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
		** Returns an iterator pointing to the first element in the Vector.
		** Notice that, unlike member Vector::front,
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
		** Returns an iterator referring to the past-the-end element in the Vector container.
		** The past-the-end element is the theoretical element
		** that would follow the last element in the Vector.
		** It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard
		** library do not include the element pointed by their
		** closing iterator, this function is often used in
		** combination with Vector::begin to specify a range
		** including all the elements in the container.
		** If the container is empty, this function returns
		** the same as Vector::begin.
		** @param void void
		** @return An iterator to the element past the end of the sequence.
		*/
		iterator end()
		{
			return (iterator(&this->_v[this->size()]));
		}

		/*
		** Returns an iterator referring to the past-the-end element in the Vector container.
		** The past-the-end element is the theoretical element
		** that would follow the last element in the Vector.
		** It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard
		** library do not include the element pointed by their
		** closing iterator, this function is often used in
		** combination with Vector::begin to specify a range
		** including all the elements in the container.
		** If the container is empty, this function returns
		** the same as Vector::begin.
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
		** element in the Vector(i.e., its reverse beginning).
		** Reverse iterators iterate backwards: increasing them moves
		** them towards the beginning of the container.
		** rbegin points to the element right before the one that would
		** be pointed to by member end.
		** Notice that unlike member Vector::back, which returns a reference
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
		** element in the Vector(i.e., its reverse beginning).
		** Reverse iterators iterate backwards: increasing them moves
		** them towards the beginning of the container.
		** rbegin points to the element right before the one that would
		** be pointed to by member end.
		** Notice that unlike member Vector::back, which returns a reference
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
		** preceding the first element in the Vector(which is considered its reverse end).
		** The range between Vector::rbegin and Vector::rend contains all
		** the elements of the Vector(in reverse order).
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
		** preceding the first element in the Vector(which is considered its reverse end).
		** The range between Vector::rbegin and Vector::rend contains all
		** the elements of the Vector(in reverse order).
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
		** Returns the number of elements in the Vector.
		** This is the number of actual objects held in the Vector,
		** which is not necessarily equal to its storage capacity.
		** @param void void
		** @return The number of elements in the container.
		*/
		size_type size() const
		{
			return (this->_size);
		}

		/*
		** Returns the size of the storage space currently allocated for the Vector,
		** expressed in terms of elements.
		** This capacity is not necessarily equal to the Vector size.
		** It can be equal or greater, with the extra space allowing
		** to accommodate for growth without the need to reallocate on each insertion.
		** Notice that this capacity does not suppose a limit on the size of the Vector.
		** When this capacity is exhausted and more is needed,
		** it is automatically expanded by the container (reallocating it storage space).
		** The theoretical limit on the size of a Vector is given by member max_size.
		** @param none none
		** @return The size of the currently allocated storage capacity in the Vector, measured in terms of the number elements it can hold.
		*/
		size_type capacity() const
		{
			return (this->_capacity);
		}

		/*
		** Return maximum size
		** Returns the maximum number of elements that the Vector can hold.
		** This is the maximum potential size the container can reach due
		** to known system or library implementation limitations,
		** but the container is by no means guaranteed to be able to reach that size:
		** it can still fail to allocate storage at any point before that size is reached.
		** @param void void
		** @return The maximum number of elements a Vector container can hold as content.
		*/
		size_type max_size() const
		{
			return (this->_alloc.max_size());
		}

		/*
		** Change size
		** Resizes the container so that it contains n elements.
		** If n is smaller than the current container size,
		** the content is reduced to its first n elements,
		** removing those beyond (and destroying them).
		** If n is greater than the current container size,
		** the content is expanded by inserting at the end as many elements
		** as needed to reach a size of n. If val is specified,
		** the new elements are initialized as copies of val, otherwise,
		** they are value-initialized.
		** If n is also greater than the current container capacity,
		** an automatic reallocation of the allocated storage space takes place.
		** Notice that this function changes the actual content
		** of the container by inserting or erasing elements from it.
		** @param n New container size, expressed in number of elements.
		** @param val Object whose content is copied to the added elements in case that n is greater than the current container size.
		*/
		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->capacity())
			{
				this->_realloc(n);
				this->_fill(this->size(), n, val);
			}
			if (n < this->capacity())
			{
				if (n < this->size())
					for (size_type i = n; i < this->size() - 1; i++)
						this->_alloc.destroy(&this->_v[i]);
				else
					this->_fill(this->size(), n, val);
			}
			this->_size = n;
		}

		/*
		** Test whether Vector is empty
		** Returns whether the Vector is empty (i.e. whether its size is 0).
		** This function does not modify the container in any way.
		** To clear the content of a Vector, see Vector::clear.
		** @param void void
		** @return true if the container size is 0, false otherwise.
		*/
		bool empty() const
		{
			return (this->size() == 0);
		}

		/*
		** Request a change in capacity
		** Requests that the Vector capacity be at least enough to contain n elements.
		** If n is greater than the current Vector capacity,
		** the function causes the container to reallocate its storage increasing
		** its capacity to n (or greater).
		** In all other cases, the function call does not cause a reallocation
		** and the Vector capacity is not affected.
		** This function has no effect on the Vector size and cannot alter its elements.
		** @param n Minimum capacity for the Vector.
		** @return void
		*/
		void reserve (size_type n)
		{
			if (n <= this->capacity())
				return ;
			this->_realloc(n);
		}

		/* ======================== */
		/* ==== ELEMENT ACCESS ==== */
		/* ======================== */
		/*
		** Access element
		** Returns a reference to the element at position n in the Vector container.
		** A similar member function, Vector::at, has the same behavior as this operator function,
		** except that Vector::at is bound-checked and signals
		** if the requested position is out of range by throwing an out_of_range exception.
		** Portable programs should never call this function with an argument n
		** that is out of range, since this causes undefined behavior.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the Vector.
		*/
		reference operator[] (size_type n)
		{
			return (this->_v[n]);
		}
		
		/*
		** Access element
		** Returns a reference to the element at position n in the Vector container.
		** A similar member function, Vector::at, has the same behavior as this operator function,
		** except that Vector::at is bound-checked and signals
		** if the requested position is out of range by throwing an out_of_range exception.
		** Portable programs should never call this function with an argument n
		** that is out of range, since this causes undefined behavior.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the Vector.
		*/
		const_reference operator[] (size_type n) const
		{
			return (this->_v[n]);
		}

		/*
		** Access element
		** Returns a reference to the element at position n in the Vector.
		** The function automatically checks whether n is within
		** the bounds of valid elements in the Vector,
		** throwing an out_of_range exception if it is not (i.e., if n is greater than,
		** or equal to, its size). This is in contrast with member operator[],
		** that does not check against bounds.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the container.
		*/
		reference at (size_type n)
		{
			if (n > this->size())
				throw std::out_of_range("oh boy, it's out of range exception, newbie :(");
			return (this->_v[n]);
		}

		/*
		** Access element
		** Returns a reference to the element at position n in the Vector.
		** The function automatically checks whether n is within
		** the bounds of valid elements in the Vector,
		** throwing an out_of_range exception if it is not (i.e., if n is greater than,
		** or equal to, its size). This is in contrast with member operator[],
		** that does not check against bounds.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the container.
		*/
		const_reference at (size_type n) const
		{
			if (n > this->size())
				throw std::out_of_range("oh boy, it's out of range exception, newbie :(");
			return (this->_v[n]);
		}

		/*
		** Access first element
		** Returns a reference to the first element in the Vector.
		** Unlike member Vector::begin, which returns an iterator to this same element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the first element in the Vector container.
		*/
		reference front()
		{
			return (*(this->_v));
		}
		
		/*
		** Access first element
		** Returns a reference to the first element in the Vector.
		** Unlike member Vector::begin, which returns an iterator to this same element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the first element in the Vector container.
		*/
		const_reference front() const
		{
			return (*(this->_v));
		}

		/*
		** Access last element
		** Returns a reference to the last element in the Vector.
		** Unlike member Vector::end, which returns an iterator just past this element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the last element in the Vector.
		*/
		reference back()
		{
			return (this->_v[this->size() - 1]);
		}

		/*
		** Access last element
		** Returns a reference to the last element in the Vector.
		** Unlike member Vector::end, which returns an iterator just past this element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the last element in the Vector.
		*/
		const_reference back() const
		{
			return (this->_v[this->size() - 1]);
		}

		/* ======================= */
		/* ====== MODIFIERS ====== */
		/* ======================= */
		/*
		** Assigns new contents to the Vector, replacing its current
		** contents, and modifying its size accordingly.
		** In the range version (1), the new contents are elements constructed from
		** each of the elements in the range between first and last, in the same order.
		** If a reallocation happens,the storage needed is allocated using the internal allocator.
		** @param first Input iterators to the initial positions in a sequence
		** @param last Input iterators to the final positions in a sequence
		** @return void
		*/
		template <class InputIterator>
  		void assign (
			  	InputIterator first,
				InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()
				)
		{
			size_type	distance;
			size_type	i;

			distance = std::distance(first, last);
			if (this->size() > distance)
				this->_destroy(distance, this->size());
			if (distance > this->capacity())
				this->reserve(distance);
			this->_destroy(0, this->size());
			this->_size = distance;
			i = -1;
			while(first != last)
				this->_alloc.construct(&this->_v[++i], *(first++));
		}

		/*
		** Assigns new contents to the Vector, replacing its current
		** contents, and modifying its size accordingly.
		** In the fill version (2), the new contents are n elements,
		** each initialized to a copy of val.
		** If a reallocation happens,the storage needed is allocated using the internal allocator.
		** @param n New size for the container.
		** @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
		** @return void
		*/
		void assign (size_type n, const value_type& val)
		{
			if (n < this->size())
				this->_destroy(n, this->size());
			if (n > this->capacity())
				this->reserve(n);
			this->_destroy(0, this->size());
			this->_size = n;
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_v[i], val);
		}

		/*
		** Adds a new element at the end of the Vector, after its current last element.
		** The content of val is copied (or moved) to the new element.
		** This effectively increases the container size by one, which causes an automatic
		** reallocation of the allocated storage space if -and only
		** if- the new Vector size surpasses the current Vector capacity.
		** @param val Value to be copied (or moved) to the new element.
		** @return void
		*/
		void push_back (const value_type& val)
		{
			if (this->size() == this->capacity())
			{
				/*
				** the condition this->capacity() == 0 is set in case the capacity is zero
				** so in this case, the multiplication of this->capacity() * __VECTOR_GROWTH_SIZE__ is 0
				** that's why we add 1 since we cannot reserve a capacity of 0
				*/
				this->reserve((this->capacity() * __VECTOR_GROWTH_SIZE__) + (this->capacity() == 0));
			}
			this->_alloc.construct(&this->_v[this->_size++], val);
		}

		/*
		** Delete last element
		** Removes the last element in the Vector,
		** effectively reducing the container size by one.
		** This destroys the removed element.
		** @param void void
		** @return void
		*/
		void pop_back()
		{
			if (!this->size())
				return ;
			this->_alloc.destroy(&this->_v[--this->_size]);
		}

		/*
		** Insert elements
		** The Vector is extended by inserting new elements before the element at the specified position,
		** effectively increasing the container size by the number of elements inserted.
		** This causes an automatic reallocation of the allocated storage
		** space if -and only if- the new Vector size surpasses the current Vector capacity.
		** Because Vectors use an array as their underlying storage,
		** inserting elements in positions other than the Vector end causes
		** the container to relocate all the elements that were after
		** position to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other
		** kinds of sequence containers (such as list or forward_list).
		** The parameters determine how many elements are inserted and to which values they are initialized:
		** @param position Position in the Vector where the new elements are inserted.
		** @param val Value to be copied (or moved) to the inserted elements.
		** @return An iterator that points to the first of the newly inserted elements.
		*/
		iterator insert (iterator position, const value_type& val)
		{
			size_type pos;

			pos = this->_prepare_insert(position, 1);
			this->_alloc.construct(&this->_v[pos], val);
			++this->_size;
			return (iterator(&this->_v[pos]));
		}
		
		/*
		** Insert elements
		** The Vector is extended by inserting new elements before the element at the specified position,
		** effectively increasing the container size by the number of elements inserted.
		** This causes an automatic reallocation of the allocated storage
		** space if -and only if- the new Vector size surpasses the current Vector capacity.
		** Because Vectors use an array as their underlying storage,
		** inserting elements in positions other than the Vector end causes
		** the container to relocate all the elements that were after
		** position to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other
		** kinds of sequence containers (such as list or forward_list).
		** The parameters determine how many elements are inserted and to which values they are initialized:
		** @param position Position in the Vector where the new elements are inserted.
		** @param n Number of elements to insert. Each element is initialized to a copy of val.
		** @param val Value to be copied (or moved) to the inserted elements.
		** @return void
		*/
		void insert (iterator position,size_type n, const value_type& val)
		{
			size_type pos;
			size_type i;

			pos = (this->_prepare_insert(position, n));
			i = n;
			while (i--)
				this->_alloc.construct(&this->_v[pos--], val);
			this->_size += n;
		}
		
		/*
		** Insert elements
		** The Vector is extended by inserting new elements before the element at the specified position,
		** effectively increasing the container size by the number of elements inserted.
		** This causes an automatic reallocation of the allocated storage
		** space if -and only if- the new Vector size surpasses the current Vector capacity.
		** Because Vectors use an array as their underlying storage,
		** inserting elements in positions other than the Vector end causes
		** the container to relocate all the elements that were after
		** position to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other
		** kinds of sequence containers (such as list or forward_list).
		** The parameters determine how many elements are inserted and to which values they are initialized:
		** @param position Position in the Vector where the new elements are inserted.
		** @param first Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
		** @param last Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
		** @return void
		*/
		template <class InputIterator>
		void insert (
					iterator position,
					InputIterator first,
					InputIterator last,
					typename ft::enable_if<!(ft::is_integral<InputIterator>::value), InputIterator>::type = InputIterator()
					)
		{
			size_type pos;
			size_type distance;

			distance = std::distance(first, last);
			pos = this->_prepare_insert(position, distance);
			while (first != last--)
				this->_alloc.construct(&this->_v[pos--], *(last));
			this->_size += distance;
		}


		/*
		** Erase elements
		** Removes from the Vector either a single element (position) or a range of elements ([first,last)).
		** This effectively reduces the container size by the number of elements removed, which are destroyed.
		** Because Vectors use an array as their underlying storage,
		** erasing elements in positions other than the Vector end causes
		** the container to relocate all the elements after the segment
		** erased to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other kinds of sequence
		** containers (such as list or forward_list).
		** @param position Iterator pointing to a single element to be removed from the Vector.
		** @return An iterator pointing to the new location of the element that followed the last element erased by the function call
		*/
		iterator erase (iterator position)
		{
			size_type distance;
			size_type i;

			distance = std::distance(this->begin(), position);
			this->_alloc.destroy(&this->_v[distance]);
			i = distance;
			for (; i < this->size() - 1; i++)
				this->_v[i] = this->_v[i + 1];
			this->_alloc.destroy(&this->_v[i]);
			--this->_size;
			return (iterator(&this->_v[distance]));
		}

		/*
		** Erase elements
		** Removes from the Vector either a single element (position) or a range of elements ([first,last)).
		** This effectively reduces the container size by the number of elements removed, which are destroyed.
		** Because Vectors use an array as their underlying storage,
		** erasing elements in positions other than the Vector end causes
		** the container to relocate all the elements after the segment
		** erased to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other kinds of sequence
		** containers (such as list or forward_list).
		** @param first Iterators specifying a range within the Vector] to be removed: [first,last)
		** @param last Iterators specifying a range within the Vector] to be removed: [first,last)
		** @return An iterator pointing to the new location of the element that followed the last element erased by the function call
		*/
		iterator erase (iterator first, iterator last)
		{
			size_type	first_element_dst;
			size_type	last_element_dst;
			size_type	first_it;
			size_type	last_it;
			
			first_element_dst = std::distance(this->begin(), first);
			last_element_dst = std::distance(this->begin(), last);
			while (first != last)
			{
				this->_alloc.destroy(&(*first));
				++first;
			}
			first_it = first_element_dst;
			last_it = last_element_dst;
			while (last_it < this->size())
				this->_v[first_it++] = this->_v[last_it++];
			while (first_it < this->size())
				this->_alloc.destroy(&this->_v[first_it++]);
			this->_size -= (last_element_dst - first_element_dst);
			return (iterator(&this->_v[first_element_dst]));
		}

		/*
		** Swap content
		** Exchanges the content of the container by the content of x,
		** which is another Vector object of the same type. Sizes may differ.
		** After the call to this member function, the elements in this container
		** are those which were in x before the call, and the elements of x
		** are those which were in this. All iterators,
		** references and pointers remain valid for the swapped objects.
		** Notice that a non-member function exists with the same name,
		** swap, overloading that algorithm with an optimization that behaves like this member function.
		** @param x Another Vector container of the same type
		** @return void
		*/
		void swap (Vector& x)
		{
			value_type		*tmp_v;
			size_type		tmp_capacity;
			size_type		tmp_size;
			allocator_type	tmp_alloc;

			tmp_v = x._v;
			tmp_capacity = x._capacity;
			tmp_size = x._size;
			tmp_alloc = x._alloc;

			x._v = this->_v;
			x._capacity = this->_capacity;
			x._size = this->_size;
			x._alloc = this->_alloc;

			this->_v = tmp_v;
			this->_capacity = tmp_capacity;
			this->_size = tmp_size;
			this->_alloc = tmp_alloc;
		}

		/*
		** Clear content
		** Removes all elements from the Vector (which are destroyed),
		** leaving the container with a size of 0.
		** A reallocation is not guaranteed to happen,
		** and the Vector capacity is not guaranteed to change due to calling this function
		** @param void void
		** @return void
		*/
		void clear()
		{
			this->erase(this->begin(), this->end());
		}

		/* ======================== */
		/* ======= ALLOATOR ======= */
		/* ======================== */
		/*
		** Returns a copy of the allocator object associated with the Vector.
		** @param none none
		** @return The allocator.
		*/
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}

		/* ============================== OPERATORS ============================== */
		/*
		** Assigns new contents to the container,
		** replacing its current contents, and modifying its size accordingly.
		** Copies all the elements from x into the container.
		** The container preserves its current allocator,
		** which is used to allocate storage in case of reallocation.
		** @param x A Vector object of the same type
		** @return *this
		*/
		Vector& operator= (const Vector& x)
		{
			if (this == &x)
				return (*this);
			if (this->capacity() == x.capacity())
			{
				this->_destroy(0, this->size());
				this->_alloc = x.get_allocator();
				for (size_type i = 0 ; i < x.size(); i++)
					this->_alloc.construct(&this->_v[i], x._v[i]);
				this->_size = x.size();
				return (*this);
			}
			this->_destroy(0, this->capacity());
			if (this->capacity())
				this->_alloc.deallocate(this->_v, this->capacity());
			this->_size = x.size();
			this->_capacity = x.capacity();
			this->_alloc = x.get_allocator();
			this->_v = nullptr;
			if (!x.capacity())
				return (*this);
			this->_v = this->_alloc.allocate(x.capacity());
			for (size_type i = 0; i < this->size(); i++)
				this->_alloc.construct(&this->_v[i], x[i]);
			return (*this);
		}
		/* ============================== HELPER FUNCTIONS ============================== */
		private:
			/*
			** This function will fill the array from [start, end)
			** @param start starting position
			** @param end ending position
			** @param val default value to be in place
			** @return void
			*/
			void	_fill(std::size_t start, std::size_t end, value_type &val)
			{
				for (; start < end; start++)
					this->_alloc.construct(&this->_v[start], val);
			}

			/*
			** This function will destroy the array from [start, end)
			** @param start starting position
			** @param end ending position
			** @return void
			*/
			void	_destroy(std::size_t start, std::size_t end)
			{
				for (; start < end; start++)
					this->_alloc.destroy(&this->_v[start]);
			}

			/*
			** reallocating the array and make the capacity bigger to fit n element
			** @param n new capacity
			** @return void
			*/
			void	_realloc(std::size_t &n)
			{
				value_type *tmp;

				if (n == this->capacity())
					return ;

				tmp = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->size(); i++)
				{
					this->_alloc.construct(&tmp[i], this->_v[i]);
					this->_alloc.destroy(&this->_v[i]);
				}
				if (this->capacity())
					this->_alloc.deallocate(this->_v, this->capacity());
				this->_v = tmp;
				this->_capacity = n;
			}

			/*
			** Insert elements
			** The Vector is extended by inserting new elements before the element at the specified position,
			** effectively increasing the container size by the number of elements inserted.
			** This causes an automatic reallocation of the allocated storage
			** space if -and only if- the new Vector size surpasses the current Vector capacity.
			** Because Vectors use an array as their underlying storage,
			** inserting elements in positions other than the Vector end causes
			** the container to relocate all the elements that were after
			** position to their new positions. This is generally an inefficient operation
			** compared to the one performed for the same operation by other
			** kinds of sequence containers (such as list or forward_list).
			** The parameters determine how many elements are inserted and to which values they are initialized:
			** @param position Position in the Vector where the new elements are inserted.
			** @param n Number of elements to insert. Each element is initialized to a copy of val.
			** @param val Value to be copied (or moved) to the inserted elements.
			** @return void
			*/
			size_type _prepare_insert (iterator position, size_type n)
			{
				size_type	distance;
				size_type	i;
				size_type	n_element;

				n_element = n;
				distance = std::distance(this->begin(), position);
				if (this->size() + n > this->capacity())
					this->reserve(((this->capacity() * 2) > this->size() + n) ? (this->capacity() * 2) : this->size() + n);
				/*
				** Here I substract a 1 since we will start the process from 0
				*/
				i = this->size() + n - 1;
				for (size_type j = 0; j < n; j++)
					this->_alloc.construct(&this->_v[this->size() + j], value_type());
				for (; i >= distance + n; i--)
					std::swap(this->_v[i], this->_v[i - n]);
				return (i);
			}
};


/* ============================== NON-FUNCTIONS MEMBER FUNCTION OVERLOADS ============================== */
/*
** Exchange contents of Vectors
** The contents of container x are exchanged with those of y.
** Both container objects must be of the same type (same template parameters),
** although sizes may differ.
** After the call to this member function, the elements in x are those which
** were in y before the call, and the elements of y are those which were in x.
** All iterators, references and pointers remain valid for the swapped objects.
** This is an overload of the generic algorithm swap that improves its performance
** by mutually transferring ownership over their assets to the other container 
** i.e., the containers exchange references to their data,
** without actually performing any element copy or movement): It behaves as if x.swap(y) was called.
** @param x Vector containers of the same type
** @param y Vector containers of the same type
** @return void
*/
template <class T, class Alloc>
void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
{
	x.swap(y);
}


/* ============================== RELATIONAL OPERATORS ============================== */
/*
** Relational operators for Vector
** Performs the appropriate comparison operation between the Vector containers lhs and rhs.
** The equality comparison (operator==) is performed by first comparing sizes,
** and if they match, the elements are compared sequentially using operator==,
** stopping at the first mismatch (as if using algorithm equal).
** The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare,
** which compares the elements sequentially using operator< in a reciprocal manner
** (i.e., checking both a<b and b<a) and stopping at the first occurrence.
** @param lhs Vector containers
** @param rhs Vector containers
** @return true if the condition holds, and false otherwise.
*/
template <class T, class Alloc>
bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template <class T, class Alloc>
bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(
			lhs.begin(),lhs.end(),
			rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
{
	return (!(rhs > lhs));
}

};
