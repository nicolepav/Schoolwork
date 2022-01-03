#include "rpn.h"
#include <iostream>

using namespace std;

int main() {

	// USER MODIFICTIONS START
	string postfixexpression[] = {"-1", "2", "3", "+", "4", "5", "6", "*", "/", "7", ">", "+", "8", "9", "10", "<", "-", "-", "+", "/", "*"};
	int expressionlength = 21;
	bool optionalOut = true;
	// USER MODIFICATIONS END

	
	double result = rpn(postfixexpression, expressionlength);
	cout << result << endl;
	if(optionalOut) {
		optionalOutput(postfixexpression, expressionlength);
	}
}
