// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 1: Operator Overloading 
// a1_1.cpp 

// Description: This program accepts zero, one, or two integer arguments to create a fraction.
// You can then perform the following operations on the fraction(s): 
// << >> + - / * > < >= <= == != += -= *= /= ++ -- 
// Program will output a fraction for arithmetic operations and true/false for comparisons

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

public:
    
    Fraction(int n = 0, int d = 1);
    ~Fraction();

    friend istream& operator >> (istream& in, const Fraction& object);
    friend ostream& operator << (ostream& out, const Fraction& object);
    
    friend Fraction operator + (const Fraction& objectA, const Fraction& objectB);
    friend Fraction operator - (const Fraction& objectA, const Fraction& objectB);
    friend Fraction operator * (const Fraction& objectA, const Fraction& objectB); 
    friend Fraction operator / (const Fraction& objectA, const Fraction& objectB);   
    
    friend bool operator < (const Fraction& objectA, const Fraction& objectB);
    friend bool operator > (const Fraction& objectA, const Fraction& objectB);

    friend bool operator <= (const Fraction& objectA, const Fraction& objectB);
    friend bool operator >= (const Fraction& objectA, const Fraction& objectB);
    friend bool operator == (const Fraction& objectA, const Fraction& objectB);
    friend bool operator != (const Fraction& objectA, const Fraction& objectB);
    
    friend Fraction operator += ( Fraction& objectA, const Fraction& objectB);
    friend Fraction operator -= ( Fraction& objectA, const Fraction& objectB);
    friend Fraction operator *= ( Fraction& objectA, const Fraction& objectB);
    friend Fraction operator /= ( Fraction& objectA, const Fraction& objectB);

    friend Fraction operator ++ (Fraction& object);
    friend Fraction operator ++ (Fraction& object, int);
    friend Fraction operator -- (Fraction& object);
    friend Fraction operator -- (Fraction& object, int);
};

// Pre: Constructor for fraction arguement, accepts two integers
// Post: Creates a fraction object with a numerator (default 0) & denominator (default 1)
Fraction::Fraction(int n, int d) {
    assert(d != 0);
    numerator = n;
    denominator = d;
}

// Pre: A fraction object exists
// Pos: Fraction object is deconstructed
Fraction::~Fraction(){
}

// Pre: User types one or two integer arguments
// Post: User arguments are used to create a fraction object
istream& operator >> (istream& in, const Fraction& object) {
    in >> object.numerator >> object.denominator;
    return in;
}

