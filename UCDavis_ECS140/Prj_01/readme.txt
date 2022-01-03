Nicole Pavlovich
ECS 140A
Project 01: Postfix Calculator w Staggered Output


How to run this project:
1. Before compiling, modify the string array "postfixexpression" in rpn.cpp line 9 to contain your postfix expression
    (each entry in the array should be an individual postfix operand or operator)
2. Modify the integer "expressionlength" in line 10 to reflect the length of your postfix expression, 
    counting both operands and operators
3. If you would like to see the postfix expression in staggered output, 
    set the boolean "optionalOutput" on line 11 to true. Otherwise, set it to false
4. Compile rpn.cpp and run in your terminal or IDE with your C++ compiler of choice
    Note: rpn.cpp and rpn.h must be copied to the same directory in order to compile correctly

Output:
Calculation result will print first on a new line by itself
Optional staggered format expression follows if desired

This program catches the following errors:
- division by 0
- 0 exponent 
- too many operands
- too few operands
- unable to find result (usually bad input such as illegal operator)

Encountering an error will cause the program to terminate