#ifndef H_QUICKSORTMEDIAN
#define H_QUICKSORTMEDIAN

#include <algorithm>

using namespace std;

//  Quick Sort  //
//------------------------------------------------------

// Swap function
template <class elemType>
void swapMedian(elemType list[], int first, int second) 
{
    elemType temp;
    temp = list[first]; 
    list[first] = list[second]; 
    list[second] = temp;

} //end swap

// Partition function
template <class elemType>
int partitionMedian(elemType list[], int first, int last) 
{
    elemType pivot;
    int index, smallIndex;
    
    // determine median
    int a = first;
    int b = last;
    int c = (first + last) / 2;
    int median = max(min(a,b), min(max(a,b),c));

    swapMedian(list, first, median);
    pivot = list[first];
    smallIndex = first;

    
    for (index = first + 1; index <= last; index++) 
    {
        if (list[index] < pivot)
        {
            smallIndex++;
            swapMedian(list, smallIndex, index);
        }
    }

    swapMedian(list, first, smallIndex); 
    return smallIndex;

} //end partition

// Recursive quick sort
template <class elemType>
void recQuickSortMedian(elemType list[], int first, int last) 
{
    int pivotLocation;
    if (first < last) 
    {
        pivotLocation = partitionMedian(list, first, last); 
        recQuickSortMedian(list, first, pivotLocation - 1); 
        recQuickSortMedian(list, pivotLocation + 1, last);
    }
} //end recQuickSort


// actual function you call
template <class elemType>
void quickSortMedian(elemType list[], int length) 
{
    recQuickSortMedian(list, 0, length - 1);
} //end quickSort

#endif




