// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<int>* numbers,  int &comparisons, int &memaccess) { 
   MergeSortRecurse(numbers, 0, numbers->size() - 1, comparisons, memaccess);
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k,  int &comparisons, int &memaccess) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j,  comparisons, memaccess);
      MergeSortRecurse(numbers, j + 1, k, comparisons, memaccess);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, comparisons, memaccess);
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k,  int &comparisons, int &memaccess) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++leftPos;

         memaccess += 2;
         
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         ++rightPos;

         memaccess += 2;
         
      }
      ++mergePos;
      
      comparisons++;
      memaccess += 2;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;

      memaccess += 2;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;

      memaccess += 2;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      
      memaccess +=2;

   }
}