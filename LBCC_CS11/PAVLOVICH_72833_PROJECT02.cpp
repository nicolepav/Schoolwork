/*
NAME:			PAVLOVICH, NICOLE [0878228]
CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE
DATE:			10_02_2018
PROGRAM NAME:	PAVLOVICH_72833_PROJECT02.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "NAME:			PAVLOVICH, NICOLE [0878228]" << endl;
	cout << "CLASS:			78233 CS11 PROF AZIZ LONG BEACH CITY COLLEGE" << endl;
	cout << "DATE:			10_02_2018" << endl;
	cout << "PROGRAM NAME:		PAVLOVICH_72833_PROJECT02.cpp" << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl << endl;

	/*
	> student ID
	> first name
	> last name
	> cs 11
	> cs 12
	> cs 22

	// calculate average and total scores
	// assign a letter grade to each score
		>=90 = A
		>=80 = B
		>=70 = C
		>=60 = D
		<60 = F

	< out: letter grade for student (overall)
	< out: congrats message or warning message
	*/

	int studentID = int();								// Declare studentID (student ID number)
	
	string fname = string(); 							// Declare fname (first name)
	string lname = string();							// Declare lname (last name)
	
	double cs11 = double();								// Declare cs11 (score for class CS11)
	double cs12 = double();								// Declare cs12 (score for class CS12)
	double cs22 = double();								// Declare cs22 (score for class CS22)

	double totalpoints = double();						// Declare totalpoints (total points earned in all classes)
	double gradepercentage = double();					// Declare gradepercentage (percent form grade based on total points)
	char letterGrade = char();							// Declare letterGrade (letter form grade based on total points)


	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "STUDENT GRADING SYSTEM" << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl;

	
	cout << "Student ID#:		";						// ask for student ID number
	cin >> studentID ;
	cout << "First Name:		";						// ask for first name of student
	cin >> fname;
	cout << "Last Name:		";							// ask for last name of student
	cin >> lname;
	cout << "Grade in CS11:		";						// ask for scores for CS11
	cin >> cs11;
	cout << "Grade in CS12:		";						// ask for scores for CS12
	cin >> cs12;
	cout << "Grade in CS22:		";						// ask for score for CS22
	cin >> cs22;

	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Student Results" << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl;

	totalpoints = cs11 + cs12 + cs22;					// calculate total points earned
	gradepercentage = (totalpoints / 300) * (100);		// calculate total grade as a percent

	// Assign a letter grade corresponding to the grade percentage

	if (gradepercentage >= 90)							// If the grade is >= 90, give student an A
	{
		letterGrade = 'A';
	}
		else if (gradepercentage >= 80)					// If it isnt >= 90 but is >= 80, give student a B
		{
			letterGrade = 'B';
		}
			else if (gradepercentage >= 70)				// If it isnt >= 80 but is >= 70, give student a C
			{
				letterGrade = 'C';
			}
				else if (gradepercentage >= 60)			// If it isnt >= 70 but is >= 60, give student a D 
				{
					letterGrade = 'D';
				}										
					else								// If it isnt >= 60, give the the student an F
					{
							letterGrade = 'F';
					}


	// Student Results Printout

	cout << "Student:		" << fname << " " << lname << endl;			// Print student name
	cout << "StudentID:		" << studentID << endl;						// Print student ID
	cout << "Points Earned:		" << totalpoints << "/300" << endl;		// Print total points earned
	cout << "Your Grade:		" << gradepercentage << "%" << endl;	// Print overall grade as a percent
	cout << "Your Grade:		" << letterGrade << endl << endl;		// Print letter grade earned


	if (letterGrade == 'A')												// If letter grade earned is an A, give congrats			
	{
		cout << "Congratulations on your hard work!" << endl;
	}
	
	else if (letterGrade == 'F')										// If letter grade earned is an F, give warning
	{
		cout << "Be careful! You are currently failing computer science" << endl;
	}

	cout << "-----------------------------------------------------------------------------" << endl << endl;

		

}