// Pre: A fraction object exists
// Post: The fraction object is printed in fraction format
ostream& operator << (ostream& out, const Fraction& object) {
    out << object.numerator << '/' << object.denominator;
    return out;
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns a single fraction object that is the sum of the two arguments
Fraction operator + (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.denominator) + (objectB.numerator * objectA.denominator);
    int d = (objectA.denominator * objectB.denominator);
    return Fraction(n,d);
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns a single fraction object that is the difference of the two arguments
Fraction operator - (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.denominator) - (objectB.numerator * objectA.denominator);
    int d = (objectA.denominator * objectB.denominator);   
    return Fraction(n,d);
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns a single fraction object that is the product of the two arguments
Fraction operator * (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.numerator);
    int d = (objectA.denominator * objectB.denominator);
    return Fraction(n,d);
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns a single fraction object that is the quotient of the two arguments
Fraction operator / (const Fraction& objectA, const Fraction& objectB) {
    int n = (objectA.numerator * objectB.denominator);
    int d = (objectA.denominator * objectB.numerator);
    return Fraction(n,d);
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns true/false depending on if the first arguments is less than the second
bool operator < (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A < B );
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns true/false depending on if the first arguments is more than the second
bool operator > (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A > B );
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns true/false depending on if the first arguments is less than or equal to the second
bool operator <= (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A <= B );
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns true/false depending on if the first arguments is more than or equal to the second
bool operator >= (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A >= B );
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns true/false depending on if the first arguments is equal to the second
bool operator == (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A == B );
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns true/false depending on if the first arguments is not equal to the second
bool operator != (const Fraction& objectA, const Fraction& objectB) {
    int A = (objectA.numerator * objectB.denominator);
    int B = (objectB.numerator * objectA.denominator);
    return ( A != B );
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns the sum of fraction object and the second argument
Fraction operator += (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator = (objectA.numerator * objectB.denominator) + (objectB.numerator * objectA.denominator);
    objectA.denominator = (objectA.denominator * objectB.denominator);
    return objectA;
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns the difference of fraction object and the second argument
Fraction operator -= (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator = (objectA.numerator * objectB.denominator) - (objectB.numerator * objectA.denominator);
    objectA.denominator = (objectA.denominator * objectB.denominator);
    return objectA;
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns the product of fraction object and the second argument
Fraction operator *= (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator  = (objectA.numerator * objectB.numerator);
    objectA.denominator = (objectA.denominator * objectB.denominator);
    return objectA;
}

// Pre: A fraction object and either another fraction object or an integer
// Post: Returns the quotient of fraction object and the second argument
Fraction operator /= (Fraction& objectA, const Fraction& objectB) {
    objectA.numerator = (objectA.numerator * objectB.denominator);
    objectA.denominator = (objectA.denominator * objectB.numerator);
    return objectA;
}

// Pre: A fraction object 
// Post: Adds 1 to the fraction object, then returns the object
Fraction operator ++ (Fraction& objectA) {
    objectA.numerator = objectA.numerator + objectA.denominator;
    return objectA;
}

// Pre: A fraction object
// Post: Subtracts 1 from the fraction object, then returns the object
Fraction operator -- (Fraction& objectA) {
    objectA.numerator = objectA.numerator - objectA.denominator;
    return objectA;

}

// Pre: A fraction object
// Post: returns the object, then adds 1 to the fraction object
Fraction operator ++ (Fraction& objectA, int) {
    int n = objectA.numerator, d = objectA.denominator;
    objectA.numerator = objectA.numerator + objectA.denominator;    
    return Fraction(n,d);
}

// Pre: A fraction object
// Post: returns the object, then subtracts 1 from the fraction object
Fraction operator -- (Fraction& objectA, int) {
    int n = objectA.numerator, d = objectA.denominator;
    objectA.numerator = objectA.numerator - objectA.denominator;
    return Fraction(n, d);
}






// client program as provided by instructor

void BasicTest();
void RelationTest();
void BinaryMathTest();
void MathAssignTest();
string boolString(bool convertMe);

int main()
{
    BasicTest();
    RelationTest();
    BinaryMathTest();
    MathAssignTest();
}





void BasicTest()
{
    cout << "\n----- Testing basic Fraction creation & printing\n";
    
    const Fraction fr[] = {Fraction(4, 8), Fraction(-15,21), 
                           Fraction(10), Fraction(12, -3),
                           Fraction(), Fraction(28, 6), Fraction(0, 12)};
                                                   
    for (int i = 0; i < 7; i++){
        cout << "Fraction [" << i <<"] = " << fr[i] << endl;
    }
}

string boolString(bool convertMe) {
	if (convertMe) {
		return "true";
	} else {
		return "false";
	}
}


void RelationTest()
{
    cout << "\n----- Testing relational operators between Fractions\n";

    const Fraction fr[] =  {Fraction(3, 6), Fraction(-15, 30), Fraction(1, 2), 
                            Fraction(1,10), Fraction(0,1), Fraction(0,2)};

    for (int i = 0; i < 5; i++) {
          cout << "Comparing " << fr[i] << " to " << fr[i+1] << endl;
          cout << "\tIs left < right? " << boolString(fr[i] < fr[i+1]) << endl;
          cout << "\tIs left <= right? " << boolString(fr[i] <= fr[i+1]) << endl;
          cout << "\tIs left > right? " << boolString(fr[i] > fr[i+1]) << endl;
          cout << "\tIs left >= right? " << boolString(fr[i] >= fr[i+1]) << endl;
          cout << "\tDoes left == right? " << boolString(fr[i] == fr[i+1]) << endl;
          cout << "\tDoes left != right ? " << boolString(fr[i] != fr[i+1]) << endl;
    }
 
    cout << "\n----- Testing relations between Fractions and integers\n";
    Fraction f(-3,6);
    int num = 2;
    cout << "Comparing " << f << " to " << num << endl;
    cout << "\tIs left < right? " << boolString(f < num) << endl;
    cout << "\tIs left <= right? " << boolString(f <= num) << endl;
    cout << "\tIs left > right? " << boolString(f > num) << endl;
    cout << "\tIs left >= right? " << boolString(f >= num) << endl;
    cout << "\tDoes left == right? " << boolString(f == num) << endl;
    cout << "\tDoes left != right ? " << boolString(f != num) << endl;
    
    Fraction g(1,4);
    num = -3;
    cout << "Comparing " << num << " to " << g << endl;
    cout << "\tIs left < right? " << boolString(num < g) << endl;
    cout << "\tIs left <= right? " << boolString(num <= g) << endl;
    cout << "\tIs left > right? " << boolString(num > g) << endl;
    cout << "\tIs left >= right? " << boolString(num >= g) << endl;
    cout << "\tDoes left == right? " << boolString(num == g) << endl;
    cout << "\tDoes left != right ? " << boolString(num != g) << endl;  
}

void BinaryMathTest()
{    
    cout << "\n----- Testing binary arithmetic between Fractions\n";
    
    const Fraction fr[] = {Fraction(1, 6), Fraction(1,3), 
                           Fraction(-2,3), Fraction(5), Fraction(-4,3)};

    for (int i = 0; i < 4; i++) {
          cout << fr[i] << " + " << fr[i+1] << " = " << fr[i] + fr[i+1] << endl;
          cout << fr[i] << " - " << fr[i+1] << " = " << fr[i] - fr[i+1] << endl;
          cout << fr[i] << " * " << fr[i+1] << " = " << fr[i] * fr[i+1] << endl;
          cout << fr[i] << " / " << fr[i+1] << " = " << fr[i] / fr[i+1] << endl;
    }

    cout << "\n----- Testing arithmetic between Fractions and integers\n";
    Fraction f(-1, 2);
    int num = 4;
    cout << f << " + " << num << " = " << f + num << endl;
    cout << f << " - " << num << " = " << f - num << endl;
    cout << f << " * " << num << " = " << f * num << endl;
    cout << f << " / " << num << " = " << f / num << endl;
     
    Fraction g(-1, 2);
    num = 3;
    cout << num << " + " << g << " = " << num + g << endl;
    cout << num << " - " << g << " = " << num - g << endl;
    cout << num << " * " << g << " = " << num * g << endl;
    cout << num << " / " << g << " = " << num / g << endl;
}


void MathAssignTest()
{    
    cout << "\n----- Testing shorthand arithmetic assignment on Fractions\n";
    
    Fraction fr[] = {Fraction(1, 6), Fraction(4), 
                     Fraction(-1,2), Fraction(5)};

    for (int i = 0; i < 3; i++) {
          cout << fr[i] << " += " << fr[i+1] << " = ";
          cout << (fr[i] += fr[i+1]) << endl;
          cout << fr[i] << " -= " << fr[i+1] << " = ";
          cout << (fr[i] -= fr[i+1]) << endl;
          cout << fr[i] << " *= " << fr[i+1] << " = ";
          cout << (fr[i] *= fr[i+1]) << endl;
          cout << fr[i] << " /= " << fr[i+1] << " = ";
          cout << (fr[i] /= fr[i+1]) << endl;
    }
   
    cout << "\n----- Testing shorthand arithmetic assignment using integers\n";
    Fraction f(-1, 3);
    int num = 3;
    cout << f << " += " << num << " = ";
    cout << (f += num) << endl;
    cout << f << " -= " << num << " = ";
    cout << (f -= num) << endl;
    cout << f << " *= " << num << " = ";
    cout << (f *= num) << endl;
    cout << f << " /= " << num << " = ";
    cout << (f /= num) << endl;

    cout << "\n----- Testing increment/decrement prefix and postfix\n";
    Fraction g(-1, 3);
    cout << "Now g = " << g << endl;
    cout << "g++ = " << g++ << endl;
    cout << "Now g = " << g << endl;
    cout << "++g = " << ++g << endl;
    cout << "Now g = " << g << endl;
    cout << "g-- = " << g-- << endl;
    cout << "Now g = " << g << endl;
    cout << "--g = " << --g << endl;
    cout << "Now g = " << g << endl;
}





// Program Output
/*
    Nicole-Pav:CS_Foothill nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/" && g++ a1_1.cpp -o a1_1 && "/Users/nicolepavlovich/Desktop/CS_Foothill/"a1_1

    ----- Testing basic Fraction creation & printing
    Fraction [0] = 4/8
    Fraction [1] = -15/21
    Fraction [2] = 10/1
    Fraction [3] = 12/-3
    Fraction [4] = 0/1
    Fraction [5] = 28/6
    Fraction [6] = 0/12

    ----- Testing relational operators between Fractions
    Comparing 3/6 to -15/30
        Is left < right? false
        Is left <= right? false
        Is left > right? true
        Is left >= right? true
        Does left == right? false
        Does left != right ? true
    Comparing -15/30 to 1/2
        Is left < right? true
        Is left <= right? true
        Is left > right? false
        Is left >= right? false
        Does left == right? false
        Does left != right ? true
    Comparing 1/2 to 1/10
        Is left < right? false
        Is left <= right? false
        Is left > right? true
        Is left >= right? true
        Does left == right? false
        Does left != right ? true
    Comparing 1/10 to 0/1
        Is left < right? false
        Is left <= right? false
        Is left > right? true
        Is left >= right? true
        Does left == right? false
        Does left != right ? true
    Comparing 0/1 to 0/2
        Is left < right? false
        Is left <= right? true
        Is left > right? false
        Is left >= right? true
        Does left == right? true
        Does left != right ? false

    ----- Testing relations between Fractions and integers
    Comparing -3/6 to 2
        Is left < right? true
        Is left <= right? true
        Is left > right? false
        Is left >= right? false
        Does left == right? false
        Does left != right ? true
    Comparing -3 to 1/4
        Is left < right? true
        Is left <= right? true
        Is left > right? false
        Is left >= right? false
        Does left == right? false
        Does left != right ? true

    ----- Testing binary arithmetic between Fractions
    1/6 + 1/3 = 9/18
    1/6 - 1/3 = -3/18
    1/6 * 1/3 = 1/18
    1/6 / 1/3 = 3/6
    1/3 + -2/3 = -3/9
    1/3 - -2/3 = 9/9
    1/3 * -2/3 = -2/9
    1/3 / -2/3 = 3/-6
    -2/3 + 5/1 = 13/3
    -2/3 - 5/1 = -17/3
    -2/3 * 5/1 = -10/3
    -2/3 / 5/1 = -2/15
    5/1 + -4/3 = 11/3
    5/1 - -4/3 = 19/3
    5/1 * -4/3 = -20/3
    5/1 / -4/3 = 15/-4

    ----- Testing arithmetic between Fractions and integers
    -1/2 + 4 = 7/2
    -1/2 - 4 = -9/2
    -1/2 * 4 = -4/2
    -1/2 / 4 = -1/8
    3 + -1/2 = 5/2
    3 - -1/2 = 7/2
    3 * -1/2 = -3/2
    3 / -1/2 = 6/-1

    ----- Testing shorthand arithmetic assignment on Fractions
    1/6 += 4/1 = 25/6
    25/6 -= 4/1 = 1/6
    1/6 *= 4/1 = 4/6
    4/6 /= 4/1 = 4/24
    4/1 += -1/2 = 7/2
    7/2 -= -1/2 = 16/4
    16/4 *= -1/2 = -16/8
    -16/8 /= -1/2 = -32/-8
    -1/2 += 5/1 = 9/2
    9/2 -= 5/1 = -1/2
    -1/2 *= 5/1 = -5/2
    -5/2 /= 5/1 = -5/10

    ----- Testing shorthand arithmetic assignment using integers
    -1/3 += 3 = 8/3
    8/3 -= 3 = -1/3
    -1/3 *= 3 = -3/3
    -3/3 /= 3 = -3/9

    ----- Testing increment/decrement prefix and postfix
    Now g = -1/3
    g++ = -1/3
    Now g = 2/3
    ++g = 5/3
    Now g = 5/3
    g-- = 5/3
    Now g = 2/3
    --g = -1/3
    Now g = -1/3
    Nicole-Pav:CS_Foothill nicolepavlovich$ 
*/