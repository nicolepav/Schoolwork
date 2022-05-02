#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>

using namespace std;

void getSingleOperand(stack<float> &operands, float storage[]);
void getOperands(stack<float> &operands, float storage[]);
float convertFloat(string floatstring);
double rpn(string &strs, int n);
void optionalOutput(string *strs, int n);




double rpn(string *strs, int n) {
	std::stack<float> operands;	
	string str = "";
	float storage[2] = {0.0, 0.0};


	for(int i = 0; i < n; i++){		
		str = strs[i];

		if (str == "+") {
			getOperands(operands, storage);
			operands.push(storage[0] + storage[1]);
		}
		else if (str == "-"){
			getOperands(operands, storage);
			operands.push(storage[0] - storage[1]);
		}
		else if (str == "*"){
			getOperands(operands, storage);
			operands.push(storage[0] * storage[1]);
		}
		else if (str == "/"){
			getOperands(operands, storage);
			if ( storage[1] ==  0) {
				std::cerr << "Error: Division by 0" << endl;
				exit(1);
			}
			operands.push(storage[0] / storage[1]);
		}
		else if (str == "**"){
			getOperands(operands, storage);
			if( storage[1] == 0) {
				std::cerr << "Error: 0 Exponent" << endl;
				exit(1);
			}
			operands.push(pow(storage[0], storage[1]));
		}
		else if (str == "<"){
			getSingleOperand(operands, storage);
			operands.push(floor(storage[0]));
		}
		else if (str == ">"){
			getSingleOperand(operands, storage);
			operands.push(ceil(storage[0]));
		}
		else {
			try
			{
				operands.push(convertFloat(str));
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				std::cerr << "Error: Bad input" << endl;
			}
			
			
		}

	}

	double result = 0.0;
	if(!operands.empty()) {
		result = operands.top();
		operands.pop();
		if(!operands.empty()) {
			std::cerr << "Too many operands provided" << std::endl;
			exit(1);
		}
		else {
			return result;
		}
	}
	else {
		std::cerr << "Error: No Result" << std::endl;
		exit(1);
	}

}

float convertFloat(string floatstring) {
	float temp = ::atof(floatstring.c_str());
	return temp;
}

void getOperands(stack<float> &operands, float storage[]) {
	if(!operands.empty()) {
		storage[1] = operands.top();
		operands.pop();

		if(!operands.empty()) {
			storage[0] = operands.top();
			operands.pop();
		}
		else {
			std::cerr << "Not enough operands" << std::endl;
			exit(1);
		}
	}
	else {
		std::cerr << "Not enough operands" << std::endl;
		exit(1);
	}		
}

void getSingleOperand(stack<float> &operands, float storage[]) {
		if(!operands.empty()) {
		storage[0] = operands.top();
		operands.pop();
		storage[1] = 0.0;
	}
	else {
		std::cerr << "Not enough operands" << std::endl;
		exit(1);
	}	
}

void optionalOutput(string *strs, int n) {


	vector<string> collection;
	string left = "", right = "", op = "", push = "";

	// push all string items into a vector
	for(int i = 0; i < n; i++){
		collection.push_back(strs[i]);
	}

	// iterate through vector, replacing items as operators are encountered
	for(int i = 0; i < collection.size(); i++){

		if(collection[i] == "+" || collection[i] == "-" || collection[i] == "*" || collection[i] == "/" || collection[i] == "**" ) {
			// if operator requires two operands
			left = collection[i-2];
			right = collection[i-1];
			op = collection[i];
		
			// create one string
			push = "(" + op + left + " " + right + ")";
			collection[i] = push;

			// erase used operands
			collection.erase(collection.begin()+i-2, collection.begin()+i);

			// go back to beginning of loop
			i = 0;
		}
		else if(collection[i] == "<" || collection[i] == ">") {
			// if operator requires one operand
			left = collection[i-1];
			op = collection[i];

			// create string, replace and erase, restart
			push = "(" + op + left + ")";
			collection[i] = push;
			collection.erase(collection.begin() + i - 1);
			i = 0;
		}
	}

	// convert single string to tabbed format
	int numtabs = 0;
	char current = ' ';
	

	for(int i = 0; i < collection[0].length(); i++) {
		
		current = collection[0][i];
		if(i == 0) {
			cout << collection[0][i] << collection[0][i+1] << "\n";
			numtabs++;
			i++;
		}
		else {

			if(current == '(') {
				for(int j = 0; j < numtabs; j++) {
					cout << "\t";
				}	
				cout << collection[0][i] << collection[0][i+1] << "\n";
				numtabs++;
				i++;
			}
			else if (current == ' ') {
				// skip
			}
			else if(current == ')') {
				numtabs--;
				cout << "\n";
				for(int j = 0; j < numtabs; j++) {
					cout << "\t";
				}
				cout << ")\n";	
			}
			else {
				for(int j = 0; j < numtabs; j++) {
					cout << "\t";
				}
				cout << collection[0][i];
				while (collection[0][i+1] != ' ' && collection[0][i+1] != ')') {
					cout << collection[0][i+1];
					i++;
				}
				if(collection[0][i+1] == ' ') {
					cout << "\n";
				}				
			}
		}
		
	}
	cout << endl;
}
