/*
** AVL tree is a self-balancing Binary Search Tree (BST)
** where the difference between heights of left and right subtrees cannot be more than one for all nodes.
*/

# pragma once

# include "./utility.hpp"
# include <functional>

namespace ft
{

	template <
		class Key,
        class T,
        class Compare = std::less<Key>,
        class Alloc = std::allocator<pair<const Key,T> >
        >
	class AVL
	{
		/* ============================== MEMBER TYPE ============================== */
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef typename ft::pair<const key_type, mapped_type> value_type;
		typedef size_t size_type;

		/* ============================== MEMBER CLASS ============================== */
	public:
		struct node
		{
			/* ======== MEMBER ATTRIBUTE ======== */
			struct AVL	*parent;
			struct AVL	*left;
			struct AVL	*right;

			value_type	value;
			size_type	height;

			/* ======== MEMBER FUNCTION ======== */
			/*
			** Get the key of the current return
			** @param void void
			** @return return the key of the current node
			*/
			key_type get_key()
			{
				return (value.first);
			}

			/*
			** Get the value of the current return
			** @param void void
			** @return return a reference to the value of the current node
			*/
			mapped_type &get_value()
			{
				return (value.first);
			}
		};

		void update_height(struct AVL *node)
		{
		}
	};

};