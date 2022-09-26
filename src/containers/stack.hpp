/*
** LIFO Stack
** Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container.
**
** Stacks are implemented as container adaptors,
** which are classes that use an encapsulated object of a specific container class as its underlying container,
** providing a specific set of member functions to access its elements. Elements are pushed/popped from the "back"
** of the specific container, which is known as the top of the Stack.
**
** The underlying container may be any of the standard container class
** templates or some other specifically designed container class.
** The container shall support the following operations:
**      - empty
**      - size
**      - back
**      - push_back
**      - pop_back
**
** The standard container classes vector, deque and list fulfill these requirements.
** By default, if no container class is specified for a particular Stack class instantiation, the standard container deque is used.
*/

#pragma once

#include "./vector.hpp"

namespace ft
{

template <class T, class Container = ft::Vector<T> >
class Stack
{
    /* ============================== MEMBER TYPE ============================== */
    private:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

    /* ============================== MEMBER TYPES ============================== */
    protected:
        container_type _c;

    /* ============================== CONSTRUCTORS/DESTRUCTORS ============================== */
        /*
        ** A container adaptor keeps internally a container object as data. This container
        ** object is a copy of the ctnr argument passed to the constructor, if any, otherwise it is an empty container.
        ** @param ctnr Container object.
        ** @return void
        */
    public:
        explicit Stack(const container_type &ctnr = container_type()) : _c(ctnr)
        {
        }

        ~Stack(void)
        {
        }

        /* ============================== MEMBER FUNCTIONS ============================== */
    public:
        /*
        ** Test whether container is empty
        ** Returns whether the Stack is empty: i.e. whether its size is zero.
        ** This member function effectively calls member empty of the underlying container object.
        ** @param void void
        ** @return true if the underlying container's size is 0, false otherwise.
        */
        bool empty() const
        {
            return (this->_c.empty());
        }

        /*
        ** Return size
        ** Returns the number of elements in the Stack.
        ** This member function effectively calls member size of the underlying container object.
        ** @param void void
        ** @return The number of elements in the underlying container.
        */
        size_type size() const
        {
            return (this->_c.size());
        }

        /*
        ** Access next element
        ** Returns a reference to the top element in the Stack.
        ** Since Stacks are last-in first-out containers, the top element is the last element inserted into the Stack.
        ** This member function effectively calls member back of the underlying container object.
        ** @param none
        ** @return A reference to the top element in the Stack.
        */
        value_type& top()
        {
            return (this->_c.at(this->_c.size() - 1));
        }
        
        /*
        ** Access next element
        ** Returns a reference to the top element in the Stack.
        ** Since Stacks are last-in first-out containers, the top element is the last element inserted into the Stack.
        ** This member function effectively calls member back of the underlying container object.
        ** @param none
        ** @return A reference to the top element in the Stack.
        */
        const value_type& top() const
        {
            return (this->_c.at(this->_c.size() - 1));
        }

        /*
        ** Insert element
        ** Inserts a new element at the top of the Stack, above its current top element. The content of this new element is initialized to a copy of val.
        ** This member function effectively calls the member function push_back of the underlying container object.
        ** @param val Value to which the inserted element is initialized.
        ** @return void
        */
        void push (const value_type& val)
        {
            this->_c.push_back(val);
        }

        /*
        ** Remove top element
        ** Removes the element on top of the Stack, effectively reducing its size by one.
        ** The element removed is the latest element inserted into the Stack, whose value can be retrieved by calling member Stack::top.
        ** This calls the removed element's destructor.
        ** This member function effectively calls the member function pop_back of the underlying container object.
        ** @param void void
        ** @return void
        */
        void pop()
        {
            this->_c.pop_back();
        }

        friend bool operator== (const Stack &lhs, const Stack &rhs)
        {
            return (lhs._c == rhs._c);
        }

        friend bool operator!= (const Stack &lhs, const Stack &rhs)
        {
            return (lhs._c != rhs._c);
        }

        friend bool operator<  (const Stack &lhs, const Stack &rhs)
        {
            return (lhs._c < rhs._c);
        }

        friend bool operator<= (const Stack &lhs, const Stack &rhs)
        {
            return (lhs._c <= rhs._c);
        }

        friend bool operator>  (const Stack &lhs, const Stack &rhs)
        {
            return (lhs._c > rhs._c);
        }

        friend bool operator>= (const Stack &lhs, const Stack &rhs)
        {
            return (lhs._c >= rhs._c);
        }
};

};