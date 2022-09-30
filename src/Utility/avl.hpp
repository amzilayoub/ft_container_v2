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

		/* ============================== MEMBER CLASS ============================== */
		public:
			struct node
			{
				/* =============== MEMBER ATTRIBUTES =============== */
				node													*parent;
				node													*left;
				node													*right;

				value_type												*value;
				size_type												height;

				/*
				** Initialize the object
				** @param void void
				** @return void
				*/
				void init(void)
				{
					this->left = NULL;
					this->right = NULL;
					this->parent = NULL;
					this->height = 0;
					this->value = NULL;
				}

				/*
				** Get the key of the current return
				** @param void void
				** @return return the key of the current node
				*/
				key_type get_key() const
				{
					return (this->value->first);
				}

				/*
				** Get the value of the current return
				** @param void void
				** @return return a reference to the value of the current node
				*/
				mapped_type &getvalue()
				{
					return (this->value->second);
				}

			};
		/* ============================== CONSTRUCTOR/DESTRUCTOR ============================== */
		public:
			/*
			** default constructor
			** @param void
			** @return void
			*/
			AVL(void)
			{
				this->root = NULL;
			}

			/*
			** Construct a node from a key value
			** @param key key inserted
			** @param value the value associated
			** @Return void
			*/
			AVL(key_type key, mapped_type value)
			{
				this->root = this->_alloc_node.allocate(1);
				this->root->init();
				this->_alloc.construct(this->root->value, ft::make_pair(key, value));
			}

			~AVL()
			{
				// this->_alloc.destroy(this->_root);
				// this->_alloc.deallocate(this->value, 1);
			}

		/* ============================== MEMBER FUNCTION ============================== */
		public:
			/*
			** Create a new node
			** @param value the value that will inside the node
			** @return the AVL object after being created
			*/
			node *create_node(value_type const value)
			{
				node *root;

				root = this->_alloc_node.allocate(1);
				root->init();
				root->value = this->_alloc.allocate(1);
				this->_alloc.construct(root->value, value);
				return (root);
			}

			/*
			** Left rotation (LLF) function
			** @param root pointer to the root to be rotated
			** @return return the new root after being left rotated
			*/
			node *left_rotation(node *root)
			{
				node *new_root;

				new_root = root->right;
				/*
				** In the next line, were pointing to the right left node in order to not lose access to it,
				** since we're going to overide the left node in the next expression (new_root->left = root)
				*/
				root->right = root->right->left;
				new_root->left = root;

				if (root->right != NULL)
					root->right->parent = root;
				
				new_root->parent = root->parent;
				root->parent = new_root;


				this->update_height(root->right);
				this->update_height(root->left);
				this->update_height(root);
				this->update_height(root->parent);

				return (new_root);
			}

			/*
			** Insert the value in the tree
			** @param tree a tree pointing to the root object
			** @param value value to be inserted in the tree
			** @return the new root after inserting the new value
			*/
			node *insert(node *tree, value_type const value)
			{
				if (!tree)
					return (this->create_node(value));
				if (tree->value->first == value.first)
					tree->value->second = value.second;
				else if (this->_compare(tree->value->first, value.first))
					tree->right = this->insert(tree->right, value);
				else
					tree->left = this->insert(tree->left, value);
				return (tree);
			}

			/*
			** This function update the height of the node
			** @param void void
			** @return void
			*/
			void update_height(node *root)
			{
				size_type height;

				if (!root || root->height == 0)
					return ;

				height = 0;
				if (root->left)
					height = root->left->height;
				else if (root->right)
					height = std::max(root->right->height, height);
				
				root->height = height + 1;
			}

			/*
			** Print the tree
			** @param tree tree to print
			** @return void
			*/
			void print(node *tree)
			{
				if (!tree)
					return ;
				std::cout << "LEFT = ";
				if (tree->left && tree->left->value)
					std::cout << '(' << tree->left->value->first << ',' << tree->left->value->second << ')';
				else
					std::cout << "(NULL)";
				std::cout << "\t|\t";
				std::cout << '(' << tree->value->first << ',' << tree->value->second << ')';
				std::cout << "\t|\t";
				std::cout << "RIGHT = ";
				if (tree->right && tree->right->value)
					std::cout << '(' << tree->right->value->first << ',' << tree->right->value->second << ')';
				else
					std::cout << "(NULL)";
				std::cout << std::endl;
				print(tree->left);
				print(tree->right);
			}

		/* ============================== MEMBER ATTRIBUTES ============================== */
		public:
			node													*root;
		
		private:
			allocator_type											_alloc;
			typename allocator_type::template rebind<node>::other	_alloc_node;
			Compare													_compare;
	};

};