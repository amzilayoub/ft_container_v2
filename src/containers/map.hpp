/*
** Map
** Maps are associative containers that store elements formed by a combination of a key value and a Mapped value, following a specific order.
** 
** In a Map, the key values are generally used to sort and uniquely identify the elements,
** while the Mapped values store the content associated to this key.
** The types of key and Mapped value may differ, and are grouped together in member type value_type,
** which is a pair type combining both:
**  
** typedef pair<const Key, T> value_type;
** 
** Internally, the elements in a Map are always sorted by its key following a specific strict weak
** ordering criterion indicated by its internal comparison object (of type Compare).
** Map containers are generally slower than unordered_Map containers to access individual
** elements by their key, but they allow the direct iteration on subsets based on their order.
** The Mapped values in a Map can be accessed directly by their corresponding key using the bracket operator ((operator[]).
** Maps are typically implemented as binary search trees.
*/

# pragma once

# include "../Utility/avl.hpp"
# include "../Utility/Iterators/iterator_traits.hpp"
# include "../Utility/Iterators/bidirectional_iterator.hpp"
# include "../Utility/Iterators/reverse_iterator.hpp"
# include "./vector.hpp"
# include <functional>

namespace ft
{

template < class Key,											// Map::key_type
           class T,												// Map::Mapped_type
           class Compare = std::less<Key>,						// Map::key_compare
           class Alloc = std::allocator<pair<const Key,T> >		// Map::allocator_type
           >
class Map
{
	/* ============================== MEMBER TYPE ============================== */
	private:
		typedef typename	ft::AVL<Key, T, Compare, Alloc>::node				node;
		typedef typename	ft::AVL<Key, const T, Compare, Alloc>::node			const_node;

	public:
		typedef				Key													key_type;
		typedef				T													Mapped_type;
		typedef				ft::pair<const key_type, Mapped_type>				value_type;
		typedef				Compare												key_compare;
		typedef				Alloc												allocator_type;
		typedef typename	allocator_type::reference							reference;
		typedef typename	allocator_type::const_reference						const_reference;
		typedef typename	allocator_type::pointer								pointer;
		typedef typename	allocator_type::const_pointer						const_pointer;
		typedef typename	ft::bidirectional_iterator<node, value_type>		iterator;
		typedef typename	ft::bidirectional_iterator<node, const value_type>	const_iterator;
		typedef typename	ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef typename	ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef				size_t												size_type;
	
	/* ============================== MEMBER CLASS ============================== */
	public:
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class Map;
			/* ========= MEMBER CLASS ========= */
			protected:
				Compare comp;

				/* ========= CONSTRUCTOR ========= */
				value_compare(Compare c) : comp(c) {}

			/* ========= MEMBER FUNCTION ========= */
			public:
				bool operator()(const value_type& x, const value_type& y) const
				{
					return (this->comp(x.first, y.first));
				}
		};

	/* ============================== MEMBER ATTRIBUTES ============================== */
	private:
		ft::AVL<Key, T, Compare, Alloc>	_tree;
		key_compare						_key_comp;
		allocator_type					_alloc;
		size_type						_size;


	/* ============================== CONSTRUCTORS ============================== */
	public:
		/*
		** Constructs a Map container object, initializing its contents depending on the constructor version used
		** @param comp Binary predicate that, taking two element keys as argument, returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
		** @param alloc Allocator object.
		*/
		explicit Map (
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
				) : _key_comp(comp), _alloc(alloc), _size(0)
		{
		}

