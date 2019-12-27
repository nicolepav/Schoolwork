// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 3.1: Pointers & Dynamic Memory (Due Ocotober 14 2019)
// a3_1.cpp
// Program uses the properties of pointers to manipulate data and variables



/*
 Type your code after each of the commented instructions below (except that the statements
 for instructions 11 and 21 should be written where the instructions indicate).  I have
 written the first statement for you.
*/

#include <iostream>
using namespace std;


void noNegatives(int *x);
void swap(int* x, int* y);


int main() {
	
	// 1. Create two integer variables named x and y.
	int x, y;

	// 2. Create an int pointer named p1.
	int* p1;

	// 3. Store the address of x in p1.
	p1 = &x;

	// 4. Use only p1 (not x) to set the value of x to 99.
	*p1 = 99;

	// 5. Using cout and x (not p1), display the value of x.
	cout << "# 5:\tx contains: " << x << endl;

	// 6. Using cout and the pointer p1 (not x), display the value of x.
	cout << "# 6:\tx contains: " << *p1 << endl;

	// 7. Store the address of y into p1.
	p1 = &y;

	// 8. Use only p1 (not y) to set the value of y to -300.
	*p1 = -300;

	// 9. Create two new variables: an int named temp, and an int pointer named p2. Make p2
	//    point to x.
	int temp;
	int* p2 = &x;

	// 10. Use only temp, p1, and p2 (not x or y) to swap the values in x and y. (This will take
	//     a few statements.   Don't use a swap function.)
	temp = *p2;
	*p2 = *p1;
	*p1 = temp;


	// 11. Write a function with the following signature: void noNegatives(int *x). The function
	//     should accept the address of an int variable. If the value of this integer is
	//     negative then it should set it to zero.
	//     Place the prototype for this function above the main function, and the definition
	//     below main().
	// 12. Invoke the function twice: once with the address of x as the argument, and once with
	//     the address of y.  Use x or y for the argument (not p1 or p2).
	noNegatives(&x);
	noNegatives(&y);

	// 13. Use p2 to display the values in x and y (this will require both assignment statements
	//     and cout statements).  You can use x and y in assignment statements, but not in your
	//     cout statement. This should produce the output
	//
	//     x is: 0
	//     y is: 99
	cout << "#13:\tx is: " << *p2;
	p2 = &y;
	cout << " and y is: " << *p2 << endl;


	// 14. Create an int array named 'a' with two elements. Make p2 point to the first element
	//     of a.
	int a[2];
	p2 = a;

	// 15. Use only p2 and x (not a) to initialize the first element of a with the value of x.
	p2[0] = x;

	// 16. Use only p2 and y (not a) to initialize the second element of a with the value of y.
	//     Leave p2 pointing to the first element of a. Don't use pointer arithmetic.
	//     Hint: don't forget that pointers and arrays are the same thing.
	p2[1] = y;

	// 17. Using cout and p2 only, display the address of the first element in a.
	cout << "#17:\tThe address of the first element is " << &p2[0] << endl;

	// 18. Using cout and p2 only, display the address of the second element in a. Leave p2
	//     pointing to the first element of a.   Don't use pointer arithmetic.
	cout << "#18:\tThe address of the second element is " << &p2[1] << endl;

	// 19. Use p1, p2, and temp to swap the values in the two elements of array 'a'.
	//     (first point p1 at a[0], then point p2 at a[1], then do not use "a" again. After this
	//     the swapping steps should look very similar to step 10. Don't use a swap function.)
	p1 = &a[0];
	p2 = &a[1];

	temp = *p2;
	*p2 = *p1;
	*p1 = temp;

	// 20. Display the values of the two elements.
	//     (The first element should be 99, the second 0).
	cout << "#20:\tThe first element in a[] is " << a[0];
	cout << " and the second element in a[] is " << a[1] << endl;

	// 21. Write a function named 'swap' that accepts two pointers to integers as arguments, and
	//     then swaps the contents of the two integers. Do not use any reference parameters.
	//     Place the function prototype for swap() above the main() function, and place the
	//     definition of swap() below main().
	// 22. Invoke your swap() function with the addresses of x and y (using the address-of
	//     operator in the arguments), then print their values.  (x should be 99, y should be 0).
	swap(&x, &y);
	cout << "#22:\tNow, x contains: " << x << " and y contains: " << y << endl;

	// 23. Invoke your swap function with the address of the two elements in array 'a', then
	//     print their values.  (a[0] should be 0, a[1] should be 99).
	swap(&a[0], &a[1]);
	cout << "#23:\tNow, a[0] contains: " << a[0] << "and a[1] contains: " << a[1] << endl;

}  /* end of function main() */






void noNegatives(int *x) {
	if (*x < 0) {
		*x = 0;
	}
}






void swap(int* x, int* y) {
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}






/* Program Output

# 5:    x contains: 99
# 6:    x contains: 99
#13:    x is: 0 and y is: 99
#17:    The address of the first element is 00EFF96C
#18:    The address of the second element is 00EFF970
#20:    The first element in a[] is 99 and the second element in a[] is 0
#22:    Now, x contains: 99 and y contains: 0
#23:    Now, a[0] contains: 0and a[1] contains: 99

*/