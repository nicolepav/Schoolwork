// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int &comparisons, int &memaccess);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int &comparisons, int &memaccess);
int Partition(std::vector<int>* numbers, int i, int k, int &comparisons, int &memaccess);