		/*
		** Constructs a Map container object, initializing its contents depending on the constructor version used
		** @param first Input iterators to the initial positions in a range.
		** @param last Input iterators to the final positions in a range.
		** @param comp Binary predicate that, taking two element keys as argument, returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
		** @param alloc Allocator object.
		*/
		template <class InputIterator>
		Map (
			InputIterator first,
			InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _key_comp(comp), _alloc(alloc), _size(0)
		{
			this->insert(first, last);
		}

		/*
		** Constructs a Map container object, initializing its contents depending on the constructor version used
		** @param x Another Map object of the same type
		*/
		Map (const Map& x)
		{
			(*this) = x;
		}

		/*
		** Destructor
		*/
		~Map (void)
		{
			this->_tree.clear(true);
		}
		
	/* ============================== MEMBER FUNCTIONS ============================== */
	public:
		/* =================== */
		/* ==== ITERATORS ==== */
		/* =================== */
		/*
		** Return iterator to beginning
		** Returns an iterator referring to the first element in the Map container.
		** Because Map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
		** If the container is empty, the returned iterator value shall not be dereferenced.
		** @param void void
		** @return An iterator to the first element in the container.
		*/
		iterator begin()
		{
			return (iterator(this->_tree.root->minimum_node()));
		}

		/*
		** Return iterator to beginning
		** Returns an iterator referring to the first element in the Map container.
		** Because Map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
		** If the container is empty, the returned iterator value shall not be dereferenced.
		** @param void void
		** @return An iterator to the first element in the container.
		*/
		const_iterator begin() const
		{
			return (const_iterator(this->_tree.root->minimum_node()));
		}

		/*
		** Return iterator to end
		** Returns an iterator referring to the past-the-end element in the Map container.
		** The past-the-end element is the theoretical element that would follow the last
		** element in the Map container. It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard library
		** do not include the element pointed by their closing iterator,
		** this function is often used in combination with Map::begin to specify a range including all the elements in the container.
		** If the container is empty, this function returns the same as Map::begin.
		** @param void void
		** @param An iterator to the past-the-end element in the container. 
		*/
		iterator end()
		{
			/*
			** in case the container is empty, we should return the begin, otherwise, we should return the end of the container
			*/
			if (this->_size)
				return (iterator(this->_tree.root_parent));
			return (iterator(this->_tree.root));
		}
		
		/*
		** Return iterator to end
		** Returns an iterator referring to the past-the-end element in the Map container.
		** The past-the-end element is the theoretical element that would follow the last
		** element in the Map container. It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard library
		** do not include the element pointed by their closing iterator,
		** this function is often used in combination with Map::begin to specify a range including all the elements in the container.
		** If the container is empty, this function returns the same as Map::begin.
		** @param void void
		** @param An iterator to the past-the-end element in the container. 
		*/
		const_iterator end() const
		{
			/*
			** in case the container is empty, we should return the begin, otherwise, we should return the end of the container
			*/
			if (this->_size)
				return (const_iterator(this->_tree.root_parent));
			return (const_iterator(this->_tree.root));
		}

		/*
		** Return reverse iterator to reverse beginning
		** Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		** Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		** rbegin points to the element preceding the one that would be pointed to by member end.
		** @param void void
		** @return A reverse iterator to the reverse beginning of the sequence container.
		*/
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}

