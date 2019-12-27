// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 6.2: Recursion (Part II)
// A6_3.cpp

// Desciption: This program demonstrates the sorting of an array
// of integers into ascending order using recursion. 

#include <iostream>
using namespace std;

void recursiveSort(int nums[], int low, int size);
int smallestindex(int nums[], int lower, int size);

int main() {

    int numbers[10] = {1, 33, 45, 12, 23, 2, 9, 10, 56, 6};
    int numbersSize = (sizeof(numbers)/sizeof(numbers[0]));
    cout << "Initial Array: ";
    for(int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    recursiveSort(numbers, 0, numbersSize);
    
    cout << "Sorted Array: ";
    for(int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

}






// Recursively sorts an array of integers (nums) into ascending
// order. Requires a starting position low and an array length size
void recursiveSort(int nums[], int low, int size) {
    int temp;
    int location = smallestindex(nums, low, size);

    if (location != size) {
        temp = nums[low];
        nums[low] = nums[location];
        nums[location] = temp;

        recursiveSort(nums, low + 1, size);
    }

}






// A helper function that returns the index of the smallest integer
// in an array of integers, nums. Requires a starting position lower and
// an array length size 
int smallestindex(int nums[], int lower, int size) {
    int location = lower;
    for (int i = lower; i < size; i ++) {
        if(nums[location] > nums[i]) {
            location = i;
        }
    }
    return location;
}


/* Expected Output

Nicole-Pav:A6 nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A6/" 
&& g++ A6_3.cpp -o A6_3 && "/Users/nicolepavlovich/Desktop/CS_Foothill/A6/"A6_3
Initial Array: 1 33 45 12 23 2 9 10 56 6 
Sorted Array: 1 2 6 9 10 12 23 33 45 56 
Nicole-Pav:A6 nicolepavlovich$ 

*/
