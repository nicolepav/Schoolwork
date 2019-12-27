#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

/*Write a program that allows the user to enter the last names of five candidates in
a local election and the number of votes received by each candidate. The
program should then output each candidate’s name, the number of votes
received, and the percentage of the total votes received by the candidate. Your
program should also output the winner of the election*/

/*
let the user search something
sort by name or total votes
*/

void bubbleSortCanidates(string lastNames[5], double canidateVotes[5], double percentVotes[5], int arraySize);

int main() {

	system("cls");
	// File Header 
	{
		cout << "*****************************************************************************" << endl;
		cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
		cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
		cout << "DATE:			11_30_2018" << endl;
		cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT07.cpp" << endl;
		cout << "*****************************************************************************" << endl << endl << endl;
	}

	// Declare necessary variables
	string lastNames[5] = { "" };
	double canidateVotes[5] = { 0.0 };
	double percentVotes[5] = { 0.0 };
	double totalVotes = 0.0;

	// Declare file manipulation variables
	ifstream VoterData;
	VoterData.open("VoterData.txt");
	ofstream VoterResults;
	VoterResults.open("VoterResults.txt");


	// Take canidate data input
	for (int i = 0; i < 5; i++) {
		VoterData >> lastNames[i];
		VoterData >> canidateVotes[i];
	}

	// Calculate total amount of votes
	for (int j = 0; j < 5; j++) {
		totalVotes = totalVotes + canidateVotes[j];
	}

	// Calculate percent votes per canidate
	for (int i = 0; i < 5; i++) {		
		percentVotes[i] = (canidateVotes[i] / totalVotes ) * 100;
	}

	cout << "_____________________________________________________________________________" << endl << endl;
	cout << "COUNTY ELECTION RESULTS" << endl;
	cout << "_____________________________________________________________________________" << endl << endl;
	bubbleSortCanidates(lastNames, canidateVotes, percentVotes, 5);
	cout << "_____________________________________________________________________________";

	if (percentVotes[4] < 50) {
		cout << endl << endl << lastNames[4] << " gathered " << percentVotes[4] << "% of the votes." << endl;
		cout << "This canidate did not reach a majority. A runoff election should be held." << endl;
		cout << "_____________________________________________________________________________";
	}
	else {
		cout << endl << "The winner of the election is " << lastNames[4] << " with " << percentVotes[4] << "% of the votes." << endl;
		cout << "_____________________________________________________________________________";
	}
	cout << endl << endl;

}

// Bubble Sort Function (modified from teacher demo)
void bubbleSortCanidates(string lastNames[5], double canidateVotes[5], double percentVotes[5], int arraySize)
{
	double tempVotes = 0.0;
	double tempPercent = 0.0;
	string tempName = "";

	for (int i = 1; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize - i; j++)
		{
			if (canidateVotes[j] > canidateVotes[j + 1])	// compare the two neighbors 
			{
				tempVotes = canidateVotes[j];
				tempPercent = percentVotes[j];
				tempName = lastNames[j];

				lastNames[j] = lastNames[j + 1];			// swap the last names
				lastNames[j + 1] = tempName;

				percentVotes[j] = percentVotes[j + 1];		// swap the percent votes
				percentVotes[j + 1] = tempPercent;

				canidateVotes[j] = canidateVotes[j + 1];	// swap the canidate votes      
				canidateVotes[j + 1] = tempVotes;

			}
		}
	}

	// Print final results
	int p[5] = { 4, 3, 2, 1, 0 };					// static values for print order

	for (int k = 0; k < 5; k++) {
		
		cout << left << setw(20) << lastNames[p[k]];
		cout << fixed << setprecision(0) << left << setw(10) << canidateVotes[p[k]];
		cout << fixed << setprecision(2) << right << setw(10) << percentVotes[p[k]] << " % " << endl;
	}

}