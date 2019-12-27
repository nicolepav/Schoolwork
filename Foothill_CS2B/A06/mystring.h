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

// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 4.1: Classes with Dynamic Memory
// mystring.h, mystring.cpp


/*
    CLASS INVARIANT:

    There is one data member in this class. "thestring" is the cstring that 
    is used and manipulated. There are no private functions.

*/


#include <cassert>

using namespace std;
namespace cs_mystring {






// post: constructs an empty MyString object
MyString::MyString() {
    thestring = new char[1];
}






// post: constructs a MyString object with thestring equal to "contents"
MyString::MyString(const char *contents) {
    thestring = new char[strlen(contents) + 1];    
    strcpy(thestring, contents);
}






// post: copy constructor, copies one MyString object into the other 
MyString::MyString(const MyString& object) {
    thestring = new char[strlen(object.thestring) + 1];    
    strcpy(thestring, object.thestring);
}






// post: deconsructor, object is deleted and pointers are also deleted
MyString::~MyString() {
    delete [] thestring;
}






// post: returns the length of the MyString object it is called on
int MyString::length() const {
    return strlen(thestring);
}






// pre: you have a stream in and a char stopAt you would like to stop at 
// post: reads the stream until the specified character
// note: maximum string to be read by this method is 127 characters
void MyString::read(istream& in, char stopAt) {
    char temp[127];
    in.getline(temp, 127, stopAt);
    strcpy(thestring, temp);
}






// post: assignment operator, assigns a MyString to a Mystring
MyString MyString::operator = (const MyString& object) {
    if (this != &object) {
        delete [] thestring;
        thestring = new char[strlen(object.thestring) + 1];
        strcpy(thestring, object.thestring);
    }
    return *this;
}






// post: constant index operator returns char at a specific location
char MyString::operator [] (int index) const {
    assert(index >= 0 && index <= strlen(thestring));
    return thestring[index];
}






// post: reference index oeprator returns a reference to a location
char& MyString::operator [] (int index) {
    assert(index >= 0 && index <= strlen(thestring));
    return thestring[index];
}






// post: prints the MyString object to the stream
std::ostream& operator << (std::ostream& out, const MyString& object) {
    out << object.thestring;
    return out;
}






// post: reads a MyString object from the stream, max 127 char at a time
istream& operator >> (std::istream& in, MyString& object) {
    char temp[127];
    in >> temp;
    strcpy(object.thestring, temp);
    return in;
}






// post: returns true if objectA is less than objectB
bool operator < (const MyString& objectA, const MyString& objectB) {
    return (strcmp(objectA.thestring, objectB.thestring) < 0);
}






// post: returns true if objectA is greater than objectB
bool operator > (const MyString& objectA, const MyString& objectB) {
    return (strcmp(objectA.thestring, objectB.thestring) > 0);
}






// post: returns true if objectA is less than or equal to objectB
bool operator <= (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return true;
    }
    else if (strcmp(objectA.thestring, objectB.thestring) < 0) {
        return true;
    }
    return false;
}






// post: returns true if objectA is greater than or equal to objectB
bool operator >= (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return true;
    }
    else if (strcmp(objectA.thestring, objectB.thestring) > 0) {
        return true;
    }
    return false;
}






// post: returns true if objectA is identical to objectB
bool operator == (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return true;
    }
    return false;
}







// post: returns true if objectA is not identical to objectB
bool operator != (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return false;
    }
    return true;
}






// post: concantenates two MyStrings and returns the resulting string 
MyString operator + (const MyString& objectA, const MyString& objectB) {
    MyString result = new char[strlen(objectA.thestring) + strlen(objectB.thestring)];   
    strcpy(result.thestring, objectA.thestring);
    strcat(result.thestring, objectB.thestring);
    return result;
}






// post: appends objectB to the original (left side) myString object
MyString MyString::operator += (const MyString& objectB) {
    *this = *this + objectB;
    return *this;
}







} // close namespace






/* Program Output

Nicole-Pav:A5 nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A5/" && g++ mystring.cpp -o mystring && "/Users/nicolepavlovich/Desktop/CS_Foothill/A5/"mystring
----- Testing basic String creation & printing
string [0] = Wow
string [1] = C++ is neat!
string [2] = 
string [3] = a-z

----- Now reading MyStrings from file

----- first, word by word
Read string = The
Read string = first
Read string = time
Read string = we
Read string = will
Read string = read
Read string = individual
Read string = words,
Read string = next
Read string = we
Read string = read
Read string = whole
Read string = lines

----- now, line by line
Read string = The  first  time  we  will
Read string =     read individual words, next    
Read string = we read whole lines

----- Testing access to characters (using const)
Whole string is abcdefghijklmnopqsrtuvwxyz
now char by char: abcdefghijklmnopqsrtuvwxyz
----- Testing access to characters (using non-const)
Start with abcdefghijklmnopqsrtuvwxyz and convert to ABCDEFGHIJKLMNOPQSRTUVWXYZ

----- Testing relational operators between MyStrings
Comparing app to apple
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing apple to 
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing  to Banana
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing Banana to Banana
	Is left < right? false
	Is left <= right? true
	Is left > right? false
	Is left >= right? true
	Does left == right? true
	Does left != right ? false

----- Testing relations between MyStrings and char *
Comparing he to hello
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing why to wackity
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true

----- Testing concatentation on MyStrings
outrageous + milk = outrageousmilk
milk +  = milk
 + cow = cow
cow + bell = cowbell

----- Testing concatentation between MyString and char *
abcde + XYZ = abcdeXYZ
XYZ + abcde = XYZabcde

----- Testing shorthand concat/assign on MyStrings
who += what = whowhatandwhowhat
what += WHEN = whatWHENandwhatWHEN
WHEN += Where = WHENWhereandWHENWhere
Where += why = WherewhyandWherewhy

----- Testing shorthand concat/assign using char *
I love  += programming = I love programming

----- Testing copy constructor and operator= on MyStrings
original is cake, copy is fake
original is cake, copy is fake
after self assignment, copy is Copy Cat
Testing pass & return MyStrings by value and ref
after calling Append, sum is BinkyBoo
val is winky
after assign,  val is BinkyBoo
Nicole-Pav:A5 nicolepavlovich$ 



*/