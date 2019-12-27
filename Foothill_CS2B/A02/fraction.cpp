#include <iostream>
#include <string>
#include <cassert>

#include "fraction.h"


namespace cs_fraction{

void Fraction::simplify() {
    int smaller;
    if (numerator < denominator) {
        smaller = numerator;
    }
    else {
        smaller = denominator;
    }

    for (int j = 1; j < smaller; j++) {      
        for (int i = 2; i <= smaller; i ++) {
            if( !(numerator % i) && !(denominator % i) ) {
                numerator = numerator / i;
                denominator = denominator / i;
                i = 0, j = 0; 
            }
            else {
                j++;
            }
        }
    }

    if (denominator < 0) {
        numerator = numerator * -1;
        denominator = denominator * -1;
    }
}



Fraction::Fraction(int n, int d) {
    assert(d != 0);
    numerator = n;
    denominator = d;
    simplify();
}


Fraction::~Fraction(){
}



std::istream& operator >> (std::istream& in, const Fraction& object) {
    
    in >> object.numerator >> object.denominator;
    
    // int temp;
    // char toss;
    
    // in >> temp;
    // // this section is a work in progress as of 10/6/19 4:15 pm
    // if (in.peek() == '+'){
    //     //in.putback(temp);
    //     in >> toss >> object.numerator >> toss >> object.denominator;

    //     // numerator = temp * denominator) + numerator after plus
    // } else if (in.peek() == '/'){
    //     in.putback(temp);
    //     in >> object.numerator >> toss >> object.denominator;
    // } else {
    //     in.putback(temp);
    //     in >> object.numerator;
    // }

    return in;
}


std::ostream& operator << (std::ostream& out, const Fraction& object) {
    
    if (object.denominator) {
        out << object.numerator;
    }
    else if (object.denominator < object.numerator) {
        int whole, part;
        whole = object.numerator / object.denominator;
        part = object.numerator - (object.denominator * (whole));
        
        if(object.numerator < 0) {
            whole *= -1;
            part *= -1;
        }
        
        out << whole << '+' << part << '/' << object.denominator;
    }
    else {
        out << object.numerator << '/' << object.denominator;
    }
    
    return out;
}


Fraction operator + (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.denominator) + (objectB.numerator * objectA.denominator);
    int d = (objectA.denominator * objectB.denominator);
    Fraction sum = Fraction(n, d);
    return sum;
}


Fraction operator - (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.denominator) - (objectB.numerator * objectA.denominator);
    int d = (objectA.denominator * objectB.denominator);
    Fraction difference = Fraction(n,d);   
    return difference;
}


Fraction operator * (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.numerator);
    int d = (objectA.denominator * objectB.denominator);
    Fraction product = Fraction(n,d);
    return product;
}


Fraction operator / (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.denominator);
    int d = (objectA.denominator * objectB.numerator);
    Fraction quotient = Fraction(n, d);
    return quotient;
}


bool operator < (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A < B );
}


bool operator > (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A > B );
}


bool operator <= (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A <= B );
}


bool operator >= (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A >= B );
}


bool operator == (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A == B );
}


bool operator != (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A != B );
}


Fraction operator += (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator = (objectA.numerator * objectB.denominator) + (objectB.numerator * objectA.denominator);
    objectA.denominator = (objectA.denominator * objectB.denominator);
    objectA.simplify();
    return objectA;
}


Fraction operator -= (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator = (objectA.numerator * objectB.denominator) - (objectB.numerator * objectA.denominator);
    objectA.denominator = (objectA.denominator * objectB.denominator);
    objectA.simplify();
    return objectA;
}


Fraction operator *= (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator  = (objectA.numerator * objectB.numerator);
    objectA.denominator = (objectA.denominator * objectB.denominator);
    objectA.simplify();
    return objectA;
}


Fraction operator /= (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator = (objectA.numerator * objectB.denominator);
    objectA.denominator = (objectA.denominator * objectB.numerator);
    objectA.simplify();
    return objectA;
}


Fraction operator ++ (Fraction& objectA) {
    objectA.numerator = objectA.numerator + objectA.denominator;
    objectA.simplify();
    return objectA;
}


Fraction operator -- (Fraction& objectA) {
    objectA.numerator = objectA.numerator - objectA.denominator;
    objectA.simplify();
    return objectA;

}


Fraction operator ++ (Fraction& objectA, int) {
    int n = objectA.numerator, d = objectA.denominator;
    objectA.numerator = objectA.numerator + objectA.denominator;
    return Fraction(n,d);
}


Fraction operator -- (Fraction& objectA, int) {
    int n = objectA.numerator, d = objectA.denominator;
    objectA.numerator = objectA.numerator - objectA.denominator;
    return Fraction(n, d);
}



}