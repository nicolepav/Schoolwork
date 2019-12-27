// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 3.1: Pointers & Dynamic Memory (Due Ocotober 14 2019)
// a3_2.cpp
// Program allows the user to report player names and scores for a 
// ficticious game, then prints the info by score in descending order

#include <iostream>
#include <string>
using namespace std;


void initializeArrays(string names[], int scores[], int size);
void sortData(string names[], int scores[], int size);
void displayData(const string names[], const int scores[], int size);

int main() {

	int numOfPlayers;
	
	cout << "How many scores will you enter?: ";
	cin >> numOfPlayers;

	string* names = new string[numOfPlayers];
	int* scores = new int[numOfPlayers];

	initializeArrays(names, scores, numOfPlayers);
	sortData(names, scores, numOfPlayers);
	displayData(names, scores, numOfPlayers);

}






// Allows you to initialize an array of names and array of scores of a given size
void initializeArrays(string names[], int scores[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "Enter the name for score #" << i + 1 << ": ";
		cin >> names[i];
		cout << "Enter the score for score #" << i + 1 << ": ";
		cin >> scores[i];
	}
}






// Sorts data in two parallel arrays based on the integer array using bubblesort
void sortData(string names[], int scores[], int size) {

	int tempscore;
	string tempname;

	for (int j = 0; j < size - 1; j++) {		
		for (int i = 0; i < size; i++) {
			
			if (scores[i] < scores[i + 1]) {
				
				tempscore = scores[i];
				scores[i] = scores[i + 1];
				scores[i + 1] = tempscore;

				tempname = names[i];
				names[i] = names[i + 1];
				names[i + 1] = tempname;
			}
		}
	}
}






// Prints the contents of the name and scores arrays to the console
void displayData(const string names[], const int scores[], int size) {
	cout << endl << "Top Scorers:" << endl;
	for (int i = 0; i < size; i++) {
		cout << names[i] << ": " << scores[i] << endl;
	}
}





/* Program Output

How many scores will you enter?: 4
Enter the name for score #1: Suzy
Enter the score for score #1: 600
Enter the name for score #2: Kim
Enter the score for score #2: 9900
Enter the name for score #3: Armando
Enter the score for score #3: 8000
Enter the name for score #4: Tim
Enter the score for score #4: 514

Top Scorers:
Kim: 9900
Armando: 8000
Suzy: 600
Tim: 514

*/