// Pavlovich, Nicole
// CS 12 Professor Aziz Project 05
// Project accepts data from a file regarding stocks, outputs alphabetized data and total to new file

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "stockType.h"

using namespace std;
void alphabetizeStocks(stockType stockObjects[], int size);

int main() {

    ifstream infile;
    infile.open("stock_data_file.txt");

    ofstream outfile;
    outfile.open("stock_results.txt");

    stockType stockObjects[5];

    string sym;
    double o, c, h, l, p, n;

    for (int i = 0; i < 5; i++){
        infile >> stockObjects[i];  // overloaded operator
    }

    // sort the stocks alphabetically
    alphabetizeStocks(stockObjects, 5);
    

    outfile << left << setw(6) << "NAME" << right << setw(10) << "SHARES" << setw(10) << "OPENING" << setw(10) << "CLOSING";
    outfile << setw(10) << "HIGH" << setw(10) << "LOW" << setw(10) << "PREV" << setw(10) << "%CHANGE";
    outfile << endl << endl;
    
    for (int i = 0; i < 5; i++){
        outfile << stockObjects[i];
    }

    outfile << endl;

    double closingassets;
    for (int i = 0; i < 5; i++){
        closingassets = closingassets + (stockObjects[i].getclosingprice()*stockObjects[i].getnumofshares());
    }

    outfile << "Closing Assets: $" << closingassets << endl;


}

void alphabetizeStocks(stockType stockObjects[], int size) {
    
    // modified bubblesort for alphabetizing
    stockType temp;
    for (int i = 0 ; i < size-1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (stockObjects[j] > stockObjects[j+1]) {
                
                //swap
                temp = stockObjects[j];                         // store the bigger in temp 
                stockObjects[j] = stockObjects[j+1];            // put the smaller in the big's location
                stockObjects[j+1] = temp;                       // put the larger item in the next spot over                   
            }
        }
    }
};

