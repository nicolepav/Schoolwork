#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "json.hpp"


// Define a node struct to make tree nodes
// all struct data public by default
struct Node {

    // Constructor
    Node(int k);
    
    // Pointers to children
    Node *leftchild;
    Node *rightchild;

    // Data about the node
    int key;
    int height;
    int balancefactor;
};


// Define class to create an AVL tree
class AVLTree {

    public:
        
        // Constructor
        AVLTree();
        
        // Setter and Getter function for root
        Node* getRoot();
        void setRoot(Node* c);

        // Getter function for size variable
        int Size();

        // Define functions for all rotation types
        Node* LLrotation(Node* c);
        Node* RRrotation(Node* c);
        Node* LRrotation(Node* c);
        Node* RLrotation(Node* c);

        // Define insertion function
        Node* Insert(int x, Node* t);

        // Define function to update balance factor
        int nodeBF(Node* n);

        // Define function to update node height
        int nodeHeight(Node* n);

        // Define function for preorder traversal of the tree
        void preorderTraversal(Node* n, int parent, nlohmann::json& jsonObj);
        
        
    private:
    
        // Private data members pointer to the root and size tracker
        Node* root;
        int size;

};


#endif