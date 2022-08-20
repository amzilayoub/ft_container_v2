/*
** Random-access iterators:
** Random-access iterators are iterators that can be used to access
** elements at an arbitrary offset position relative to the element they point to,
** offering the same functionality as pointers.
** 
** Random-access iterators are the most complete
** iterators in terms of functionality.
** All pointer types are also valid random-access iterators.
*/

# pragma once

# include "./iterator_traits.hpp"
# include "./iterator.hpp"

namespace ft
{

template <typename T>
class random_access_iterator : public ft::iterator_traits<ft::iterator<std::random_access_iterator_tag, T> >
{
    /* ============================== MEMBER ATTRIBUTES ============================== */
    private:
        value_type *_iter;
    
    /* ============================== CONSTRUCTOR/DESTRUCTOR ============================== */
    public:
        random_access_iterator(pointer ptr = nullptr) : _iter(ptr)
        {
        }

        explicit random_access_iterator(value_type &ptr) : _iter(&ptr)
        {
        }

        random_access_iterator(random_access_iterator const &rhs)
        {
            (*this) = rhs;
        }

        random_access_iterator &operator=(random_access_iterator const &rhs)
        {
            this->_iter = rhs._iter;

            return (*this);
        }

        reference operator*(void) const
        {
            return ((*this->_iter));
        }

        pointer operator->(void) const
        {
            return (*this->operator*());
        }

        random_access_iterator &operator++(void)
        {
            ++this->_iter;

            return (*this);
        }

        random_access_iterator &operator++(void)
        {
            ++this->_iter;

            return (*this);
        }

        random_access_iterator &operator++(int)
        {
            random_access_iterator tmp(this);

            ++this->_iter;
            return (tmp);
        }

        random_access_iterator &operator--(void)
        {
            --this->_iter;

            return (*this);
        }

        random_access_iterator &operator--(int)
        {
            random_access_iterator tmp(this);

            --this->_iter;
            return (tmp);
        }

        random_access_iterator operator+(difference_type n) const
        {
            random_access_iterator tmp(this);

            tmp._iter += n;
            return (tmp);
        }

        random_access_iterator operator-(difference_type n) const
        {
            random_access_iterator tmp(this);

            tmp._iter -= n;
            return (tmp);
        }

        random_access_iterator operator+=(difference_type n)
        {
            this->_iter += n;

            return (*this);
        }
        
        random_access_iterator operator-=(difference_type n)
        {
            this->_iter -= n;

            return (*this);
        }
};

template <class Iterator>
random_access_iterator<Iterator> operator+ (
	typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator>& it)
{
	return (it + n);
}

template <class Iterator>
random_access_iterator<Iterator> operator- (
	typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator>& it)
{
	return (it - n);
}

template <class Iterator>
bool operator==(
	const random_access_iterator<Iterator>& lhs,
	const random_access_iterator<Iterator>& rhs)
{
	return (lhs._iter == rhs._iter);
}

template <class Iterator>
bool operator!= (
	const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs)
{
	return (lhs._iter != rhs._iter);
}

template <class Iterator>
bool operator< (
	const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs)
{
	return (lhs._iter < rhs._iter);
}

template <class Iterator>
bool operator<= (
	const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs)
{
	return (lhs._iter <= rhs._iter);
}

template <class Iterator>
bool operator> (
	const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs)
{
	return (lhs._iter > rhs._iter);
}

template <class Iterator>
bool operator>= (
	const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs)
{
	return (lhs._iter >= rhs._iter);
}

};