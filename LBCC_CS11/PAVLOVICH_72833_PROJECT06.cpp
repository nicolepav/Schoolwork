#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void	projectheader(string date, string filename);
void	readzip(int& zipcode);
int		zipsumfunc(int zipnum, int zipsum = 0);
string	encodeDigit(int num);
int		correctiondigitfunc(int zipsum, int correctionDigit);
void	encodeAll(int extractedDigit, int zipEncode, int correctionDigit);

int main() {

	// Print project header
	projectheader("11_13_18","PAVLOVICH_72833_PROJECT06");
	string encodingNeeded = "Y";

	while (encodingNeeded == "Y" || encodingNeeded == "y" || encodingNeeded == "Yes" || encodingNeeded == "yes") {
		
		// Print project begining
		cout << "----CONVERT A ZIPCODE -------------------------------------------------------" << endl;
		cout << "-----------------------------------------------------------------------------" << endl << endl;

		// Ask for zipcode	
		int zipcode = int();
		cout << left << setw(35) << "Enter your zipcode: ";
		readzip(zipcode);
		cout << endl;

		// Relevant Variables
		int zipnum = zipcode;
		int zipsum = int();
		int correctionDigit = int();

		// Create the zipsum	
		zipsum = zipsumfunc(zipnum, zipsum);

		// Calculate the correction Digit
		correctionDigit = correctiondigitfunc(zipsum, correctionDigit);

		// Encode All Digits 
		int extractedDigit = int();
		int zipEncode = zipcode;
		encodeAll(extractedDigit, zipEncode, correctionDigit);
		cout << endl << endl;

		// Print final details
		cout << left << setw(35) << "The zipcoded entered was " << zipcode << endl;
		cout << left << setw(35) << "The zipsum is " << zipsum << endl;
		cout << left << setw(35) << "The correction digit was " << correctionDigit << endl;;
		cout << "-----------------------------------------------------------------------------" << endl;

		// Ask to repeat process
		cout << endl << endl;
		cout << "*****************************************************************************" << endl;
		cout << "Do you need to encode another zipcode (Y/N):	";
		cin >> encodingNeeded;
		cout << "*****************************************************************************" << endl;
		cout << endl << endl << endl;
	}

	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "No more zipcodes will be encoded. Thank you.";
	cout << endl;
}

void projectheader(string date, string filename) {

	cout << "*****************************************************************************" << endl;
	cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
	cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
	cout << "DATE:			" << date << endl;
	cout << "PROGRAM NAME:		" << filename << ".cpp" << endl;
	cout << "*****************************************************************************" << endl << endl << endl;

}

void readzip(int& zipcode) {
	cin >> zipcode;
}

int zipsumfunc(int zipnum, int zipsum) {
	
	do
	{
		zipsum = zipsum + zipnum % 10;		// extract the last digit and add it to sum
		zipnum = zipnum / 10;				// remove the last digit
	} while (zipnum > 0);					// do until there are no numbers left

	return zipsum;
}

string encodeDigit(int num) {	// use a char instead an int?

	string codedDigit;
	switch (num) {

	case 0:
		codedDigit = "||:::";	// 11000
		break;
	case 1:
		codedDigit = ":::||";	// 00011
		break;
	case 2:
		codedDigit = "::|:|";	// 00101
		break;
	case 3:
		codedDigit = "::||:";	// 00110
		break;
	case 4:
		codedDigit = ":|::|";	// 01001
		break;
	case 5:
		codedDigit = ":|:|:";	// 01010
		break;
	case 6:
		codedDigit = ":||::";	// 01100
		break;
	case 7:
		codedDigit = "|:::|";	// 10001
		break;
	case 8:
		codedDigit = "|::|:";	// 10010
		break;
	case 9:
		codedDigit = "|:|::";	// 10100
		break;
	default:
		codedDigit = "Input Error";
		break;
	}

	return codedDigit;

}

int correctiondigitfunc(int zipsum, int correctionDigit) {
	
	if ((zipsum % 10) == 0) {
		correctionDigit = 0;
	}
	else {
		correctionDigit = 10 - (zipsum % 10);
	}

	return correctionDigit;

}

void encodeAll(int extractedDigit, int zipEncode, int correctionDigit) {
	
	cout << left << setw(35) << "The barcode for this zipcode is " << "|";		// Open barcode frame

	do
	{
		extractedDigit = zipEncode % 10;										// extract the last digit
		cout << encodeDigit(extractedDigit);

		zipEncode = zipEncode / 10;												// remove the last digit
	} while (zipEncode > 0);													// do until there are no more digits

	cout << encodeDigit(correctionDigit);
	cout << "|" << endl;														// close barcode

}