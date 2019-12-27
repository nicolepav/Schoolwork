/*
NAME:			PAVLOVICH, NICOLE [0878228]
CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE
DATE:			09_23_2018
PROGRAM NAME:	PAVLOVICH_72833_PROJECT01.cpp
*/

#include <iostream>;
using namespace std;

int main()
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
	cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
	cout << "DATE:			09_23_2018" << endl;
	cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT01.cpp" << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl;

	int EmployeeID;			// employee ID number
	double HoursWorked;		// amount of hours worked
	double RatePerHour;		// Pay rate per hour
	double GrossSalary;		// Gross salary (dependednt on hours and rate)


	cout << "---------------------------Employee Salary Records---------------------------" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl << endl;

	cout << "------------------------------Employee Details-------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl;

	cout << "Enter your employee ID number:		";			// ask use for their employee ID
	cin >> EmployeeID;										// assign user value to the variable employeeID
	cout << "Enter your hours worked:		";				// ask user for their hours worked
	cin >> HoursWorked;										// assign user value to the variable HoursWorked
	cout << "Enter your rate per hour:		";				// ask user for their rate per hour
	cin >> RatePerHour;										// assign user value to the variable RatePerHour
	cout << endl;

	GrossSalary = HoursWorked * RatePerHour;				// Calculate gross salary


	cout << "--------------------------------Employee Data--------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl;

	cout << "Employee ID#:	" << EmployeeID << endl;		// print employee ID number
	cout << "Hours Worked:	" << HoursWorked << endl;		// print hours worked
	cout << "Rate by Hour:	" << RatePerHour << endl;		// print RatePerHour
	cout << "Gross Salary:	" << GrossSalary << endl;		// Print Gross Salary

	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl;
	
	//system("pause");
}