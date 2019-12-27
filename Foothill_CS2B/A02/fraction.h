// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 2: Operator Overloading Part II
// fraction.h, fraction.cpp

// This header file allows you to create fractions with zero, one or two integer arguments.
// Acceptable input formats: integer (ex: 1), fraction (2/3, 3/2), mixed number (1+3/15)
// You can then perform the following operations on the fraction(s): 
// << >> + - / * > < >= <= == != += -= *= /= ++ -- 
// Program will output a fraction for arithmetic operations and true/false for comparisons

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

namespace cs_fraction {

class Fraction {
private:
    int numerator;
    int denominator;

    // Pre: A fraction object
    // Post: Reduces the numerator and denominator members to simplified form by checking for common factors
    void simplify();

public:
    
    // Pre: Constructor for fraction arguement, accepts two integers
    // Post: Creates a fraction object with a numerator (default 0) & denominator (default 1)
    Fraction(int n = 0, int d = 1);

    // Pre: A fraction object exists
    // Pos: Fraction object is deconstructed
    ~Fraction();

    // Pre: User types one or two integer arguments
    // Post: User arguments are used to create a fraction object
    friend std::istream& operator >> (std::istream& in, const Fraction& object);
    
    // Pre: A fraction object exists
    // Post: The fraction object is printed in fraction format
    friend std::ostream& operator << (std::ostream& out, const Fraction& object);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns a single fraction object that is the sum of the two arguments
    friend Fraction operator + (const Fraction& objectA, const Fraction& objectB);

    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns a single fraction object that is the difference of the two arguments
    friend Fraction operator - (const Fraction& objectA, const Fraction& objectB);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns a single fraction object that is the product of the two arguments
    friend Fraction operator * (const Fraction& objectA, const Fraction& objectB); 
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns a single fraction object that is the quotient of the two arguments
    friend Fraction operator / (const Fraction& objectA, const Fraction& objectB);   
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns true/false depending on if the first arguments is less than the second
    friend bool operator < (const Fraction& objectA, const Fraction& objectB);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns true/false depending on if the first arguments is more than the second
    friend bool operator > (const Fraction& objectA, const Fraction& objectB);

    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns true/false depending on if the first arguments is less than or equal to the second
    friend bool operator <= (const Fraction& objectA, const Fraction& objectB);

    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns true/false depending on if the first arguments is more than or equal to the second
    friend bool operator >= (const Fraction& objectA, const Fraction& objectB);

    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns true/false depending on if the first arguments is equal to the second
    friend bool operator == (const Fraction& objectA, const Fraction& objectB);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns true/false depending on if the first arguments is not equal to the second
    friend bool operator != (const Fraction& objectA, const Fraction& objectB);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns the sum of fraction object and the second argument
    friend Fraction operator += ( Fraction& objectA, const Fraction& objectB);

    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns the difference of fraction object and the second argument
    friend Fraction operator -= ( Fraction& objectA, const Fraction& objectB);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns the product of fraction object and the second argument
    friend Fraction operator *= ( Fraction& objectA, const Fraction& objectB);
    
    // Pre: A fraction object and either another fraction object or an integer
    // Post: Returns the quotient of fraction object and the second argument
    friend Fraction operator /= ( Fraction& objectA, const Fraction& objectB);

    // Pre: A fraction object 
    // Post: Adds 1 to the fraction object, then returns the object
    friend Fraction operator ++ (Fraction& object);

    // Pre: A fraction object
    // Post: returns the object, then adds 1 to the fraction object
    
    friend Fraction operator ++ (Fraction& object, int);

    // Pre: A fraction object
    // Post: Subtracts 1 from the fraction object, then returns the object
    friend Fraction operator -- (Fraction& object);

    // Pre: A fraction object
    // Post: returns the object, then subtracts 1 from the fraction object
    friend Fraction operator -- (Fraction& object, int);
};


}
#endif