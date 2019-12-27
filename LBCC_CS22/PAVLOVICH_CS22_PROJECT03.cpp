#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

#include "queuefile.h" // Queue file from textbook
#include "stackfile.h" // Stack file from textbook

using namespace std;

int main()
{
    char input = ' ';

    stackType<char> charStack(100);
    queueType<char> charQueue(100);

	cout << endl << "Input a series of characters: ";
    while (cin.peek() != '\n')
    {
    	// Write a program that reads a line of text, 
		cin >> input;
		
		// changes each uppercase letter to lowercase, 
		// and places each letter both in a queue and onto a stack. 
		charStack.push(tolower(input));
		charQueue.addQueue(tolower(input));
    }
	cout << endl;
	
	// The program should then verify whether the line of text is a palindrome
	bool ispalindrome = true;
	while (!charStack.isEmptyStack())
	{
		// charstack off top gives the ordered version
		// charqueue off front gives the reversed version

		if(charStack.top() != charQueue.front())
		{
			// therefore charstack.top() and charqueue.front() must give the same value 
			ispalindrome = false;
		}

		charStack.pop();
		charQueue.deleteQueue();
	}
	if (ispalindrome)
	{
		cout << "This is a palindrome!" << endl;
	}
	else 
	{
		cout << "This is not a palindrome" << endl;
	}
	cout << endl;

}