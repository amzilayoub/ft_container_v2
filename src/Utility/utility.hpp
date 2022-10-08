/*
** Construct pair
** Constructs a pair object.
** This involves individually constructing its two component objects, with an initialization that depends on the constructor form invoked.
*/

# pragma once

namespace ft
{


template <class T1, class T2>
struct pair {
    /* ============================== MEMBER TYPE ============================== */
    typedef T1  first_type;
    typedef T2  second_type;

    /* ============================== MEMBER ATTRIBTE ============================== */
    first_type      first;
    second_type     second;

    /* ============================== CONSTRUCTORS ============================== */
    /*
    ** default constructor
    ** Constructs a pair object with its elements value-initialized.
    ** @param void void
    ** @return void
    */
    pair() : first(), second()
    {
    }

    /*
    ** initialization constructor
    ** Member first is constructed with a and member second with b. 
    ** @param x An object of the type of first, or some other type implicitly convertible to it.
    ** @param y An object of the type of second, or some other type implicitly convertible to it.
    ** @return void
    */
    pair(const first_type& x, const second_type& y) : first(x), second(y)
    {
    }

    /*
    ** copy / move constructor (and implicit conversion)
    ** The object is initialized with the contents of the pr pair object.
    ** The corresponding member of pr is passed to the constructor of each of its members.
    ** @param pr Another pair object.
    ** @return void
    */
    template<class U, class V>
	pair(const pair<U, V> &p) : first(p.first), second(p.second)
    {
    }

    /* ============================== CONSTRUCTORS ============================== */
    pair    &operator=(pair const &rhs)
    {
        if (this == &rhs)
            return (*this);
        this->first = rhs.first;
        this->second = rhs.second;

        return (*this);
    }

};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return ((x.first == y.first) && (x.second == y.second));
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(x == y);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(y < x);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return (y < x);
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return (y <= x);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
    return (ft::pair<T1, T2>(x, y));
}

};