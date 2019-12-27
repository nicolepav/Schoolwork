#include <iostream>
#include "sequence.h"

using namespace std;
using namespace cs_sequence;

int main() {
	
	// Create the Sequence
	Sequence s;

	// Add items to the sequence (0 - 5)
	for (int i = 0; i < 6; i++) {
		s.insert(i);
	}
	
	// Print the sequence by traversing
	for (s.start(); s.is_item(); s.advance()) {
		cout << s.current() << " ";
	}
	cout << endl;
	
	// Print the size of the sequence
	cout << "This sequence has size: " << s.size() << endl;

}