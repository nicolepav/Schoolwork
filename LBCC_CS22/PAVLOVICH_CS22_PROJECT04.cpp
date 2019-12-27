#include <iostream>
#include <string>
#include <ctime>
#include <random>

#include "insertionsort.h"
#include "quicksort.h"
#include "quicksort_median.h"
#include "quicksort_insert.h"
#include "quicksort_median_insert.h"

using namespace std;

int main()
{
    clock_t x;
    int array[10000] = { 0 };       // create an array of 10 000 elements
    cout << endl;


    // a. Sort the array using pivot as the middle element of the array.
    for (int i = 0; i  < 10000; i++) { array[i] = rand() % 10000; } 
    x = clock();
    quickSort(array, 10000);
    x = clock() - x;
    cout << "PART A: PIVOT AS MIDDLE" << "\t" << x << " ticks" << endl;
    // for (int i = 0; i  < 10000; i++) { cout << array[i] << " "; }


    // b. Sort the array using pivot as the median of the first, last, and middle elements of the array.
    for (int i = 0; i  < 10000; i++) { array[i] = rand() % 10000; }
    x = clock();
    quickSortMedian(array, 10000);
    x = clock() - x;
    cout << "PART B: PIVOT AS MEDIAN" << "\t" << x << " ticks" << endl;
    //for (int i = 0; i  < 10000; i++) { cout << array[i] << " "; }


    // c. Sort the array using pivot as the middle element of the array. However, when the size 
    //    of any sublist reduces to less than 20, sort the sublist using an insertion sort.
    for (int i = 0; i  < 10000; i++) { array[i] = rand() % 10000; }
    x = clock();
    quickSortINS(array, 10000);
    x = clock() - x;
    cout << "PART C: MIDDLE W INSERT" << "\t" << x << " ticks" << endl;
    // for (int i = 0; i  < 10000; i++) { cout << array[i] << " "; }


    // d. Sort the array using pivot as the median of the first, last, and middle elements of the array. 
    //    When the size of any sublist reduces to less than 20, sort the sublist using an insertion sort.
    for (int i = 0; i  < 10000; i++) { array[i] = rand() % 10000; }
    x = clock();
    quickSortMedianINS(array, 10000);
    x = clock() - x;
    cout << "PART D: MEDIAN W INSERT" << "\t" << x << " ticks" << endl;
    //for (int i = 0; i  < 10000; i++) { cout << array[i] << " "; }

    cout << endl;
}