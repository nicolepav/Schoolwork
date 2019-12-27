// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 4.1: Classes with Dynamic Memory
// mystring.h, mystring.cpp


#ifndef MYSTRING_H
#define MYSTRING_H


#include <iostream>
#include <cstring>
#include <assert.h>

using namespace std;
#pragma warning(disable:4996)


namespace cs_mystring{

class MyString {
    private:
        char *thestring; 

    public:

        // A length member function that returns the number of characters in the string. Use strlen().
        int length() const;

        // Construction of a MyString from a const c-string. 
        // Constructing a MyString with no arguments creates an empty MyString object (i.e. ""). 
        MyString();
        MyString(const char *contents);

        // Printing a MyString to a stream using an overloaded << (insertion) operator, 
        friend ostream& operator << (std::ostream& out, const MyString& object);

        // Your MyString object should overload the square brackets [ ] operator to allow direct access 
        char operator [] (int index) const;
        char& operator [] (int index);

        // They should be able to compare MyString objects to other MyStrings as well as MyStrings to c-strings. 
        // Confused? You don't need to worry about any of this: just use strcmp(). 
        // You must do this using only one function for each of the six operators.
        friend bool operator < (const MyString& objectA, const MyString& objectB);
        friend bool operator > (const MyString& objectA, const MyString& objectB);
        friend bool operator <= (const MyString& objectA, const MyString& objectB);
        friend bool operator >= (const MyString& objectA, const MyString& objectB);
        friend bool operator == (const MyString& objectA, const MyString& objectB);
        friend bool operator != (const MyString& objectA, const MyString& objectB);

        // Don't forget to include the big-3.
        MyString operator = (const MyString& object);
        MyString(const MyString& object);
        ~MyString();    
};


}

#endif
