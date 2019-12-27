//This program tests various operation of a linked list

#include <iostream> 
#include <cassert> 
#include <string>

#include "circularlinkedlist.h"

using namespace std;

char listactions();
circularLinkedList<int> doactionsInteger(char choice, char listtype, circularLinkedList<int> list);
circularLinkedList<string> doactionsString(char choice, char listtype, circularLinkedList<string> list);
circularLinkedList<char> doactionsChar(char choice, char listtype, circularLinkedList<char> list);

int main()
{
	circularLinkedList<int> list1, list2;
	int num;

	cout << "What kind of list would you like to create?" << endl;
	cout << " # - list of integers \n S - list of strings \n C - list of single characters" << endl;
	cout << "Enter choice: ";
	char listchoice;
	cin >> listchoice;

	if (listchoice == '#') {

		circularLinkedList<int> integerlist, integerlist2;
		int integer;

		cout << "Enter your data, type -999 when done" << endl;
		cin >> integer;

		while (integer != -999)
		{
			integerlist.insertNode(integer);
			cin >> integer;
		}
		cout << "-------------------------------------" << endl;
		cout << "Your list: ";
		integerlist.print();
		cout << endl << "List length: " << integerlist.length() << endl;

		bool repeat = true;
		char repeatresponse = 'Y';

		while (repeat) {
			
			char actionchoice = listactions();
			if (actionchoice == 'D') {
				integerlist2 = integerlist;
				cout << "Original list: ";
				integerlist.print();
				cout << endl;
				cout << "Duplicated as: ";
				integerlist2.print();
				cout << endl;
			}
			integerlist = doactionsInteger(actionchoice, '#', integerlist);
			cout << "-------------------------------------" << endl;
			cout << "Do something else to this list [Y/N]? ";
			cin >> repeatresponse;

			if (repeatresponse != 'Y') {
				repeat = false;
			}			
		}

	}
	else if (listchoice == 'S') {

		circularLinkedList<string> stringlist, stringlist2;
		string stringitem;

		cout << "Enter your data, type DONE when done" << endl;
		cin >> stringitem;

		while (stringitem != "DONE")
		{
			stringlist.insertNode(stringitem);
			cin >> stringitem;
		}
		cout << "-------------------------------------" << endl;
		cout << "Your list: ";
		stringlist.print();
		cout << endl << "List length: " << stringlist.length() << endl;

		bool repeat = true;
		char repeatresponse = 'Y';

		while (repeat) {

			char actionchoice = listactions();
			if (actionchoice == 'D') {
				stringlist2 = stringlist;
				cout << "Original list: ";
				stringlist.print();
				cout << endl;
				cout << "Duplicated as: ";
				stringlist2.print();
				cout << endl;
			}
			stringlist = doactionsString(actionchoice, 'S', stringlist);
			cout << "-------------------------------------" << endl;
			cout << "Do something else to this list [Y/N]? ";
			cin >> repeatresponse;

			if (repeatresponse != 'Y') {
				repeat = false;
			}
		}

	}
	else if (listchoice == 'C') {
		circularLinkedList<char> charlist, charlist2;
		char charitem;

		cout << "Enter your data, type ~ when done" << endl;
		cin >> charitem;

		while (charitem != '~')
		{
			charlist.insertNode(charitem);
			cin >> charitem;
		}
		cout << "-------------------------------------" << endl;
		cout << "Your list: ";
		charlist.print();
		cout << endl << "List length: " << charlist.length() << endl;

		bool repeat = true;
		char repeatresponse = 'Y';

		while (repeat) {

			char actionchoice = listactions();
			if (actionchoice == 'D') {
				charlist2 = charlist;
				cout << "Original list: ";
				charlist.print();
				cout << endl;
				cout << "Duplicated as: ";
				charlist2.print();
				cout << endl;
			}
			charlist  = doactionsChar(actionchoice, 'C', charlist);
			cout << "-------------------------------------" << endl;
			cout << "Do something else to this list [Y/N]? ";
			cin >> repeatresponse;

			if (repeatresponse != 'Y') {
				repeat = false;
			}
		}

	}
	else {
		cout << "Sorry, that isn't a valid type of list" << endl;
	}

}

char listactions() {
	
	char choice;

	cout << "-------------------------------------" << endl;
	cout << "Choose a list behavior: " << endl;
	cout << " [A] Insert new item" << endl;
	cout << " [B] Delete an item" << endl;
	cout << " [C] Check if an item is in the list" << endl;
	cout << " [D] Duplicate this list" << endl;
	cout << "Input choice: ";
	cin >> choice;

	return choice;
}

circularLinkedList<int> doactionsInteger(char choice, char listtype, circularLinkedList<int> list) {

	int manipinteger = 0;

	switch (choice)
	{

	case 'A':
		cout << "Enter the number to be inserted: ";
		cin >> manipinteger;

		list.insertNode(manipinteger);
		cout << "Item inserted. Your list: ";
		list.print();
		cout << endl;
		break;

	case 'B':
		cout << "Enter the number to be deleted: ";
		cin >> manipinteger;

		list.deleteNode(manipinteger);
		cout << "Item deleted. Your list: ";
		list.print();
		cout << endl;
		break;

	case 'C':
		cout << "Enter the number to search for: ";
		cin >> manipinteger;

		if (list.search(manipinteger)) {
			cout << "The item is in the list." << endl;
		}
		else {
			cout << "The item is not in the list." << endl;
		}
		cout << "Your list: ";
		list.print();
		cout << endl;
		break;

	case 'D':
		break;

	default:
		break;
	}

	return list;

}

circularLinkedList<string> doactionsString(char choice, char listtype, circularLinkedList<string> list) {

	string manipstring = "";

	switch (choice)
	{

	case 'A':
		cout << "Enter the string to be inserted: ";
		cin >> manipstring;

		list.insertNode(manipstring);
		cout << "Item inserted. Your list: ";
		list.print();
		cout << endl;
		break;

	case 'B':
		cout << "Enter the string to be deleted: ";
		cin >> manipstring;
		list.deleteNode(manipstring);
		cout << "Item deleted. Your list: ";
		list.print();
		cout << endl;
		break;

	case 'C':
		cout << "Enter the string to search for: ";
		cin >> manipstring;

		if (list.search(manipstring)) {
			cout << "The item is in the list." << endl;
		}
		else {
			cout << "The item is not in the list." << endl;
		}
		cout << "Your list: ";
		list.print();
		cout << endl;
		break;

	case 'D':
		break;

	default:
		break;
	}

	return list;
}

circularLinkedList<char> doactionsChar(char choice, char listtype, circularLinkedList<char> list) {
	
	char manipchar = ' ';

	switch (choice)
	{

	case 'A':
		cout << "Enter the character to be inserted: ";
		cin >> manipchar;

		list.insertNode(manipchar);
		cout << "Item inserted. Your list: ";
		list.print();
		cout << endl;
		break;

	case 'B':
		cout << "Enter the character to be deleted: ";
		cin >> manipchar;
		list.deleteNode(manipchar);
		cout << "Item deleted. Your list: ";
		list.print();
		cout << endl;
		break;

	case 'C':
		cout << "Enter the character to search for: ";
		cin >> manipchar;

		if (list.search(manipchar)) {
			cout << "The item is in the list." << endl;
		}
		else {
			cout << "The item is not in the list." << endl;
		}
		cout << "Your list: ";
		list.print();
		cout << endl;
		break;

	case 'D':
		break;

	default:
		break;
	}

	return list;
}