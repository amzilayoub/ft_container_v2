/*
** AVL tree is a self-balancing Binary Search Tree (BST)
** where the difference between heights of left and right subtrees cannot be more than one for all nodes.
*/

# pragma once

# include "./utility.hpp"
# include <algorithm>
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
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef typename ft::pair<const key_type, mapped_type>	value_type;
			typedef size_t											size_type;
			typedef Alloc											allocator_type;

		/* ============================== CONSTRUCTOR/DESTRUCTOR ============================== */
		public:
			/*
			** default constructor
			** @param void
			** @return void
			*/
			AVL(void)
			{
				this->_init();
			}

			/*
			** Construct a node from a key value
			** @param key key inserted
			** @param value the value associated
			** @Return void
			*/
			AVL(key_type key, mapped_type value)
			{
				this->_init();
				this->_alloc.construct(this->value, ft::make_pair(key, value));
			}

			~AVL()
			{
				this->_alloc.destroy(this->_value);
				this->_alloc.deallocate(this->_value, 1);
			}

		/* ============================== MEMBER FUNCTION ============================== */
		public:
			/*
			** Get the key of the current return
			** @param void void
			** @return return the key of the current node
			*/
			key_type get_key() const
			{
				return (this->_value->first);
			}

			/*
			** Get the value of the current return
			** @param void void
			** @return return a reference to the value of the current node
			*/
			mapped_type &get_value()
			{
				return (this->_value->second);
			}

			/*
			** This function update the height of the node
			** @param void void
			** @return void
			*/
			void update_height(AVL *tree)
			{
				size_type height;

				if (!tree || tree->_height == 0)
					return ;

				height = 0;
				if (tree->_left)
					height = tree->_left->_height;
				else if (tree->_right)
					height = std::max(tree->_right->_height, height);
				
				tree->_height = height + 1;
			}

			/*
			** Left rotation (LLF) function
			** @param root pointer to the root to be rotated
			** @return return the new root after being left rotated
			*/
			struct AVL *left_rotation(struct AVL *root)
			{
				struct AVL *new_root;

				new_root = root->_right;
				/*
				** In the next line, were pointing to the right left node in order to not lose access to it,
				** since we're going to overide the left node in the next expression (new_root->left = root)
				*/
				root->_right = root->_right->_left;
				new_root->_left = root;

				if (root->_right != NULL)
					root->_right->_parent = root;
				
				new_root->_parent = root->_parent;
				root->_parent = new_root;

				this->update_height(root->_right);
				this->update_height(root->_left);
				this->update_height(root);
				this->update_height(root->_parent);

				return (new_root);
			}

			/*
			** Insert the value in the tree
			** @param tree a tree pointing to the root object
			** @param value value to be inserted in the tree
			** @return the new root after inserting the new value
			*/
			AVL *insert(AVL *tree, value_type const value)
			{
				if (!tree)
					return (this->create(value));
				if (tree->_value->first == value.first)
					tree->_value->second = value.second;
				else if (this->_compare(tree->_value->first, value.first))
					tree->_right = this->insert(tree->_right, value);
				else
					tree->_left = this->insert(tree->_left, value);
				return (tree);
			}

			/*
			** Create a new node
			** @param value the value that will inside the node
			** @return the AVL object after being created
			*/
			AVL *create(value_type const value)
			{
				AVL *root;

				root = this->_alloc_avl.allocate(1);
				root->_init();
				root->_value = this->_alloc.allocate(1);
				this->_alloc.construct(root->_value, value);
				return (root);
			}

			/*
			** Print the tree
			** @param tree tree to print
			** @return void
			*/
			void print(AVL *tree)
			{
				if (!tree)
					return ;
				std::cout << "LEFT = ";
				if (tree->_left && tree->_left->_value)
					std::cout << '(' << tree->_left->_value->first << ',' << tree->_left->_value->second << ')';
				else
					std::cout << "(NULL)";
				std::cout << "\t|\t";
				std::cout << '(' << tree->_value->first << ',' << tree->_value->second << ')';
				std::cout << "\t|\t";
				std::cout << "RIGHT = ";
				if (tree->_right && tree->_right->_value)
					std::cout << '(' << tree->_right->_value->first << ',' << tree->_right->_value->second << ')';
				else
					std::cout << "(NULL)";
				std::cout << std::endl;
				print(tree->_left);
				print(tree->_right);
			}

		private:
			/*
			** Initialize the object
			** @param void void
			** @return void
			*/
			void _init(void)
			{
				this->_left = NULL;
				this->_right = NULL;
				this->_parent = NULL;
				this->_height = 0;
			}

		/* ============================== MEMBER ATTRIBUTES ============================== */
		public:
			AVL														*_parent;
			AVL														*_left;
			AVL														*_right;

			value_type												*_value;
			size_type												_height;
			allocator_type											_alloc;
			Compare													_compare;
			typename allocator_type::template rebind<AVL>::other	_alloc_avl;
	};

};