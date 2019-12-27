// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 4.1: Classes with Dynamic Memory
// mystring.h, mystring.cpp

#include "mystring.h"

using namespace std;
namespace cs_mystring{


int MyString::length() const {
    return strlen(thestring);
}






MyString::MyString() {
    thestring = new char[1];
}






MyString::MyString(const char *contents) {
    thestring = new char[strlen(contents) + 1];    
    strcpy(thestring, contents);
}






std::ostream& operator << (std::ostream& out, const MyString& object) {
    out << object.thestring;
    return out;
}






char MyString::operator [] (int index) const {
    assert(index >= 0 && index <= strlen(thestring));
    return thestring[index];
}






char& MyString::operator [] (int index) {
    assert(index >= 0 && index <= strlen(thestring));
    return thestring[index];
}







bool operator < (const MyString& objectA, const MyString& objectB) {
    return (strcmp(objectA.thestring, objectB.thestring) < 0);
}






bool operator > (const MyString& objectA, const MyString& objectB) {
    return (strcmp(objectA.thestring, objectB.thestring) > 0);
}






bool operator <= (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return true;
    }
    else if (strcmp(objectA.thestring, objectB.thestring) < 0) {
        return true;
    }
    return false;
}






bool operator >= (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return true;
    }
    else if (strcmp(objectA.thestring, objectB.thestring) > 0) {
        return true;
    }
    return false;
}






bool operator == (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return true;
    }
    return false;
}






bool operator != (const MyString& objectA, const MyString& objectB) {
    if (!strcmp(objectA.thestring, objectB.thestring)) {
        return false;
    }
    return true;
}






MyString MyString::operator = (const MyString& object) {
    if (this != &object) {
        delete [] thestring;
        thestring = new char[strlen(object.thestring) + 1];
        strcpy(thestring, object.thestring);
    }
    return *this;
}







MyString::MyString(const MyString& object) {
    thestring = new char[strlen(object.thestring) + 1];    
    strcpy(thestring, object.thestring);
}






MyString::~MyString() {
    delete [] thestring;
}






} // close namespace



/*
Nicole-Pav:A3 nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A3/" 
&& g++ client.cpp -o client && "/Users/nicolepavlovich/Desktop/CS_Foothill/A3/"client
----- Testing basic String creation & printing
string [0] = Wow
string [1] = C++ is neat!
string [2] = 
string [3] = a-z

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

----- Testing copy constructor and operator= on MyStrings
original is cake, copy is fake
original is cake, copy is fake
after self assignment, copy is Copy Cat
Testing pass & return MyStrings by value and ref
after calling Append, sum is Binky
val is winky
after assign,  val is Binky
Nicole-Pav:A3 nicolepavlovich$ 


*/