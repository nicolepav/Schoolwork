// PAVLOVICH, NICOLE
// CS12 PROJECT 06: RECURSIVE PALINDROME CHECKER

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

bool ispalindrome(string str);

int main () {

    char input = ' ';
    string sinput = "";

	cout << endl << "Input a string: ";
    getline(cin, sinput);

    ispalindrome(sinput);
    cout << endl;
}

bool ispalindrome(string str) {

    if (str.length() == 0) {
        cout << "This is a palindrome" << endl;
        return true;
    }
    else if (str[0] != str[str.length()-1]) {
        cout << "characters " << str[0] << " and " << str[str.length()-1] << " do not match." << endl;
        cout << "This is not a palindrome" << endl << endl;
        return false;
    }
    else if (str[0] == str[str.length()-1]) {
        // if the first and last characters match, create a substring
        string substr = str.substr(1, str.length()-2);
        
        // check the substring for palindrome
        ispalindrome(substr);
    }
    else {
        cout << "Something went wrong" << endl;
    }

    return true;
};