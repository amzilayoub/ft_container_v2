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
# include <stdexcept>

# define __VECTOR_GROWTH_SIZE__ 2
# define __EPSILON_SIZE__ 1

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
		explicit vector(const allocator_type& alloc = allocator_type())
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
		explicit vector(size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type())
		: _capacity(n), _size(n), _alloc(alloc)
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
        vector(InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type())
		: _alloc(alloc)
		{
			this->_size = 0;
			this->_capacity = std::distance(first, last);
			this->_alloc.allocate(this->capacity());
			this->assign(first, last);
		}

		vector(const vector& x) : _alloc(x.get_allocator())
		{
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
			this->_alloc.deallocate(this->_v, this->capacity());
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
		** element in the vector(i.e., its reverse beginning).
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
		** element in the vector(i.e., its reverse beginning).
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
		** preceding the first element in the vector(which is considered its reverse end).
		** The range between vector::rbegin and vector::rend contains all
		** the elements of the vector(in reverse order).
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
		** preceding the first element in the vector(which is considered its reverse end).
		** The range between vector::rbegin and vector::rend contains all
		** the elements of the vector(in reverse order).
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
		** Return maximum size
		** Returns the maximum number of elements that the vector can hold.
		** This is the maximum potential size the container can reach due
		** to known system or library implementation limitations,
		** but the container is by no means guaranteed to be able to reach that size:
		** it can still fail to allocate storage at any point before that size is reached.
		** @param void void
		** @return The maximum number of elements a vector container can hold as content.
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
		** Test whether vector is empty
		** Returns whether the vector is empty (i.e. whether its size is 0).
		** This function does not modify the container in any way.
		** To clear the content of a vector, see vector::clear.
		** @param void void
		** @return true if the container size is 0, false otherwise.
		*/
		bool empty() const
		{
			return (this->size() == 0);
		}

		/*
		** Request a change in capacity
		** Requests that the vector capacity be at least enough to contain n elements.
		** If n is greater than the current vector capacity,
		** the function causes the container to reallocate its storage increasing
		** its capacity to n (or greater).
		** In all other cases, the function call does not cause a reallocation
		** and the vector capacity is not affected.
		** This function has no effect on the vector size and cannot alter its elements.
		** @param n Minimum capacity for the vector.
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
		** Returns a reference to the element at position n in the vector container.
		** A similar member function, vector::at, has the same behavior as this operator function,
		** except that vector::at is bound-checked and signals
		** if the requested position is out of range by throwing an out_of_range exception.
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
		** A similar member function, vector::at, has the same behavior as this operator function,
		** except that vector::at is bound-checked and signals
		** if the requested position is out of range by throwing an out_of_range exception.
		** Portable programs should never call this function with an argument n
		** that is out of range, since this causes undefined behavior.
		** @param n Position of an element in the container.
		** @return The element at the specified position in the vector.
		*/
		const_reference operator[] (size_type n) const
		{
			return (this->_v[n]);
		}

		/*
		** Access element
		** Returns a reference to the element at position n in the vector.
		** The function automatically checks whether n is within
		** the bounds of valid elements in the vector,
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
		** Returns a reference to the element at position n in the vector.
		** The function automatically checks whether n is within
		** the bounds of valid elements in the vector,
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
		** Returns a reference to the first element in the vector.
		** Unlike member vector::begin, which returns an iterator to this same element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the first element in the vector container.
		*/
		reference front()
		{
			return (*(this->_v));
		}
		
		/*
		** Access first element
		** Returns a reference to the first element in the vector.
		** Unlike member vector::begin, which returns an iterator to this same element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the first element in the vector container.
		*/
		const_reference front() const
		{
			return (*(this->_v));
		}

		/*
		** Access last element
		** Returns a reference to the last element in the vector.
		** Unlike member vector::end, which returns an iterator just past this element,
		** this function returns a direct reference.
		** Calling this function on an empty container causes undefined behavior.
		** @param void void
		** @return A reference to the last element in the vector.
		*/
		reference back()
		{
			return (this->_v[this->size() - 1]);
		}
		const_reference back() const
		{
			return (this->_v[this->size() - 1]);
		}

		/* ======================= */
		/* ====== MODIFIERS ====== */
		/* ======================= */
		/*
		** Assigns new contents to the vector, replacing its current
		** contents, and modifying its size accordingly.
		** In the range version (1), the new contents are elements constructed from
		** each of the elements in the range between first and last, in the same order.
		** If a reallocation happens,the storage needed is allocated using the internal allocator.
		** @param first Input iterators to the initial positions in a sequence
		** @param last Input iterators to the final positions in a sequence
		** @return void
		*/
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last)
		{
			size_type	distance;
			size_type	i;

			distance = std::distance(first, last);
			if (this->size() > distance)
				this->_destroy(distance, this->size());
			if (distance > this->capacity())
				this->reserve(distance);
			this->_size = distance;
			i = -1;
			while(first != last)
			{
				this->_alloc.destroy(&this->_v[++i]);
				this->_alloc.construct(this->_v[i], *(first++));
			}
		}

		/*
		** Assigns new contents to the vector, replacing its current
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
			this->_size = n;
			for (size_type i = 0; i < n; i++)
			{
				this->_alloc.destroy(&this->_v[i]);
				this->_alloc.construct(&this->_v[i], val);
			}
		}

		/*
		** Adds a new element at the end of the vector, after its current last element.
		** The content of val is copied (or moved) to the new element.
		** This effectively increases the container size by one, which causes an automatic
		** reallocation of the allocated storage space if -and only
		** if- the new vector size surpasses the current vector capacity.
		** @param val Value to be copied (or moved) to the new element.
		** @return void
		*/
		void push_back (const value_type& val)
		{
			if (this->size() == this->capacity())
				this->reserve((this->capacity() + __EPSILON_SIZE__) * __VECTOR_GROWTH_SIZE__);
			this->_alloc.construct(&this->_v[this->_size++], val);
		}

		/*
		** Delete last element
		** Removes the last element in the vector,
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
		** The vector is extended by inserting new elements before the element at the specified position,
		** effectively increasing the container size by the number of elements inserted.
		** This causes an automatic reallocation of the allocated storage
		** space if -and only if- the new vector size surpasses the current vector capacity.
		** Because vectors use an array as their underlying storage,
		** inserting elements in positions other than the vector end causes
		** the container to relocate all the elements that were after
		** position to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other
		** kinds of sequence containers (such as list or forward_list).
		** The parameters determine how many elements are inserted and to which values they are initialized:
		** @param position Position in the vector where the new elements are inserted.
		** @param val Value to be copied (or moved) to the inserted elements.
		** @return An iterator that points to the first of the newly inserted elements.
		*/
		iterator insert (iterator position, const value_type& val)
		{
			// size_type	distance;
			// size_type	i;

			// distance = std::distance(this->begin(), position);
			// if (this->size() == this->capacity())
			// 	this->reserve((distance + __EPSILON_SIZE__) * __VECTOR_GROWTH_SIZE__);
			// for (i = this->size(); i > distance + 1; i--)
			// 	std::swap(&this->_v[i], &this->_v[i - 1]);
			// this->_alloc.construct(&this->_alloc[i], val);
			// ++this->_size;
			// return (iterator(&this->_v[i]));
			return (this->_insert(position, 1, val));
		}
		
		/*
		** Insert elements
		** The vector is extended by inserting new elements before the element at the specified position,
		** effectively increasing the container size by the number of elements inserted.
		** This causes an automatic reallocation of the allocated storage
		** space if -and only if- the new vector size surpasses the current vector capacity.
		** Because vectors use an array as their underlying storage,
		** inserting elements in positions other than the vector end causes
		** the container to relocate all the elements that were after
		** position to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other
		** kinds of sequence containers (such as list or forward_list).
		** The parameters determine how many elements are inserted and to which values they are initialized:
		** @param position Position in the vector where the new elements are inserted.
		** @param n Number of elements to insert. Each element is initialized to a copy of val.
		** @param val Value to be copied (or moved) to the inserted elements.
		** @return void
		*/
		void insert (iterator position, size_type n, const value_type& val)
		{
			// size_type	distance;
			// size_type	i;
			// size_type	n_element;

			// n_element = n;
			// distance = std::distance(this->begin(), position);
			// if (this->size() + n >= this->capacity())
			// 	this->resize(((this->capacity() + __EPSILON_SIZE__) * __VECTOR_GROWTH_SIZE__) + n);
			// /*
			// ** Here I substract a 1 since we will start the process from 0
			// */
			// i = this->size() + n - 1;
			// for (; i > distance + n; i--)
			// 	std::swap(&this->_v[i], &this->_v[i - n]);
			// while (n--)
			// 	this->_alloc.construct(this->_v[i++], val);
			// this->_size += n_element;
			(void)(this->_insert(position, n, val));
		}
		
		/*
		** Insert elements
		** The vector is extended by inserting new elements before the element at the specified position,
		** effectively increasing the container size by the number of elements inserted.
		** This causes an automatic reallocation of the allocated storage
		** space if -and only if- the new vector size surpasses the current vector capacity.
		** Because vectors use an array as their underlying storage,
		** inserting elements in positions other than the vector end causes
		** the container to relocate all the elements that were after
		** position to their new positions. This is generally an inefficient operation
		** compared to the one performed for the same operation by other
		** kinds of sequence containers (such as list or forward_list).
		** The parameters determine how many elements are inserted and to which values they are initialized:
		** @param position Position in the vector where the new elements are inserted.
		** @param first Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
		** @param last Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
		** @return void
		*/
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			size_type	distance;
			size_type	i;
			size_type	n;

			n = std::distance(first, last);
			distance = std::distance(this->begin(), position);
			if (this->size() + n >= this->capacity())
				this->resize(((this->capacity() + __EPSILON_SIZE__) * __VECTOR_GROWTH_SIZE__) + n);
			/*
			** Here I substract a 1 since we will start the process from 0
			*/
			i = this->size() + n - 1;
			for (; i > distance + n; i--)
				std::swap(this->_v[i], this->_v[i - n]);
			while (first != last)
				this->_alloc.construct(&this->_v[i++], *(first++));
		}


		


		/* ======================== */
		/* ======= ALLOATOR ======= */
		/* ======================== */
		/*
		** Returns a copy of the allocator object associated with the vector.
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
		** @param x A vector object of the same type
		** @return *this
		*/
		vector& operator= (const vector& x)
		{
			if (this == &x)
				return ((*this));
			for (size_type i = 0; i < this->capacity(); i++)
				this->_alloc.destroy(&this->_v[i]);
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
				this->_alloc.deallocate(this->_v, this->capacity());
				this->_v = tmp;
				this->_capacity = n;
			}

			/*
			** Insert elements
			** The vector is extended by inserting new elements before the element at the specified position,
			** effectively increasing the container size by the number of elements inserted.
			** This causes an automatic reallocation of the allocated storage
			** space if -and only if- the new vector size surpasses the current vector capacity.
			** Because vectors use an array as their underlying storage,
			** inserting elements in positions other than the vector end causes
			** the container to relocate all the elements that were after
			** position to their new positions. This is generally an inefficient operation
			** compared to the one performed for the same operation by other
			** kinds of sequence containers (such as list or forward_list).
			** The parameters determine how many elements are inserted and to which values they are initialized:
			** @param position Position in the vector where the new elements are inserted.
			** @param n Number of elements to insert. Each element is initialized to a copy of val.
			** @param val Value to be copied (or moved) to the inserted elements.
			** @return void
			*/
			iterator _insert (iterator position, size_type n, const value_type& val)
			{
				size_type	distance;
				size_type	i;
				size_type	n_element;

				n_element = n;
				distance = std::distance(this->begin(), position);
				if (this->size() + n >= this->capacity())
					this->reserve(((this->capacity() + __EPSILON_SIZE__) * __VECTOR_GROWTH_SIZE__) + n);
				/*
				** Here I substract a 1 since we will start the process from 0
				*/
				i = this->size() + n - 1;
				for (; i >= distance + n; i--)
					std::swap(this->_v[i], this->_v[i - n]);
				while (n--)
					this->_alloc.construct(&this->_v[i--], val);
				this->_size += n_element;
				return (iterator(this->_v[i - n_element]));
			}

			

};

};