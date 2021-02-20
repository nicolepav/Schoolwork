#include <iostream>
#include <math.h>
#include "AVL.h"

// Constructor for Node struct
// Sets all data fields to 0 (NULL for pointers) 
// Sets key to provided value
Node::Node(int k){
    key = k;
    leftchild = NULL;
    rightchild = NULL;
    height = 0;
    balancefactor = 0;
}

// Constructor for AVL Tree class instance
// Sets root and size to NULL and 0 respectively
AVLTree::AVLTree() {
    root = NULL;
    size = 0;
}

// Getter function for the root
Node* AVLTree::getRoot(){ return root; };

// Setter function for the root
void AVLTree::setRoot(Node* c){ root = c; };

// Getter function for the size
int AVLTree::Size(){ return size; };

// Left-Left Solution for Right-Right imbalance
// For BF(c) > 1 and BF(b) > 0
Node* AVLTree::LLrotation(Node* c){
    
    // Create outside pointers so that original nodes are not lost
    Node *p;
    Node *tp;
    p = c;
    tp = p->rightchild;

    // Rotate
    p->rightchild = tp->leftchild;
    tp->leftchild = p;
    
    // Update the height of the new parent & children after rotation 
    tp->leftchild->height = nodeHeight(tp->leftchild);
    tp->rightchild->height = nodeHeight(tp->rightchild);
    tp->height = nodeHeight(tp);

    // Update the BF of the new parent & children after rotation 
    tp->balancefactor = nodeBF(tp);
    tp->leftchild->balancefactor = nodeBF(tp->leftchild);
    tp->rightchild->balancefactor = nodeBF(tp->rightchild);

    // return the new parent node 
    return tp; 
}

// Right-Right Rotation for Left-Left imbalance
// For BF(c) < -1 and BF(b) < 0
Node* AVLTree::RRrotation(Node* c){

    // Create outside pointers so that original nodes are not lost
    Node *p;                        
    Node *tp;                       
    p = c;                          
    tp = p->leftchild;              

    // Rotate
    p->leftchild = tp->rightchild;  
    tp->rightchild = p;  

    // Update the height of the new parent & children after rotation
    tp->leftchild->height = nodeHeight(tp->leftchild);
    tp->rightchild->height = nodeHeight(tp->rightchild);
    tp->height = nodeHeight(tp);

    // Update the BF of the new parent & children after rotation
    tp->balancefactor = nodeBF(tp); 
    tp->leftchild->balancefactor = nodeBF(tp->leftchild);
    tp->rightchild->balancefactor = nodeBF(tp->rightchild);          

    // return the new parent node
    return tp; 
}

// Left-Right Rotation for Right-Left imbalance
// For BF(c) > 1 and BF(b) < 0
Node* AVLTree::LRrotation(Node* c){

    // Create outside pointers so that original nodes are not lost
    Node *p;
    Node *tp;
    Node *tp2;
    p = c;
    tp = p->rightchild;
    tp2 =p->rightchild->leftchild;

    // Rotate and update height 
    p->rightchild = tp2->leftchild;
    p->height = nodeHeight(p);

    // Rotate and update height 
    tp->leftchild = tp2->rightchild;
    tp->height = nodeHeight(tp);

    // Final rearrangement and height update
    tp2->leftchild = p;
    tp2->rightchild = tp; 
    tp2->height = nodeHeight(tp2);

    // Update the new parent node and children BF
    tp2->leftchild->balancefactor = nodeBF(tp2->leftchild);
    tp2->rightchild->balancefactor = nodeBF(tp2->rightchild);
    tp2->balancefactor = nodeBF(tp2);

    // Return new parent
    return tp2; 

}

// Right-Left Solution for Left-Right imbalance
// For BF(c) < -1 and BF(b) > 0
Node* AVLTree::RLrotation(Node* c){
    
    // Create outside pointers so that original nodes are not lost
    Node *p;
    Node *tp;
    Node *tp2;
    p = c;
    tp = p->leftchild;
    tp2 =p->leftchild->rightchild;

    // Rotate and update height 
    p->leftchild = tp2->rightchild;
    p->height = nodeHeight(p);
    
    // Rotate and update height
    tp->rightchild = tp2->leftchild;
    tp->height = nodeHeight(tp);

    // Final rearrangement and height update
    tp2->rightchild = p;
    tp2->leftchild = tp; 
    tp2->height = nodeHeight(tp2);
    
    // Update the new parent node and children BF
    tp2->leftchild->balancefactor = nodeBF(tp2->leftchild);
    tp2->rightchild->balancefactor = nodeBF(tp2->rightchild);
    tp2->balancefactor = nodeBF(tp2);

    // Return new parent
    return tp2; 
}


