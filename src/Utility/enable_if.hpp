/*
** Enable type if condition is met
** The type T is enabled as member type enable_if::type if Cond is true.
** Otherwise, enable_if::type is not defined.
** This is useful to hide signatures on compile time when a particular
** condition is not met, since in this case, the member enable_if::type
** will not be defined and attempting to compile using it should fail.
*/

# pragma once

/*
** Enable type if condition is met
** @param Cond A compile-time constant of type bool.
** @param T a Type
** @return void
*/

namespace ft
{

template<bool Cond, class T = void> struct enable_if {};

template<class T> struct enable_if<true, T> { typedef T type; };

};