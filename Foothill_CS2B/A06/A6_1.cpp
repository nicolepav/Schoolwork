// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 6.1: Recursion (Part I)
// A6_1.cpp

// Description: This program demonstrates two functions: 
// reverseWithinBounds reverses an array of characters between two indicies
// reverseCString completely reverses a CString
// Both functions are implemented using recursion

#include <iostream>
#include <cstring>

using namespace std;

void reverseWithinBounds(char characters[], int lower, int upper);
void reverseCstring(char cstr[]);

int main () {

    char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char str[] = "example";

    cout << endl << "Character Array: ";
    for (int i = 0 ; i < sizeof(characters); i ++) {
        cout << characters[i] << " ";
    }

    cout << endl <<  "Reverse within bounds: ";
    reverseWithinBounds(characters, 0, sizeof(characters) - 1);
    for (int i = 0 ; i < sizeof(characters); i ++) {
        cout << characters[i] << " ";
    }


    cout << endl << "CString: " << str;
    cout << endl << "Revserse CString: ";
    reverseCstring(str);
    cout << str << endl << endl;
}






// Reverses an array of characters given a low bound lower and high bound upper
void reverseWithinBounds(char characters[], int lower, int upper) {
    if (upper - lower > 0) {
        char temp = characters[lower];
        characters[lower] = characters[upper];
        characters[upper] = temp;
        reverseWithinBounds(characters, lower + 1, upper - 1);
    }

}






// Reverse a cstring by checking for the terminating characters and then calling
// the reverseWithinBounds function
void reverseCstring(char cstr[]) {
    int location = 0;
    while (cstr[location] != '\0') {
        location++;
    }
    reverseWithinBounds(cstr, 0, location - 1);
}







/* Expected Output

Nicole-Pav:A6 nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A6/" 
&& g++ A6_1.cpp -o A6_1 && "/Users/nicolepavlovich/Desktop/CS_Foothill/A6/"A6_1

Character Array: a b c d e f g h 
Reverse within bounds: h g f e d c b a 
CString: example
Revserse CString: elpmaxe

Nicole-Pav:A6 nicolepavlovich$ 


*/
