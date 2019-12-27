/**
 * Nicole Pavlovich
 * CS 22 Project 02
 * 03/31/19
 * Updated 4/7/19 
 * Program accepts a number as a string and uses stacks to convert it to a double
**/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

#include "stackfile.h" // stack file from textbook

using namespace std;

int main(){

    string numericalstring = " ";
    cout << endl << "Enter an integer or decimal number with two decimal places: ";
    cin >> numericalstring;

    stackType<char> charStack;
    stackType<double> digitStack;
    
    bool isdecimal = true;
    int powerstart = 0;
    int powercounter = 0;
    double conversionInt = 0;


    // import chars to the stack
    for (int i = 0; i < numericalstring.size(); i++)
    {
        charStack.push(numericalstring[i]);

        // identify type of string
        if (numericalstring[i] == '.') 
        {
            isdecimal = true;
            powerstart = -2;
        }
    }

    // convert to double and add to digitStack
    while (!charStack.isEmptyStack())
    {
        switch (charStack.top())
        {
            case '0':
                conversionInt = 0;
                break;

            case '1':
                conversionInt = 1;
                break;

            case '2':
                conversionInt = 2;
                break;

            case '3':
                conversionInt = 3;
                break;
            case '4':
                conversionInt = 4;
                break;

            case '5':
                conversionInt = 5;
                break;
            case '6':
                conversionInt = 6;
                break;

            case '7':
                conversionInt = 7;
                break;

            case '8':
                conversionInt = 8;
                break;

            case '9':
                conversionInt = 9;
                break;
            
            case '.':
                conversionInt = 0;
                powercounter--;
                break;

            default:
                break;
        }
        
        // multiply the int by the appropriate place holder
        conversionInt = conversionInt * pow(10, (powerstart + powercounter));
        powercounter++;

        // clean up charStack and place the int in the digitStack
        charStack.pop();
        digitStack.push(conversionInt);
    }

    // Add everything up
    double convertednumber = 0.0;
    while(!digitStack.isEmptyStack())
    {
        convertednumber = convertednumber + digitStack.top();
        digitStack.pop();
    }

    cout << fixed << setprecision(2);
    cout << "The number in double form is: " << convertednumber << endl << endl;

}