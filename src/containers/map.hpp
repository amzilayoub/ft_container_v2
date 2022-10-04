/*
** Map
** Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.
** 
** In a map, the key values are generally used to sort and uniquely identify the elements,
** while the mapped values store the content associated to this key.
** The types of key and mapped value may differ, and are grouped together in member type value_type,
** which is a pair type combining both:
**  
** typedef pair<const Key, T> value_type;
** 
** Internally, the elements in a map are always sorted by its key following a specific strict weak
** ordering criterion indicated by its internal comparison object (of type Compare).
** map containers are generally slower than unordered_map containers to access individual
** elements by their key, but they allow the direct iteration on subsets based on their order.
** The mapped values in a map can be accessed directly by their corresponding key using the bracket operator ((operator[]).
** Maps are typically implemented as binary search trees.
*/

# pragma once

# include "../Utility/avl.hpp"
# include "../Utility/Iterators/iterator_traits.hpp"
# include "../Utility/Iterators/bidirectional_iterator.hpp"
# include "../Utility/Iterators/reverse_iterator.hpp"
# include <functional>

namespace ft
{

template < class Key,											// map::key_type
           class T,												// map::mapped_type
           class Compare = std::less<Key>,						// map::key_compare
           class Alloc = std::allocator<pair<const Key,T> >		// map::allocator_type
           >
class map
{
	/* ============================== MEMBER TYPE ============================== */
	private:
		typedef typename	ft::AVL<Key, T, Compare, Alloc>::node				node;
		typedef typename	ft::AVL<Key, const T, Compare, Alloc>::node			const_node;

	public:
		typedef				Key													key_type;
		typedef				T													mapped_type;
		typedef				ft::pair<const key_type, mapped_type>				value_type;
		typedef				Compare												key_compare;
		typedef				Alloc												allocator_type;
		typedef typename	allocator_type::reference							reference;
		typedef typename	allocator_type::const_reference						const_reference;
		typedef typename	allocator_type::pointer								pointer;
		typedef typename	allocator_type::const_pointer						const_pointer;
		typedef typename	ft::bidirectional_iterator<node>					iterator;
		typedef typename	ft::bidirectional_iterator<const_node>				const_iterator;
		typedef typename	ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef typename	ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef				size_t												size_type;
	
	/* ============================== MEMBER ATTRIBUTES ============================== */
	private:
		ft::AVL<Key, T, Compare, Alloc>	_tree;
		key_compare						_comp;
		allocator_type					_alloc;
		size_type						_size;

	/* ============================== MEMBER CLASS ============================== */
	public:
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
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

	/* ============================== CONSTRUCTORS ============================== */
	public:
		/*
		** Constructs a map container object, initializing its contents depending on the constructor version used
		** @param comp Binary predicate that, taking two element keys as argument, returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
		** @param alloc Allocator object.
		*/
		explicit map (
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
				) : _comp(comp), _alloc(alloc), _size(0)
		{
		}

		/*
		** Constructs a map container object, initializing its contents depending on the constructor version used
		** @param first Input iterators to the initial positions in a range.
		** @param last Input iterators to the final positions in a range.
		** @param comp Binary predicate that, taking two element keys as argument, returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
		** @param alloc Allocator object.
		*/
		template <class InputIterator>
		map (
			InputIterator first,
			InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0)
		{
			this->insert(first, last);
		}

		/*
		** Constructs a map container object, initializing its contents depending on the constructor version used
		** @param x Another map object of the same type
		*/
		map (const map& x)
		{
			(*this) = x;
		}

	/* ============================== MEMBER FUNCTIONS ============================== */
	public:
		/* =================== */
		/* ==== MODIFIERS ==== */
		/* =================== */
		/*
		** Insert elements
		** Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
		** Because element keys in a map are unique, the insertion operation checks whether each inserted
		** element has a key equivalent to the one of an element already in the container,
		** and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
		** For a similar container allowing for duplicate elements, see multimap.
		** An alternative way to insert elements in a map is by using member function map::operator[].
		** Internally, map containers keep all their elements sorted by their key following the criterion
		** specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		** @param val Value to be copied to (or moved as) the inserted element.
		** @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map
		*/
		pair<iterator,bool> insert (const value_type& val)
		{
			return (this->_insert(val));
		}

		/*
		** Insert elements
		** Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
		** Because element keys in a map are unique, the insertion operation checks whether each inserted
		** element has a key equivalent to the one of an element already in the container,
		** and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
		** For a similar container allowing for duplicate elements, see multimap.
		** An alternative way to insert elements in a map is by using member function map::operator[].
		** Internally, map containers keep all their elements sorted by their key following the criterion
		** specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		** @param position Hint for the position where the element can be inserted.
		** @param val Value to be copied to (or moved as) the inserted element.
		** @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map
		*/
		iterator insert (iterator position, const value_type& val)
		{
			return (this->_insert(val, &position).first);
		}

		/*
		** Insert elements
		** Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
		** Because element keys in a map are unique, the insertion operation checks whether each inserted
		** element has a key equivalent to the one of an element already in the container,
		** and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
		** For a similar container allowing for duplicate elements, see multimap.
		** An alternative way to insert elements in a map is by using member function map::operator[].
		** Internally, map containers keep all their elements sorted by their key following the criterion
		** specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		** @param first Input iterators to the initial positions in a range.
		** @param last Input iterators to the final positions in a range.
		** @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map
		*/
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
				this->insert(*(first++));
		}
		
	/* ============================== MEMBER FUNCTIONS ============================== */
	public:
		/* =================== */
		/* ==== ITERATORS ==== */
		/* =================== */
		/*
		** Return iterator to beginning
		** Returns an iterator referring to the first element in the map container.
		** Because map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
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
		** Returns an iterator referring to the first element in the map container.
		** Because map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
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
		** Returns an iterator referring to the past-the-end element in the map container.
		** The past-the-end element is the theoretical element that would follow the last
		** element in the map container. It does not point to any element, and thus shall not be dereferenced.
		** Because the ranges used by functions of the standard library
		** do not include the element pointed by their closing iterator,
		** this function is often used in combination with map::begin to specify a range including all the elements in the container.
		** If the container is empty, this function returns the same as map::begin.
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
		const_iterator end() const
		{
			/*
			** in case the container is empty, we should return the begin, otherwise, we should return the end of the container
			*/
			if (this->_size)
				return (const_iterator(this->_tree.root_parent));
			return (const_iterator(this->_tree.root));
		}
		
	/* ============================== MEMBER FUNCTIONS ============================== */
	public:
		map& operator= (const map& x)
		{
			this->_alloc = x._alloc;
			this->_comp = x._comp;
			this->_tree = x._tree;
			this->_size = x._size;

			return (*this);
		}
	
	/* ============================== HELPER MEMBER FUNCTIONS ============================== */
	private:
		/*
		** insert a new element to the tree
		** @param val the value to be inserted
		** @param position a hint to which position the element should be inserted
		** @return a pair which ::first point to the element, and ::Second indicate wheter the key is already in the tree or it is a new key
		*/
		pair<iterator,bool> _insert(const value_type& val, iterator *position = NULL)
		{
			node	*tmp;

			tmp = this->_tree.search(val.first);
			if (position)
				this->_tree.insert(position->base(), position->base()->parent, val);
			else
				this->_tree.insert(val);
			if (tmp)
				return (pair<iterator, bool>(tmp, false));
			++this->_size;
			return (pair<iterator, bool>(this->_tree.search(val.first), true));
		}
};

};