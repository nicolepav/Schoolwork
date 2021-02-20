// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
#include <iostream>

void InsertionSort(std::vector<int>* numbers, int& comparisons, int& memaccess) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   
   for (i = 1; i < numbers->size(); ++i) {
      j = i;

      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
    
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         comparisons++;
         memaccess += 2;

         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
         --j;

         memaccess += 4;
      }
      if(j>0) {
         comparisons++;
         memaccess += 2;
      }
      
   }
   
   return;
}