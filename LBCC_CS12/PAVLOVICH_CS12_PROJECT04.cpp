// Accepts DOB in MM-DD-YYYY format and outputs in Month Day, Year format
// If the user enters an out of range month or day an exception is thrown
// By: Nicole Pavlovich CS 12

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string convertINTtoSTRING(int inINT, int &dayMax);

struct invalidMonth : public exception{};
struct invalidDay : public exception{};

int main() 
{
    int month = 0, day = 0, year = 0, dayMax = 0;
    bool isLeapYear = false, validInput = true;
    
    char dash = ' ';
    string monthname = " ";

    try
    {
        cout << endl;
        cout << "Enter date of birth in MM-DD-YYYY format: ";
        cin >> month >> dash >> day >> dash >> year; 
        monthname = convertINTtoSTRING(month, dayMax); // will throw invalidMonth as necessary
        
        if ( year % 4 == 0) 
        {
            isLeapYear = true;        
        }
        
        if (day > dayMax || day < 0)
        {
            throw invalidDay();
        }
        if (month == 2 && day == 29 && !isLeapYear)
        {
            throw invalidDay();
        }
    }
    catch(invalidMonth)
    {
        cout << "You have entered an invalid month" << endl;
        validInput = false;
    }
    catch(invalidDay)
    {
        cout << "You have entered an invalid day" << endl;
        validInput = false;
    }
    
    if (validInput)
    {
        cout << "Your birthday is " << monthname << " " << day << ", " << year << endl;
        cout << endl;   
    }
}

// Converts the given month to month name
// throws InvalidMonth() if there is no matching month
string convertINTtoSTRING(int inINT, int &dayMax)
{
    string month;
    switch (inINT)
    {
        case 1:
            month = "January";
            dayMax = 31;
            break;
        case 2:
            month = "February";
            dayMax = 29;
            break;
        case 3:
            month = "March";
            dayMax = 31;
            break;
        case 4:
            month = "April";
            dayMax = 30;
            break;
        case 5:
            month = "May";
            dayMax = 31;
            break;
        case 6:
            month = "June";
            dayMax = 30;
            break;
        case 7:
            month = "July";
            dayMax = 31;
            break;
        case 8:
            month = "August";
            dayMax = 31;
            break;
        case 9:
            month = "September";
            dayMax = 30;
            break;
        case 10:
            month = "October";
            dayMax = 31;
            break;
        case 11:
            month = "November";
            dayMax = 30;
            break;
        case 12:
            month = "December";
            dayMax = 31;
            break;
        default:
            throw invalidMonth();
            dayMax = 31;
            break;
    }

    return month;
}
