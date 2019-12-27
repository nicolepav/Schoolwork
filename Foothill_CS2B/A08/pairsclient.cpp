// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 8.2: Templates & Exceptions
// orderedpair.cpp orderedpair.h pairsclient.cpp

// Description: Allows you to create ordered pair of various types
// using a template class OrderedPair. Throws an exception if user 
// attempts to create a pair with duplicate non default members

// No documentation required for this project


#include <iostream>
#include <ctime>
#include <cstdlib>
#include "orderedpair.h"


using namespace std;
using namespace cs_pairs;


int main() {


    // Integer Version

    cout << endl << "-------------Integers---------------" << endl;
    int num1, num2;
    OrderedPair<int> myList[10];
    
    srand(static_cast<unsigned>(time(0)));
    cout << "default value: ";
    myList[0].print();
    cout << endl;
    
    for (int i = 0; i < 10; i++) {
        myList[i].setFirst(rand() % 50);
        myList[i].setSecond(rand() % 50 + 50);
    }
    
    myList[2] = myList[0] + myList[1];
    
    if (myList[0] < myList[1]) {
        myList[0].print();
        cout << " is less than ";
        myList[1].print(); 
        cout << endl;
    }
    
    for (int i = 0; i < 10; i++) {
        myList[i].print();
        cout << endl;
    }
    
    cout << "Enter two numbers to use in an OrderedPair.  Make sure they are different numbers: ";
    cin >> num1 >> num2;
    OrderedPair<int> x;
    
    try {
        x.setFirst(num1);
        x.setSecond(num2);
    } catch (OrderedPair<int>::DuplicateMemberError e) {
        x.setFirst(OrderedPair<int>::DEFAULT_VALUE);
        x.setSecond(OrderedPair<int>::DEFAULT_VALUE);        
    }
    
    cout << "The resulting OrderedPair: ";
    x.print();
    cout << endl;






    // String Version

    cout << endl << "-------------Strings---------------" << endl;
    string s1, s2;
    OrderedPair<string> myList2[10];
    
    srand(static_cast<unsigned>(time(0)));
    cout << "default value: ";
    myList2[0].print();
    cout << endl;
    
    for (int i = 0; i < 10; i++) {
        string empty = "";
        myList2[i].setFirst(empty + char('a' + rand() % 26));
        myList2[i].setSecond(empty + char('A' + rand() % 26));
    }
    
    myList2[2] = myList2[0] + myList2[1];
    
    if (myList2[0] < myList2[1]) {
        myList2[0].print();
        cout << " is less than ";
        myList2[1].print(); 
        cout << endl;
    }
    
    for (int i = 0; i < 10; i++) {
        myList2[i].print();
        cout << endl;
    }
    
    cout << "Enter two strings to use in an OrderedPair.  Make sure they are different: ";
    cin >> s1 >> s2;
    OrderedPair<string> s;
    
    try {
        s.setFirst(s1);
        s.setSecond(s2);
    } catch (OrderedPair<string>::DuplicateMemberError e) {
        s.setFirst(OrderedPair<string>::DEFAULT_VALUE);
        s.setSecond(OrderedPair<string>::DEFAULT_VALUE);        
    }

    cout << "The resulting OrderedPair: ";
    s.print();
    cout << endl;
}


/* Expected Output

Nicole-Pav:A8b nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A8b/" && 
g++ pairsclient.cpp -o pairsclient && "/Users/nicolepavlovich/Desktop/CS_Foothill/A8b/"pairsclient

-------------Integers---------------
default value: (0, 0)
(32, 99)
(29, 63)
(61, 162)
(2, 97)
(21, 55)
(25, 72)
(40, 71)
(35, 70)
(40, 84)
(37, 65)
Enter two numbers to use in an OrderedPair.  Make sure they are different numbers: 2 2
The resulting OrderedPair: (0, 0)

-------------Strings---------------
default value: (, )
(h, G) is less than (p, A)
(h, G)
(p, A)
(hp, GA)
(o, G)
(y, R)
(k, F)
(p, D)
(f, I)
(h, B)
(w, L)
Enter two strings to use in an OrderedPair.  Make sure they are different: abc abc
The resulting OrderedPair: (, )
Nicole-Pav:A8b nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A8b/" && 
g++ pairsclient.cpp -o pairclient && "/Users/nicolepavlovich/Desktop/CS_Foothill/A8b/"pairsclient

-------------Integers---------------
default value: (0, 0)
(38, 94)
(31, 86)
(69, 180)
(4, 89)
(20, 51)
(4, 57)
(47, 57)
(34, 56)
(21, 66)
(16, 61)
Enter two numbers to use in an OrderedPair.  Make sure they are different numbers: 1 2
The resulting OrderedPair: (1, 2)

-------------Strings---------------
default value: (, )
(v, H)
(f, R)
(vf, HR)
(e, K)
(o, L)
(b, W)
(s, V)
(b, R)
(r, L)
(q, P)
Enter two strings to use in an OrderedPair.  Make sure they are different: abc def
The resulting OrderedPair: (abc, def)
Nicole-Pav:A8b nicolepavlovich$ 

*/