/*
** AVL tree is a self-balancing Binary Search Tree (BST)
** where the difference between heights of left and right subtrees cannot be more than one for all nodes.
*/

# pragma once

# include "./utility.hpp"
# include <algorithm>
# include <functional>
# include <iostream>

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
				/* =============== MEMBER TYPE =============== */
				/*
				** redefining these members as we will need them in the biderectional iterator
				*/
				typedef value_type										value_type;
				typedef key_type										key_type;
				typedef mapped_type										mapped_type;
				
				/* =============== MEMBER ATTRIBUTES =============== */
				node													*parent;
				node													*left;
				node													*right;

				value_type												*value;
				size_type												height;

				/* =============== MEMBER FUNCTIONS =============== */
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
				mapped_type &get_value()
				{
					return (this->value->second);
				}

				/*
				** Left rotation (LR) function
				** @param void void
				** @return return the new root after being left rotated
				*/
				node *left_rotation()
				{
					node *new_root;

					new_root = this->right;
					/*
					** In the next line, were pointing to the right left node in order to not lose access to it,
					** since we're going to overide the left node in the next expression (new_root->left = root)
					*/
					this->right = new_root->left;
					new_root->left = this;

					if (this->right != NULL)
						this->right->parent = this;
					
					new_root->parent = this->parent;
					this->parent = new_root;


					this->right->update_height();
					this->left->update_height();
					this->update_height();
					new_root->update_height();

					return (new_root);
				}

				/*
				** Right rotation (RR) function
				** @param void void
				** @return return the new root after being right rotated
				*/
				node *right_rotation()
				{
					node *new_root;

					new_root = this->left;
					this->left = new_root->right;
					new_root->right = this;

					if (this->left)
						this->left->parent = this;
					
					new_root->parent = this->parent;
					this->parent = new_root;

					this->right->update_height();
					this->left->update_height();
					this->update_height();
					new_root->update_height();

					return (new_root);
				}

				/*
				** This function update the height of the node
				** @param root targeted subtree
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
				** This function update the height of the node
				** @param void void
				** @return void
				*/
				void update_height()
				{
					return (this->update_height(this));
				}

				/*
				** take a node and search in the left side to get the smallest key
				** @param root the targeted tree/sub tree
				** @return return the smallest node
				*/
				node *minimum_node(node *root)
				{
					if (root && root->left)
						return (root->left->minimum_node());
					return (root);
				}

				/*
				** take a node and search in the left side to get the smallest key
				** @param void void
				** @return return the smallest node
				*/
				node *minimum_node()
				{
					return (this->minimum_node(this));
				}
				
				/*
				** take a node and search in the right side to get the biggest key
				** @param root the targeted tree/sub tree
				** @return return the biggest node
				*/
				node *maximum_node(node *root)
				{
					if (root && root->right)
						return (root->right->maximum_node());
					return (root);
				}

				/*
				** take a node and search in the left side to get the smallest key
				** @param void void
				** @return return the smallest node
				*/
				node *maximum_node()
				{
					return (this->maximum_node(this));
				}

				value_type &operator*() const
				{
					return (*(this->value));
				}

				node	*operator++()
				{
					node *cur;

					cur = this;
					if (cur->right)
						return (cur->right->minimum_node());

					while (cur->parent && cur->parent->right == cur)
						cur = cur->parent;
					return (cur->parent);
				}

				node	*operator--()
				{
					node *cur;

					cur = this;
					if (cur->left)
						return (cur->left->maximum_node());

					while (cur->parent && cur->parent->left == cur)
						cur = cur->parent;
					return (cur->parent);
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
				/*
				** this is the last element in the tree, which should be retourned by the end() function in the ::map
				*/
				this->root_parent = this->_alloc_node.allocate(1);
				this->root_parent->init();
				this->root_parent->left = this->root;
				this->root = NULL;
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
			node *create_node(value_type const value, node *parent = NULL)
			{
				node *root;

				root = this->_alloc_node.allocate(1);
				root->init();
				root->value = this->_alloc.allocate(1);
				this->_alloc.construct(root->value, value);
				root->height = 1;
				root->parent = parent;
				return (root);
			}

			/*
			** Balance the tree
			** @param node the targeted node
			** return the node after being balanced
			*/
			node *balance_tree(node *root)
			{
				int balance;

				balance = this->get_balance(root);
				if (std::abs(balance) != 2)
					return (root);
				/*
				** Since the balance is negatif, that means the left height is bigget than the right height
				** Which means we are in the LEFT CASE, we need just to check if it's LEFT LEFT CASE or LEFT RIGHT CASE
				*/
				if (balance > 0)
				{
					/*
					** LEFT LEFT CASE, Since the left key of the root is bigger than the key,
					** then the new element will be inserted in the left as well
					*/
					if (this->get_balance(root->left) > 0)
						root = root->right_rotation();
					else
					{
						/*
						** LEFT RIGHT CASE, since the new element is going to be inserted in the right side
						*/
						root->left = root->left->left_rotation();
						root = root->right_rotation();
					}
				}
				else
				{
					/*
					** RIGHT RIGHT CASE, Read the comment for the LEFT LEFT CASE and reverse it to understand this block
					*/
					if (this->get_balance(root->right) < 0)
						root = root->left_rotation();
					/*
					** RIGHT LEFT CASE
					*/
					else
					{
						root->right = root->right->right_rotation();
						root = root->left_rotation();
					}						
				}
			return (root);
			}

			/*
			** Get the difference in height between left and right
			** @param root targeted node to get the balance
			** @return positive integer if left height is bigger than the right, otherwise, positive, or zero in case they are equal
			*/
			int	get_balance(node *root)
			{
				int balance;

				balance = (root->left) ? root->left->height : 0;
				balance -= (root->right) ? root->right->height : 0;

				return (balance);
			}

			/*
			** Insert the value in the tree
			** @param value value to be inserted in the tree
			** @return the new root after inserting the new value
			*/
			node *insert(value_type const value)
			{
				this->root = this->insert(this->root, this->root_parent, value);

				this->root_parent->left = this->root;
				return (this->root);
			}

			/*
			** Insert the value in the tree
			** @param root a tree pointing to the root object
			** @param parent parent of the root
			** @param value value to be inserted in the tree
			** @return the new root after inserting the new value
			*/
			node *insert(node *root, node *parent, value_type const value)
			{
				int balance;

				if (!root)
					root = this->create_node(value, parent);
				else if (root->get_key() == value.first)
					root->value->second = value.second;
				else if (this->_compare(root->value->first, value.first))
					root->right = this->insert(root->right, root, value);
				else
					root->left = this->insert(root->left, root, value);

				root = this->balance_tree(root);
				root->update_height();
				return (root);
			}

			/*
			** Delete a noce
			** @param key targeted key
			** @return returning the tree after deleting the targeted key
			*/
			node *delete_node(key_type key)
			{
				this->root = this->delete_node(this->root, key);

				return (this->root);
			}

			/*
			** Delete a noce
			** @param root targeted tree
			** @param key targeted key
			** @return returning the tree after deleting the targeted key
			*/
			node *delete_node(node *root, key_type key)
			{
				if (!root)
					return (root);
				
				/*
				** Targeted key has been found
				*/
				if (root->get_key() == key)
				{
					node *tmp;

					tmp = NULL;
					/*
					** At least there's a child, left or right
					*/
					if (root->left || root->right)
					{
						tmp = root->right->minimum_node();
						if (tmp == root->right)
							tmp->parent->right = NULL;
						else
							tmp->parent->left = NULL;
						tmp->parent = root->parent;
						tmp->left = root->left;
						tmp->right = root->right;
						/*
						** Normally, we should connect the parent to the new node (tmp),
						** but since we are calling the functions in recursive way, the parent left or right,
						** will be replaced manually by one the next if else block
						** which is root->right = this->delete_node(...) or root->left = ...
						*/
					}
					this->_alloc.destroy(root->value);
					this->_alloc.deallocate(root->value, 1);
					this->_alloc_node.deallocate(root, 1);

					root = tmp;
				}
				/*
				** Search on the right
				*/
				else if (this->_compare(root->get_key(), key))
					root->right = this->delete_node(root->right, key);
				/*
				** Search on the left
				*/
				else
					root->left = this->delete_node(root->left, key);

				/*
				** if the tree has only one node, which means no left or right,
				** then return it
				*/
				if (root == NULL)
					return (root);
				root->update_height();
				root = this->balance_tree(root);
				return (root);
			}

			/*
			** search for a specific key inside the tree
			** @param key the needle
			** @return return the node that contains that key, otherwise NULL
			*/
			node *search(key_type key)
			{
				return (this->search(this->root, key));
			}

			/*
			** search for a specific key inside the tree
			** @param root subtree to search at
			** @param key the needle
			** @return return the node that contains that key, otherwise NULL
			*/
			node *search(node *root, key_type key)
			{
				if (root == NULL)
					return (root);
				else if (root->get_key() == key)
					return (root);
				else if (this->_compare(root->get_key(), key))
					return (this->search(root->right, key));
				else
					return (this->search(root->left, key));
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

			/*
			** take a node and clear all the subtree
			** @param root the targeted tree/sub tree
			** @return void
			*/
			node *clear(node *root)
			{
				if (root->left)
					root->left->clear();
				if (root->right)
					root->right->clear();
				this->_alloc.destroy(root->value);
				this->_alloc.deallocate(root->value);
				this->_alloc_node.destroy(root);
				this->_alloc_node.deallocate(root);

				return (NULL);
			}

			/*
			** take a node and clear all the subtree
			** @param void void
			** @return void
			*/
			node* clear()
			{
				this->root = this->clear(this->root);
			}

			/*
			** take a node and insert all it's alement into the root of the current object
			** @param node the targeted node to be copied
			** @return void void
			*/
			void copy_tree(const node *rhs)
			{
				if (rhs->right)
					this->copy_tree(rhs->right);
				if (rhs->left)
					this->copy_tree(rhs->left);
				this->insert(rhs->value);
			}

			AVL& operator= (const AVL& rhs)
			{
				this->clear();
				this->_alloc = rhs._alloc;
				this->_alloc_node = rhs._alloc_node;
				this->_compare = rhs._compare;
				this->copy_tree(rhs.tree);

				return (*this);
			}

		/* ============================== MEMBER ATTRIBUTES ============================== */
		public:
			node													*root;
			node													*root_parent;
		
		private:
			allocator_type											_alloc;
			typename allocator_type::template rebind<node>::other	_alloc_node;
			Compare													_compare;
	};

	/* ============================== HELPER FUNCTIONS ============================== */


};