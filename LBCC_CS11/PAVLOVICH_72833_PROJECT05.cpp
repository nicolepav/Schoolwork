/*
NAME:			PAVLOVICH, NICOLE [0878228]
CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE
DATE:			11_06_2018
PROGRAM NAME:	PAVLOVICH_72833_PROJECT05.cpp
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <string>	

using namespace std;

int main() {

	// ------------------------------------------------------------------------------ //
	// SPECIAL NOTE: THIS PROGRAM OUTPUTS TO BOTH THE CONSOLE AND TO THE OUTDATA FILE //
	// ------------------------------------------------------------------------------ //

	// File Header 
	{
	cout << "*****************************************************************************" << endl;
	cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
	cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
	cout << "DATE:			11_06_2018" << endl;
	cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT05.cpp" << endl;
	cout << "*****************************************************************************" << endl << endl << endl;
	}

	// Declare Necessary Variables
	string item = string();			// name of inventory item
	double units = double();		// amount of item in inventory
	double cost = double();			// price of the item

	double value = double();		// value of the inventory for a specific item
	double totalvalue = double();	// value of the inventory for the whole store

	// Open Inventory Import/Export Files
	ifstream inData;
	inData.open("PAVLOVICH_72833_PROJECT05_INPUT.txt");
	ofstream outData;
	outData.open("PAVLOVICH_72833_PROJECT05_OUTPUT.txt");


	// Formatting for output
	char ch = '_';														// character for a horizontal line
	
	// --------------------------------------- Console ------------------------------------------------ //
	// Draw Top Line
	for (int i = 0; i < 100; i++) {
		cout << ch;
	}

	// Header Text
	cout << endl;
	cout << right << setfill(' ') << setw(70) << "INVENTORY REPORT FOR PAVLOVICH PROJECT 05" << endl;

	// Draw Bottom Line
	for (int i = 0; i < 100; i++) {
		cout << ch;
	}

	// Subheader Text
	cout << endl;
	cout << left << setfill(' ') << setw(25) << "Item";
	cout << left << setfill(' ') << setw(26) << "Units";
	cout << left << setfill(' ') << setw(20) << "Cost ($)";
	cout << right << setfill(' ') << setw(29) << "Inventory Value ($)" << endl;

	// Draw Divider Line
	for (int i = 0; i < 100; i++) {
		cout << ch;
	}
	cout << endl;

	// ----------------------------------------- File ------------------------------------------------- //
	// Draw Top Line
	for (int i = 0; i < 100; i++) {										
		outData << ch;
	}
	
	// Header Text
	outData << endl;													
	outData << right << setfill(' ') << setw(70) << "INVENTORY REPORT FOR PAVLOVICH PROJECT 05" << endl;

	// Draw Bottom Line
	for (int i = 0; i < 100; i++) {										
		outData << ch;
	}
	
	// Subheading text
	outData << endl;													
	outData << left << setfill(' ') << setw(25) << "Item";
	outData << left << setfill(' ') << setw(26) << "Units";
	outData << left << setfill(' ') << setw(20) << "Cost ($)";
	outData << right << setfill(' ') << setw(29) << "Inventory Value ($)" << endl;

	// Draw Divider Line
	for (int i = 0; i < 100; i++) {										
		outData << ch;
	}
	outData << endl;





	// ---------------------------------- Collect/Release Data ----------------------------------------- //
	
	// While the end of the file has not been reached, execute data collecton
	while (!inData.eof()) {

		// Gather Data
		inData >> item >> units >> cost;
		
		// Calculate item inventory value and total inventory value
		value = units * cost;
		totalvalue = totalvalue + value;

		// Report Data to Console
		cout << fixed << setprecision(0);
		cout << left	<< setfill(' ') << setw(25) << item;
		cout << right	<< setfill(' ') << setw(5) << units;

		cout << fixed << setprecision(2);
		cout << right	<< setfill(' ') << setw(29) << setprecision(2) << cost;
		cout << right	<< setfill(' ') << setw(41) << value << endl;

		// Report Data to outData file
		outData << fixed << setprecision(0);
		outData << left << setfill(' ') << setw(25) << item;
		outData << right << setfill(' ') << setw(5) << units;

		outData << fixed << setprecision(2);
		outData << right << setfill(' ') << setw(29) << setprecision(2) << cost;
		outData << right << setfill(' ') << setw(41) << value << endl;

	}

	// ------------------------------ Final Output (Console & File) ------------------------------------- //
	// Draw end of report line
	for (int i = 0; i < 100; i++) {	
		cout << ch;
	}
	for (int i = 0; i < 100; i++) {
		outData << ch;
	}

	// Display total inventory and formatting (console)
	cout << endl;
	cout << fixed << setprecision(2);
	cout << left  << setfill(' ') << setw(20) << "Inventory Total ($)";
	cout << right << setfill(' ') << setw(80) << totalvalue << endl << endl;

	// Display total inventory and formatting (file)
	outData << endl;
	outData << fixed << setprecision(2);
	outData << left << setfill(' ') << setw(20) << "Inventory Total ($)";
	outData << right << setfill(' ') << setw(80) << totalvalue << endl << endl;

}