		/*
		** Return reverse iterator to reverse beginning
		** Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		** Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		** rbegin points to the element preceding the one that would be pointed to by member end.
		** @param void void
		** @return A reverse iterator to the reverse beginning of the sequence container.
		*/
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		/*
		** Return reverse iterator to reverse end
		** Returns a reverse iterator pointing to the theoretical element right before
		** the first element in the Map container (which is considered its reverse end).
		** The range between Map::rbegin and Map::rend contains all the elements of the container (in reverse order).
		** @param void void
		** @return A reverse iterator to the reverse end of the sequence container.
		*/
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}

		/*
		** Return reverse iterator to reverse end
		** Returns a reverse iterator pointing to the theoretical element right before
		** the first element in the Map container (which is considered its reverse end).
		** The range between Map::rbegin and Map::rend contains all the elements of the container (in reverse order).
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
		** Test whether container is empty
		** Returns whether the Map container is empty (i.e. whether its size is 0).
		** This function does not modify the container in any way. To clear the content of a Map container, see Map::clear.
		** @param void void
		** @return true if the container size is 0, false otherwise.
		*/
		bool empty() const
		{
			return (this->_size == 0);
		}

		/*
		** Return container size
		** Returns the number of elements in the Map container.
		** @param void void
		** @return The number of elements in the container.
		*/
		size_type size() const
		{
			return (this->_size);
		}

		/*
		** Return maximum size
		** Returns the maximum number of elements that the Map container can hold.
		** This is the maximum potential size the container can reach
		** due to known system or library implementation limitations,
		** but the container is by no means guaranteed to be able to reach that size:
		** it can still fail to allocate storage at any point before that size is reached.
		** @param void void
		** @return The maximum number of elements a Map container can hold as content.
		*/
		size_type max_size() const
		{
			return (this->_alloc.max_size());
		}

		/* ======================== */
		/* ==== ELEMENT ACCESS ==== */
		/* ======================== */
		/*
		** Access element
		** If k matches the key of an element in the container, the function returns a reference to its Mapped value.
		** If k does not match the key of any element in the container,
		** the function inserts a new element with that key and returns a reference to its Mapped value.
		** Notice that this always increases the container size by one, even if no Mapped
		** value is assigned to the element (the element is constructed using its default constructor).
		** A similar member function, Map::at, has the same behavior when an element with the key exists,
		** but throws an exception when it does not.
		** @param k Key value of the element whose Mapped value is accessed.
		** @return A reference to the Mapped value of the element with a key value equivalent to k.
		*/
		Mapped_type& operator[] (const key_type& k)
		{
			return ((*((this->insert(ft::make_pair(k, Mapped_type()))).first)).second);
		}

		/* =================== */
		/* ==== MODIFIERS ==== */
		/* =================== */
		/*
		** Insert elements
		** Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
		** Because element keys in a Map are unique, the insertion operation checks whether each inserted
		** element has a key equivalent to the one of an element already in the container,
		** and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
		** For a similar container allowing for duplicate elements, see multiMap.
		** An alternative way to insert elements in a Map is by using member function Map::operator[].
		** Internally, Map containers keep all their elements sorted by their key following the criterion
		** specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		** @param val Value to be copied to (or moved as) the inserted element.
		** @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the Map
		*/
		pair<iterator,bool> insert (const value_type& val)
		{
			node	*tmp;

			tmp = this->_tree.search(val.first);
			this->_tree.insert(val);
			if (tmp)
				return (pair<iterator, bool>(tmp, false));
			++this->_size;
			return (pair<iterator, bool>(this->_tree.search(val.first), true));
		}

		/*
		** Insert elements
		** Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
		** Because element keys in a Map are unique, the insertion operation checks whether each inserted
		** element has a key equivalent to the one of an element already in the container,
		** and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
		** For a similar container allowing for duplicate elements, see multiMap.
		** An alternative way to insert elements in a Map is by using member function Map::operator[].
		** Internally, Map containers keep all their elements sorted by their key following the criterion
		** specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		** @param position Hint for the position where the element can be inserted.
		** @param val Value to be copied to (or moved as) the inserted element.
		** @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the Map
		*/
		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			return (this->insert(val).first);
		}

		/*
		** Insert elements
		** Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
		** Because element keys in a Map are unique, the insertion operation checks whether each inserted
		** element has a key equivalent to the one of an element already in the container,
		** and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
		** For a similar container allowing for duplicate elements, see multiMap.
		** An alternative way to insert elements in a Map is by using member function Map::operator[].
		** Internally, Map containers keep all their elements sorted by their key following the criterion
		** specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		** @param first Input iterators to the initial positions in a range.
		** @param last Input iterators to the final positions in a range.
		** @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the Map
		*/
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
				this->insert(*(first++));
		}

		/*
		** Erase elements
		** Removes from the Map container either a single element or a range of elements ([first,last)).
		** This effectively reduces the container size by the number of elements removed, which are destroyed.
		** @param position Iterator pointing to a single element to be removed from the Map.
		** @return void
		*/
		void erase (iterator position)
		{
			if (this->_tree.search((*position).first))
			{
				this->_tree.delete_node((*position).first);
				--this->_size;
			}
		}

		/*
		** Erase elements
		** Removes from the Map container either a single element or a range of elements ([first,last)).
		** This effectively reduces the container size by the number of elements removed, which are destroyed.
		** @param k Key of the element to be removed from the Map.
		** @return the function returns the number of elements erased.
		*/
		size_type erase (const key_type& k)
		{
			if (this->_tree.search(k))
			{
				this->_tree.delete_node(k);
				--this->_size;
				return (1);
			}
			return (0);
		}

		/*
		** Erase elements
		** Removes from the Map container either a single element or a range of elements ([first,last)).
		** This effectively reduces the container size by the number of elements removed, which are destroyed.
		** @param first Iterators specifying a range within the Map container to be removed
		** @param last Iterators specifying a range within the Map container to be removed
		** @return void
		*/
    	void erase (iterator first, iterator last)
		{
			ft::Vector<key_type> tmp;
			typename ft::Vector<key_type>::iterator it;

			while (first != last)
				tmp.push_back((first++)->first);
			for (it = tmp.begin(); it != tmp.end(); it++)
				this->erase(*it);
		}

		/*
		** Swap content
		** Exchanges the content of the container by the content of x, which is another Map of the same type. Sizes may differ.
		** After the call to this member function, the elements in this container are those which
		** were in x before the call, and the elements of x are those which were in this.
		** All iterators, references and pointers remain valid for the swapped objects.
		** Notice that a non-member function exists with the same name, swap,
		** overloading that algorithm with an optimization that behaves like this member function.
		** @param x Another Map container of the same type as this
		*/
		void swap (Map& x)
		{
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_key_comp, x._key_comp);
			std::swap(this->_size, x._size);
			this->_tree.swap(x._tree);
		}

		/*
		** Removes all elements from the Map container (which are destroyed), leaving the container with a size of 0.
		** @param void void
		** @return void
		*/
		void clear()
		{
			this->erase(this->begin(), this->end());
		}

		/* =================== */
		/* ==== OBSERVERS ==== */
		/* =================== */
		/*
		** Return key comparison object
		** Returns a copy of the comparison object used by the container to compare keys.
		** The comparison object of a Map object is set on construction. Its type
		** (member key_compare) is the third template parameter of the Map template. By default,
		** this is a less object, which returns the same as operator<.
		** This object determines the order of the elements in the container:
		** it is a function pointer or a function object that takes two arguments of the same
		** type as the element keys, and returns true if the first argument is considered to go before
		** the second in the strict weak ordering it defines, and false otherwise.
		** Two keys are considered equivalent if key_comp returns false reflexively
		** (i.e., no matter the order in which the keys are passed as arguments).
		** @param void void
		** @return The comparison object.
		*/
		key_compare key_comp() const
		{
			return (this->_key_comp);
		}

		/*
		** Return value comparison object
		** Returns a comparison object that can be used to compare two
		** elements to get whether the key of the first one goes before the second.
		** The arguments taken by this function object are of member type value_type
		** (defined in Map as an alias of pair<const key_type,Mapped_type>),
		** but the Mapped_type part of the value is not taken into consideration in this comparison.
		** @param void void
		** @return The comparison object for element values.
		*/
		value_compare value_comp() const
		{
			return (value_compare(this->_key_comp));
		}

		/* ==================== */
		/* ==== OPERATIONS ==== */
		/* ==================== */
		/*
		** Get iterator to element
		** Searches the container for an element with a key equivalent to k and returns an iterator
		** to it if found, otherwise it returns an iterator to Map::end.
		** Two keys are considered equivalent if the container's comparison
		** object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
		** Another member function, Map::count, can be used to just check whether a particular key exists.
		** @param k Key to be searched for.
		** @return An iterator to the element, if an element with specified key is found, or Map::end otherwise.
		*/
		iterator find (const key_type& k)
		{
			node *target;

			target = this->_tree.search(k);
			return (target ? iterator(target) : this->end());
		}
		
		/*
		** Get iterator to element
		** Searches the container for an element with a key equivalent to k and returns an iterator
		** to it if found, otherwise it returns an iterator to Map::end.
		** Two keys are considered equivalent if the container's comparison
		** object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
		** Another member function, Map::count, can be used to just check whether a particular key exists.
		** @param k Key to be searched for.
		** @return An iterator to the element, if an element with specified key is found, or Map::end otherwise.
		*/
		const_iterator find (const key_type& k) const
		{
			node *target;

			target = this->_tree.search(k);
			return (target ? const_iterator(target) : this->end());
		}

		/*
		** Count elements with a specific key
		** Searches the container for elements with a key equivalent to k and returns the number of matches.
		** Because all elements in a Map container are unique,
		** the function can only return 1 (if the element is found) or zero (otherwise).
		** Two keys are considered equivalent if the container's comparison
		** object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
		** @param k Key to search for.
		** @return 1 if the container contains an element whose key is equivalent to k, or zero otherwise.
		*/
		size_type count (const key_type& k) const
		{
			return (this->_tree.search(k) != NULL);
		}

		/*
		** Return iterator to lower bound
		** Returns an iterator pointing to the first element in the container whose
		** key is not considered to go before k (i.e., either it is equivalent or goes after).
		** The function uses its internal comparison object (key_comp) to determine this,
		** returning an iterator to the first element for which key_comp(element_key,k) would return false.
		** If the Map class is instantiated with the default comparison type (less),
		** the function returns an iterator to the first element whose key is not less than k.
		** A similar member function, upper_bound, has the same behavior as lower_bound,
		** except in the case that the Map contains an element with a key equivalent to k:
		** In this case, lower_bound returns an iterator pointing to that element,
		** whereas upper_bound returns an iterator pointing to the next element.
		** @param k Key to search for.
		** @return An iterator to the the first element in the container whose key is not considered to go before k
		*/
		iterator lower_bound (const key_type& k)
		{
			node *tmp;

			tmp = this->_tree.lower_bound(k);
			return (tmp ? iterator(tmp) : this->end());
		}

		/*
		** Return iterator to lower bound
		** Returns an iterator pointing to the first element in the container whose
		** key is not considered to go before k (i.e., either it is equivalent or goes after).
		** The function uses its internal comparison object (key_comp) to determine this,
		** returning an iterator to the first element for which key_comp(element_key,k) would return false.
		** If the Map class is instantiated with the default comparison type (less),
		** the function returns an iterator to the first element whose key is not less than k.
		** A similar member function, upper_bound, has the same behavior as lower_bound,
		** except in the case that the Map contains an element with a key equivalent to k:
		** In this case, lower_bound returns an iterator pointing to that element,
		** whereas upper_bound returns an iterator pointing to the next element.
		** @param k Key to search for.
		** @return An iterator to the the first element in the container whose key is not considered to go before k
		*/
		const_iterator lower_bound (const key_type& k) const
		{
			node *tmp;

			tmp = this->_tree.lower_bound(k);
			return (tmp ? const_iterator(tmp) : this->end());
		}

		/*
		** Return iterator to upper bound
		** Returns an iterator pointing to the first element in the container whose key is considered to go after k.
		** The function uses its internal comparison object (key_comp) to determine this,
		** returning an iterator to the first element for which key_comp(k,element_key) would return true.
		** If the Map class is instantiated with the default comparison type (less),
		** the function returns an iterator to the first element whose key is greater than k.
		** A similar member function, lower_bound, has the same behavior as upper_bound,
		** except in the case that the Map contains an element with a key equivalent
		** to k: In this case lower_bound returns an iterator pointing to that element,
		** whereas upper_bound returns an iterator pointing to the next element.
		** @paragm k Key to search for.
		** @return An iterator to the the first element in the container whose key is considered to go after k, or Map::end if no keys are considered to go after k.
		*/
		iterator upper_bound (const key_type& k)
		{
			node *tmp;

			tmp = this->_tree.upper_bound(k);
			return (tmp ? iterator(tmp) : this->end());
		}
		
		/*
		** Return iterator to upper bound
		** Returns an iterator pointing to the first element in the container whose key is considered to go after k.
		** The function uses its internal comparison object (key_comp) to determine this,
		** returning an iterator to the first element for which key_comp(k,element_key) would return true.
		** If the Map class is instantiated with the default comparison type (less),
		** the function returns an iterator to the first element whose key is greater than k.
		** A similar member function, lower_bound, has the same behavior as upper_bound,
		** except in the case that the Map contains an element with a key equivalent
		** to k: In this case lower_bound returns an iterator pointing to that element,
		** whereas upper_bound returns an iterator pointing to the next element.
		** @paragm k Key to search for.
		** @return An iterator to the the first element in the container whose key is considered to go after k, or Map::end if no keys are considered to go after k.
		*/
		const_iterator upper_bound (const key_type& k) const
		{
			node *tmp;

			tmp = this->_tree.upper_bound(k);
			return (tmp ? const_iterator(tmp) : this->end());
		}

		/*
		** Get range of equal elements
		** Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
		** Because the elements in a Map container have unique keys,
		** the range returned will contain a single element at most.
		** If no matches are found, the range returned has a length of zero,
		** with both iterators pointing to the first element that has a key
		** considered to go after k according to the container's internal comparison object (key_comp).
		** Two keys are considered equivalent if the container's comparison object
		** returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
		** @param k Key to search for.
		** @return The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
		*/
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}
		
		/*
		** Get range of equal elements
		** Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
		** Because the elements in a Map container have unique keys,
		** the range returned will contain a single element at most.
		** If no matches are found, the range returned has a length of zero,
		** with both iterators pointing to the first element that has a key
		** considered to go after k according to the container's internal comparison object (key_comp).
		** Two keys are considered equivalent if the container's comparison object
		** returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
		** @param k Key to search for.
		** @return The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
		*/
		pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}
		/* =================== */
		/* ==== ALLOCATOR ==== */
		/* =================== */
		/*
		** Returns a copy of the allocator object associated with the Map.
		** @param void void
		** @return The allocator.
		*/
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}

	/* ============================== MEMBER FUNCTIONS ============================== */
	public:
		Map& operator= (const Map& x)
		{
			this->_alloc = x._alloc;
			this->_key_comp = x._key_comp;
			this->_tree = x._tree;
			this->_size = x._size;

			return (*this);
		}
	
	/* ============================== COMPARAISON FUNCTIONS ============================== */
	public:
	    friend bool operator==(const Map &lhs, const Map &rhs)
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
        friend bool operator!=(const Map& lhs, const Map& rhs)
		{
			return !(lhs == rhs);
		}

        friend bool operator<(const Map& lhs,const Map& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

        friend bool operator<=(const Map& lhs,const Map& rhs)
		{
			return !(rhs < lhs);
		}

        friend bool operator>(const Map& lhs, const Map& rhs )
		{
			return (rhs < lhs);
		}

        friend bool operator>=(const Map& lhs,const Map& rhs )
		{
			return !(rhs > lhs);
		}
};

template <class Key, class T, class Compare, class Alloc>
void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y)
{
	x.swap(y);
}
};