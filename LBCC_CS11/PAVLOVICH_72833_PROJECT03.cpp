/*
NAME:			PAVLOVICH, NICOLE [0878228]
CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE
DATE:			10_04_2018
PROGRAM NAME:	PAVLOVICH_72833_PROJECT03.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main()
{	

	//	File Header 
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
	cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
	cout << "DATE:			10_04_2018" << endl;
	cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT03.cpp" << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl << endl;

	// Variables
	string employeeName = string();
	double grossPay = double();

	// Get Data From User	
	cout << "Enter your full name:	";				
	getline(cin, employeeName);
	cout << "Enter your gross pay:	$";
	cin >> grossPay;
	cout << endl << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl << endl;

	// Define Necessary Variables
	const double FEDTAX = 15.0 / 100;
	const double STATETAX = 3.50 / 100;
	const double SSNTAX = 5.75 / 100;
	const double MEDICARETAX = 2.75 / 100;
	const double PENSION = 5.00 / 100;
	const double HEALTHFEE = 75.00;

	const double TOTALTAX = FEDTAX + STATETAX + SSNTAX + MEDICARETAX + PENSION;
	double netPay = grossPay - ((grossPay)*(TOTALTAX)) - HEALTHFEE;

	// Print Data to Console
	cout << right;
	cout << fixed << showpoint << setprecision(2);

	cout << left << setfill(' ') << setw(15) << "Employee Name: "	<< employeeName << endl;
	cout << left << setfill('.') << setw(15) << "Gross Pay: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << grossPay << endl;
	cout << left << setfill('.') << setw(15) << "Federal Tax: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << FEDTAX * grossPay << endl;
	cout << left << setfill('.') << setw(15) << "State Tax: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << STATETAX * grossPay << endl;
	cout << left << setfill('.') << setw(15) << "SSN Tax: "			<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << SSNTAX * grossPay << endl;
	cout << left << setfill('.') << setw(15) << "Medicare Tax: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << MEDICARETAX * grossPay << endl;
	cout << left << setfill('.') << setw(15) << "Pension Tax: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << PENSION * grossPay << endl;
	cout << left << setfill('.') << setw(15) << "Health Fee: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << HEALTHFEE << endl;
	cout << left << setfill('.') << setw(15) << "Net Pay: "			<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << netPay << endl;

	cout << endl << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl << endl;

	// Create Output File
	ofstream outData;
	outData.open("outData.txt");

	outData << right;
	outData << fixed << showpoint << setprecision(2);

	outData << "--------------------------------------------------------------" << endl;
	outData << "Employee Salary Record" << endl;
	outData << "--------------------------------------------------------------" << endl << endl;

	outData << setfill(' ') << setw(15) << "Employee Name: "		<< employeeName << endl;
	outData << left << setfill('.') << setw(15) << "Gross Pay: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << grossPay << endl;
	outData << left << setfill('.') << setw(15) << "Federal Tax: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << FEDTAX * grossPay << endl;
	outData << left << setfill('.') << setw(15) << "State Tax: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << STATETAX * grossPay << endl;
	outData << left << setfill('.') << setw(15) << "SSN Tax: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << SSNTAX * grossPay << endl;
	outData << left << setfill('.') << setw(15) << "Medicare Tax: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << MEDICARETAX * grossPay << endl;
	outData << left << setfill('.') << setw(15) << "Pension Tax: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << PENSION * grossPay << endl;
	outData << left << setfill('.') << setw(15) << "Health Fee: "	<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << HEALTHFEE << endl;
	outData << left << setfill('.') << setw(15) << "Net Pay: "		<< right << setfill('.') << setw(40) << "$" << setfill(' ') << setw(7) << netPay << endl;
	
	outData << endl << "--------------------------------------------------------------" << endl;

	outData.close();

	}