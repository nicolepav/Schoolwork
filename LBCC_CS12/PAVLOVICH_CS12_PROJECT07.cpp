#include <iostream>
#include "circularlinkedlist.h"

using namespace std;

int main() {

    circularLinkedList<int> circA;
    circularLinkedList<int> circB;


    for(int i = 0; i<10; i++) {
        circA.insertNode(i);
    } 


    cout << endl << "List A: ";
    circA.print();
    cout << endl;

    circA.divideAt(circB, 5);
    
    cout << "Divide List A into A and B at the number 5: " << endl << "A: ";
    circA.print();
    cout << endl << "B: ";
    circB.print();
    cout << endl << endl;

 
}