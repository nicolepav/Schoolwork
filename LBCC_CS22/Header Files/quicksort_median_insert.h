#ifndef H_QUICKSORTMEDIANINS
#define H_QUICKSORTMEDIANINS

#include <algorithm>

using namespace std;

//  Quick Sort  //
//------------------------------------------------------

// Swap function
template <class elemType>
void swapMedianINS(elemType list[], int first, int second) 
{
    elemType temp;
    temp = list[first]; 
    list[first] = list[second]; 
    list[second] = temp;

} //end swap

// Partition function
template <class elemType>
int partitionMedianINS(elemType list[], int first, int last) 
{
    elemType pivot;
    int index, smallIndex;
    
    swapMedian(list, first, (first + last) / 2);
    
    // determine median
    int a = first;
    int b = last;
    int c = (first + last) / 2;
    int median = max(min(a,b), min(max(a,b),c));

    pivot = median;
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
void recQuickSortMedianINS(elemType list[], int first, int last) 
{
    int pivotLocation;
    if (first < last) 
    {
        pivotLocation = partitionINS(list, first, last); 
        
        // When the size of any sublist reduces to less than 20, sort the sublist using an insertion sort.
        if( pivotLocation-1 - first > 20){
            recQuickSortINS(list, first, pivotLocation - 1); 
        }
        else {
            insertionSort(list, pivotLocation-1 - first, first); 
        }

        if (last - pivotLocation + 1 > 20){
            recQuickSortINS(list, pivotLocation + 1, last);
        }
        else {
            insertionSort(list, last - pivotLocation + 1 , (pivotLocation+1) ); 
        }
    }
} //end recQuickSort


// actual function you call
template <class elemType>
void quickSortMedianINS(elemType list[], int length) 
{
    recQuickSortMedianINS(list, 0, length - 1);
} //end quickSort

#endif




