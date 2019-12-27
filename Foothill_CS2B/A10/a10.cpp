#include <iostream>
#include "sequence.h"

using namespace std;
using namespace cs_sequence;

void printSequence(Sequence s);

int main() {
	
	// Create the Sequence
	Sequence s;

	// Add items to the sequence (0 - 5)
	for (int i = 0; i < 6; i++) {
		s.insert(i);
	}

    // Print the sequence by traversing
	printSequence(s);
	
	// Print the size of the sequence
	cout << "This sequence has size: " << s.size() << endl;


}


void printSequence(Sequence s) {
    // Print the sequence by traversing
	for (s.start(); s.is_item(); s.advance()) {
		cout << s.current() << " ";
	}
	cout << endl;
}