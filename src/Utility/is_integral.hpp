/*
** Trait class that identifies whether T is an integral type.
** It inherits from integral_constant as being either
** true_type or false_type, depending on whether T is an integral type:

** |--------------------------------|
** | fundamental integral types     |
** |--------------------------------|
** | bool                           |
** | char                           |
** | char16_t                       |
** | char32_t                       |
** | wchar_t                        |
** | signed char                    |
** | short int                      |
** | int                            |
** | long int                       |
** | long long int                  |
** | unsigned char                  |
** | unsigned short int             |
** | unsigned int                   |
** | unsigned long int              |
** | unsigned long long int         |
** |--------------------------------|
**
*/

# pragma once

namespace ft
{

template <class T>
struct is_integral
{
    typedef T           type;

    static const bool	value = false;
};

template <>
struct is_integral<bool>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<char>
{
    typedef bool		type;

    static const bool	value = true;
};

/*
** Since we're using C++98, the types char16_t and char32_t
** are not defined yet. (they are defined in C++11)
**
** template <>
** struct is_integral<char16_t>
** {
**     typedef bool		type;
** 
**     static const bool	value = true;
** };
** 
** template <>
** struct is_integral<char32_t>
** {
**     typedef bool		type;
** 
**     static const bool	value = true;
** };
**
*/

template <>
struct is_integral<wchar_t>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<signed char>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<short int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<long int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<long long int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<unsigned char>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<unsigned short int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<unsigned int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<unsigned long int>
{
    typedef bool		type;

    static const bool	value = true;
};

template <>
struct is_integral<unsigned long long int>
{
    typedef bool		type;

    static const bool	value = true;
};

};