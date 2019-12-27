// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 6.2: Recursion (Part II)
// A6_2.cpp, mystring.h

// Desciption: Program checks if a MyString object is a palindrome. Program ignores
// puncutation and whitespace, and does not modify or copy the argument in any way
// Program uses the custom MyString class from assignment A5. User may enter unlimited
// MyStrings and can exit program by entering "quit".

#include "mystring.h"
#include <cctype>
#include <string>

using namespace std;
using namespace cs_mystring;

bool isAPalindrome(MyString str, int low, int high);

int main() {

    MyString input = " ";

    cout << "Enter a string: ";
    input.read(cin, '\n');

    while(input != "quit") {
    
        if (isAPalindrome(input, 0, input.length()-1)) {
            cout << input << " is a palindrome" << endl;
        }
        else {
            cout << input << " is not a palindrome" << endl;
        }

        cout << "Enter a string: ";
        input.read(cin, '\n');
    }

}







// Checks if a MyString is a palindrome between two index bounds, low and high
bool isAPalindrome(MyString str, int low, int high) {

    if (isspace(str[low]) || ispunct(str[low])) {
        return(isAPalindrome(str, low + 1, high));
    }
    else if (isspace(str[high]) || ispunct(str[high])) {
        return(isAPalindrome(str, low, high - 1));
    }

    if (toupper(str[low]) == toupper(str[high])) {
        if (high - low > 0) {
            return(isAPalindrome(str, low+1, high-1));
        }
        return true;
    }
    else {
        return false;
    }
}







/* Expected Output

Nicole-Pav:A6 nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A6/" && 
g++ A6_2.cpp -o A6_2 && "/Users/nicolepavlovich/Desktop/CS_Foothill/A6/"A6_2

Enter a string: Able was I, ere I saw Elba
Able was I, ere I saw Elba is a palindrome
Enter a string: peanut butter
peanut butter is not a palindrome
Enter a string: taco cat
taco cat is a palindrome
Enter a string: a Toyota!
a Toyota! is a palindrome
Enter a string: racecar
racecar is a palindrome
Enter a string: starts and ends
starts and ends is not a palindrome
Enter a string: quit
Nicole-Pav:A6 nicolepavlovich$ 

*/