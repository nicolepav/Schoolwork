#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

class romanType 
{
	private:
		string romanNumeral;
		int romanValue;

	public:
		void setRomanNumeral(string rNum) { romanNumeral = rNum; };
		string getRomanNumeral() { return romanNumeral; };

		void setRomanValue(int rValue) { romanValue = rValue; };
		int getRomanValue() { return romanValue; };

		void assignDigits(string romNum, int conversionArray[]);

};
void displayArrayValues(int conversionArray[], string romnum);

// MAIN FUNCTION //
int main() {

	// File Header 
	{
		cout << "*****************************************************************************" << endl;
		cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
		cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
		cout << "DATE:			12_12_2018" << endl;
		cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT09.cpp" << endl;
		cout << "*****************************************************************************" << endl << endl << endl;
	}

	// Declare an object to use 
	romanType romanObj;

	// Collect the roman numeral to convert
	string userRomanNumeral;
	char continueconvert = 'Y';

	cout << "Welcome to the Roman Numeral Converter. Enter a numeral between 1 and 3999." << endl << endl;

	do {
		cout << left << setw(35) << "Enter a roman numeral: ";
		cin >> userRomanNumeral;
		romanObj.setRomanNumeral(userRomanNumeral);

		// Make an array to store roman digits
		int conversionArray[15] = { 0 };
		romanObj.assignDigits(romanObj.getRomanNumeral(), conversionArray);


		// Calculate an integer value
		romanObj.setRomanValue(0);
		int numeralLength = romanObj.getRomanNumeral().size();

		for (int i = 0; i < numeralLength; i++) {

			if (conversionArray[i] >= conversionArray[i + 1] && (conversionArray[i + 1] != 0)) {

				// Add the digits if the one to the right is lesser
				romanObj.setRomanValue(romanObj.getRomanValue() + conversionArray[i]);

				// If the next digit is the last digit, also add that
				// Additionally, increment I an extra time to account for calculation being out of sequence
				if (conversionArray[i + 2] == 0) {
					romanObj.setRomanValue(romanObj.getRomanValue() + conversionArray[i + 1]);
					i++;
				}
			}
			else if ((conversionArray[i] <= conversionArray[i + 1]) && (conversionArray[i + 1] != 0)) {

				// Subtract digits if the one to the right is great
				romanObj.setRomanValue(romanObj.getRomanValue() + (conversionArray[i + 1] - conversionArray[i]));

			}
			else if (conversionArray[i + 1] == 0) {

				// If this is the last digit, do nothing
				romanObj.setRomanValue(romanObj.getRomanValue());

			}
		}


		cout << left << setw(35) << "Value of roman numeral: " << romanObj.getRomanValue() << endl;
		cout << left << setw(35) << "Convert another numeral? (Y/N)";

		cin >> continueconvert;
		cout << "-----------------------------------------------------------------------------" << endl;


	} while (continueconvert == 'Y');
}


// FUNCTION DEFINITIONS //
void romanType::assignDigits(string romNum, int conversionArray[]) {

	for (int i = 0; i < romNum.size(); i++) {

		switch (romNum[i])
		{
		case 'M':
			conversionArray[i] = 1000;
			break;
		case 'D':
			conversionArray[i] = 500;
			break;
		case 'C':
			conversionArray[i] = 100;
			break;
		case 'L':
			conversionArray[i] = 50;
			break;
		case 'X':
			conversionArray[i] = 10;
			break;
		case 'V':
			conversionArray[i] = 5;
			break;
		case 'I':
			conversionArray[i] = 1;
			break;
		default:
			conversionArray[i] = 0;
			break;

		}

	}

}

void displayArrayValues(int conversionArray[], string romnum) {

	// Test code for when you want to know what has been assigned to each array slot
	cout << endl << "Conversion Array Values for " << romnum << endl;
	for (int i = 0; i < romnum.size(); i++) {
		cout << conversionArray[i] << " ";
	}
	cout << endl << endl;

}

/*

	d. Test your program using the following Roman numerals: MCXIV,
	CCCLIX, MDCLXVI.

*/