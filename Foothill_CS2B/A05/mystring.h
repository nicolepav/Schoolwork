// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 4.1: Classes with Dynamic Memory
// mystring.h, mystring.cpp
// This class creates a custom string class that's implemented as a cstring
// Supports assignments, all comparison types, object copying, concatenation,
// and reading to a specified character.


/* * List of Public Prototypes
 * 
 * MyString();
 * post: constructs an empty MyString object
 * 
 * MyString(const char *contents);
 * post: constructs a MyString object with thestring equal to "contents"
 * 
 * MyString(const MyString& object);
 * post: copy constructor, copies one MyString object into the other 
 * 
 * ~MyString();
 * post: deconsructor, object is deleted and pointers are also deleted
 * 
 * int length() const;
 * post: returns the length of the MyString object it is called on
 * 
 * void read(istream& in, char stopAt);
 * pre: you have a stream in and a char stopAt you would like to stop at 
 * post: reads the stream until the specified character
 * 
 * MyString operator = (const MyString& object);
 * post: assignment operator, assigns a MyString to a Mystring
 * 
 * char operator [] (int index) const;
 * post: constant index operator returns char at a specific location
 * 
 * char& operator [] (int index);
 * post: reference index oeprator returns a reference to a location
 * 
 * friend ostream& operator << (std::ostream& out, const MyString& object);
 * post: prints the MyString object to the stream
 * 
 * friend istream& operator >> (std::istream& in, MyString& object);
 * post: reads a MyString object from the stream, max 127 char at a time
 * 
 * friend bool operator < (const MyString& objectA, const MyString& objectB);
 * post: returns true if objectA is less than objectB
 * 
 * friend bool operator > (const MyString& objectA, const MyString& objectB);
 * post: returns true if objectA is greater than objectB
 * 
 * friend bool operator <= (const MyString& objectA, const MyString& objectB);
 * post: returns true if objectA is less than or equal to objectB
 * 
 * friend bool operator >= (const MyString& objectA, const MyString& objectB);
 * post: returns true if objectA is greater than or equal to objectB
 * 
 * friend bool operator == (const MyString& objectA, const MyString& objectB);
 * post: returns true if objectA is identical to objectB
 * 
 * friend bool operator != (const MyString& objectA, const MyString& objectB);
 * post: returns true if objectA is not identical to objectB
 * 
 * friend MyString operator + (const MyString& objectA, const MyString& objectB);
 * post: concantenates two MyStrings and returns the resulting string 
 * 
 * MyString operator += (const MyString& objectB);
 * post: appends objectB to the original (left side) myString object
 * 
 * */



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

 
        MyString();
        MyString(const char *contents);
        MyString(const MyString& object);
        ~MyString();

        int length() const;
        void read(istream& in, char stopAt);

        MyString operator = (const MyString& object);
        char operator [] (int index) const;
        char& operator [] (int index);
   
        friend ostream& operator << (std::ostream& out, const MyString& object);
        friend istream& operator >> (std::istream& in, MyString& object);

        friend bool operator < (const MyString& objectA, const MyString& objectB);
        friend bool operator > (const MyString& objectA, const MyString& objectB);
        friend bool operator <= (const MyString& objectA, const MyString& objectB);
        friend bool operator >= (const MyString& objectA, const MyString& objectB);
        friend bool operator == (const MyString& objectA, const MyString& objectB);
        friend bool operator != (const MyString& objectA, const MyString& objectB);

        friend MyString operator + (const MyString& objectA, const MyString& objectB);
        MyString operator += (const MyString& objectB);

};


}

#endif
