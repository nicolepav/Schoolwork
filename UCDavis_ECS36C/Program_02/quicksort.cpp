// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"


void QuickSort(std::vector<int>* numbers, int &comparisons, int &memaccess) {
   QuickSortRecurse(numbers, 0, numbers->size() - 1, comparisons, memaccess);
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int &comparisons, int &memaccess) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k, comparisons, memaccess);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j, comparisons, memaccess);
   QuickSortRecurse(numbers, j + 1, k, comparisons, memaccess);
   
   return;
}

int Partition(std::vector<int>* numbers, int i, int k, int &comparisons, int &memaccess) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = (*numbers)[midpoint];
   
   l = i;
   h = k;
   
   memaccess++;

   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while ((*numbers)[l] < pivot) {
         ++l;

         comparisons++;
         memaccess++;
      }
      comparisons++;
      memaccess++;
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < (*numbers)[h]) {
         --h;

         comparisons++;
         memaccess++;
      }
      comparisons++;
      memaccess++;
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = (*numbers)[l];
         (*numbers)[l] = (*numbers)[h];
         (*numbers)[h] = temp;
         
         ++l;
         --h;
         memaccess += 4;
      }
   }
   
   return h;
}