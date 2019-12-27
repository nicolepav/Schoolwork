
// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 8.2: Templates & Exceptions
// orderedpair.cpp orderedpair.h pairsclient.cpp

// Description: Allows you to create ordered pair of various types
// using a template class OrderedPair. Throws an exception if user 
// attempts to create a pair with duplicate non default members

// No documentation required for this project

#include <iostream>
#include <exception>

using namespace std;

namespace cs_pairs {

    template <class T>
    class OrderedPair {
        public:

            static const T DEFAULT_VALUE;

            OrderedPair(T newFirst = DEFAULT_VALUE, T newSecond = DEFAULT_VALUE);
            void setFirst(T newFirst);
            void setSecond(T newSecond);
            T getFirst() const;
            T getSecond() const;
            OrderedPair operator+(const OrderedPair& right) const;
            bool operator<(const OrderedPair& right) const;
            void print() const;


            /* precondition for setFirst and setSecond: the values of first and second cannot be equal, 
            except when they are both equal to DEFAULT_VALUE. */
            class DuplicateMemberError { };


        private:
            T first;
            T second;
    };
    
    template <class T>
    const T OrderedPair<T>::DEFAULT_VALUE = T();

}

#include "orderedpair.cpp"
