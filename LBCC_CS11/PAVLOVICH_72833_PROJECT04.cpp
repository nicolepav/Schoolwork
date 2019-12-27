/*
NAME:			PAVLOVICH, NICOLE [0878228]
CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE
DATE:			10_21_2018
PROGRAM NAME:	PAVLOVICH_72833_PROJECT04.cpp
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <string>	

using namespace std;

int main() {

	// File Header 
	cout << "*****************************************************************************" << endl;
	cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
	cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
	cout << "DATE:			10_21_2018" << endl;
	cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT04.cpp" << endl;
	cout << "*****************************************************************************" << endl << endl << endl;

	// Variables
	double A = double();
	double B = double();
	double C = double();
	double numofsolut = double();

	// Program Header
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "Quardratic Equation Solver" << endl;
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	// Main Program
	cout << endl;
	cout << right << setfill(' ') << setw(40) << "Enter A, B, and C where Ax^2 + Bx + C : " << left;
	
	cin >> A >> B >> C;														// Accept user values for A B and C
	double discrim = (B * B) - (4 * A * C);									// calculate the discrim

	if (A != 0)																// if A does not equal zero, attempt to calculate
	{

		if (discrim < 0)													// if the discrim is negative the solutions are imaginary
		{

			// Print Imaginary Solutions Message //
			cout << right << setfill(' ') << setw(40) << "Your values give this quadratic: " << A << "x^2 + " << B << "x + " << C << " " << endl;
			cout << endl;
			cout << right << setfill(' ') << setw(40) << "The discriminant is: " << scientific << discrim << endl;

			cout << right << setfill(' ') << setw(40) << "The two imaginary solutions are: " << scientific << ((-1 * B) / (2 * A)) << " + (" << ((sqrt(abs(discrim))) / (2 * A)) << ")i" << endl;
			cout << right << setfill(' ') << setw(40) << " "								 << scientific << ((-1 * B) / (2 * A)) << " - (" << ((sqrt(abs(discrim))) / (2 * A)) << ")i" << endl;

		}

		else if (discrim >= 0)												// if the discrim is greater than or equal to zero
		{

			double pos_solution = ((-1 * B) + sqrt(discrim)) / (2 * A);		// calculate solution using -B + discrim
			double neg_solution = ((-1 * B) - sqrt(discrim)) / (2 * A);		// calculate solution using -B - discrim

			if (discrim == 0)												// check if it equals zero exactly, then change respective variables
			{
				numofsolut = 1;
			}
			else if (discrim > 0)											// check if it is positive, then change the respective variables
			{
				numofsolut = 2;
			}

			// Print Real Solutions Message //

			cout << right << setfill(' ') << setw(40) << "Your values give this quadratic: " << A << "x^2 + " << B << "x + " << C << " " << endl;
			cout << endl;
			cout << right << setfill(' ') << setw(40) << "The discriminant is: " << scientific << discrim << endl;

			if (numofsolut > 1)											// for two solutions, use plural language
			{
				cout << right << setfill(' ') << setw(40) << "The two real solutions are: " << scientific << pos_solution << endl;
				cout << right << setfill(' ') << setw(40) << " "							<< scientific << neg_solution << endl;
			}
			else															// for one solution, use singular lanaguage
			{
				cout << right << setfill(' ') << setw(40) << "The one real solution is: "	<< scientific << pos_solution << endl;
			}
			
		}
	}
	else																	// if A is equal to zero, do npt attempt to calculate a solution
	{
		cout << endl;
		cout << "::ERROR::" << endl;
		cout << "A must not equal zero. Rerun program and choose a valid value. " << endl;

	}

	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

}