// Insertion function for adding a new node to the tree
// Implemented recursively
Node* AVLTree::Insert(int x, Node* t) {
    

    // Base case: node traversed to is empty
    // Make a new node and put it in this empty spot
    if(t == NULL){
        
        // Define a new node and place it in t
        Node *newnode = new Node(x);
        t = newnode;
        t->leftchild = t->rightchild = NULL;
        t->height = 0;
        
        // Increment size and return up
        size++;
        return(t);
    }

    // Case 2: x > current node key
    // Traverse tree to the right by making a recursive call
    else if (x > t->key) {
        t->rightchild = Insert(x, t->rightchild);
    }

    // Case 3: x < current node
    // Traverse tree to the left by making a recursive call
    else if( x < t->key) {
        t->leftchild = Insert(x, t->leftchild);
    }

    // Case 4: Node is already in tree
    // Stop traversing and no insertion necessary, duplicates not permitted in BST
    else {
        return t;
    }


    // Update the height of t
    // Update the balance factor of t
    t->height = nodeHeight(t);
    t->balancefactor =  nodeBF(t);

    // Perform rotations if needed
    
    // Right Right imbalance
    if(t->balancefactor > 1 && t->rightchild->balancefactor > 0){
        return LLrotation(t);
    }

    // Left Left imbalance
    if(t->balancefactor < -1 && t->leftchild->balancefactor < 0){
        return RRrotation(t);
    }

    // Right Left imbalance
    if(t->balancefactor > 1 && t->rightchild->balancefactor < 0){
        return LRrotation(t);
    }

    // Left Right imbalance
    if(t->balancefactor < -1 && t->leftchild->balancefactor > 0){
        return RLrotation(t);
    }


    // No corrections needed, return up
    return t;
}


// Define function to update balance factor of a given node
int AVLTree::nodeBF(Node* n) {

    // If both children exist, use formula BF = R - L
    if(n->leftchild && n->rightchild) {
        return (n->rightchild->height - n->leftchild->height);
    }

    // If no children exist, the node is perfectly balanced
    else if(n->rightchild == NULL && n->leftchild == NULL){
        return 0;
    }

    // If the left child does not exist, use -1 for its portion of the formula
    else if(n->rightchild && n->leftchild == NULL){
        return (n->rightchild->height - (-1));
    }

    // If the right child does not exist, use -1 for its portion of the formula
    else if(n->leftchild && n->rightchild == NULL){
        return ((-1) - n->leftchild->height);
    }

    // If you get here, print an error
    else {
        std::cerr << "Something went wrong calculating the balance factor" << std::endl;
        return 0;
    }
    
}

// Define function to update node height 
int AVLTree::nodeHeight(Node* n){

    // If both children are null, leaf has height 0
    if(n->leftchild == NULL && n->rightchild == NULL) {
        n->balancefactor = 0;
        return 0;
    }
    // If left is null, height is based on right only
    else if(n->leftchild == NULL){
        return n->rightchild->height + 1;
    }
    // If right is null, height is based on left only
    else if(n->rightchild == NULL) {
        return n->leftchild->height + 1;
    }

    // If none of the children are null, pick maximum of the children's heights
    return std::max(n->leftchild->height, n->rightchild->height) + 1;

}


// Preorder traversal (give root to n)
void AVLTree::preorderTraversal(Node* n, int parent, nlohmann::json& jsonObj) {
    
    // If the node given doesnt exist, return
    if(n == NULL) { return; }

    // Create string to store key so JSON doesn't freak out
    std::string string_key = std::to_string(n->key);
    
    // Put balance factor and height into the node's JSON data
    jsonObj[string_key]["balance factor"] = n->balancefactor;
    jsonObj[string_key]["height"] = n->height;
    
    // If the left child exists, add the left child to the node's JSON data
    if(n->leftchild != NULL) {
        jsonObj[string_key]["left"] = n->leftchild->key;
    }

    // If the right child exists, add the right child to the node's JSON data
    if (n->rightchild != NULL) {
        jsonObj[string_key]["right"] = n->rightchild->key;
    }
    

    // If the node is the same as its parent, then it is the root
    // Since this case only happens once, assign height and root data here
    if(n->key == parent) {
        jsonObj[string_key]["root"] = true;
        jsonObj["height"] = n->height;
        jsonObj["root"] = n->key;
    }
    // If it is not the root, add the node's parent field to the JSON data
    else{
        jsonObj[string_key]["parent"] = parent;
    }
    
    // Execute recursive calls on the left and right children of this node
    preorderTraversal(n->leftchild, n->key, jsonObj);
    preorderTraversal(n->rightchild, n->key, jsonObj);
}