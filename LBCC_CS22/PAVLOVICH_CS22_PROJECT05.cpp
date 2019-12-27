#include <iostream>
#include "binarysearchtree.h" // file created from book model

using namespace std;

int main() {

    // Function singleparent() is a member of binaryTreeType, of which binarySearchTree is a subtype
    bSearchTreeType<int> testerTree;
    int num;

    cout << endl <<  "Enter a list numbers where the final number is -999." << endl;
    cin >> num;

    while (num != -999)
    {
        testerTree.insert(num);
        cin >> num;
    }

    cout << endl << "This tree has " << testerTree.singleParent() << " single parent nodes." << endl;

}

