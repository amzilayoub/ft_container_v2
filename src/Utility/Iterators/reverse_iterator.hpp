/*
** reverse_iterator is an iterator adaptor that reverses
** the direction of a given iterator, which must be at least
** a LegacyBidirectionalIterator or model bidirectional_iterator (since C++20).
** In other words, when provided with a bidirectional iterator,
** std::reverse_iterator produces a new iterator that moves from
** the end to the beginning of the sequence defined by the underlying bidirectional iterator.
** For a reverse iterator r constructed from an iterator i,
** the relationship &*r == &*(i-1) is always true (as long as r is dereferenceable);
** thus a reverse iterator constructed from a one-past-the-end iterator
** dereferences to the last element in a sequence.
** This is the iterator returned by member functions
** rbegin() and rend() of the standard library containers.
*/

# pragma once

namespace ft
{

class reverse_iterator
{

};

};