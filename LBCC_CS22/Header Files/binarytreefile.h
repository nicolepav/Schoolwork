#ifndef BINARYTREEFILE_H
#define BINARYTREEFILE_H

#include "stackfile.h"

using namespace std;

template <class elemType> 
struct nodeType
{
    elemType info; 
    nodeType<elemType> *lLink; 
    nodeType<elemType> *rLink;
};


// Definition of the class
template <class elemType> class binaryTreeType
{
    public:
        const binaryTreeType<elemType>& operator= (const binaryTreeType<elemType>&);
            //Overload the assignment operator.
        bool isEmpty() const;
            //Function to determine whether the binary tree is empty. 
            //Postcondition: Returns true if the binary tree is empty; otherwise, returns false.


        void inorderTraversal() const;
            //Function to do an inorder traversal of the binary tree. 
            //Postcondition: Nodes are printed in inorder sequence.
        void preorderTraversal() const;
            //Function to do a preorder traversal of the binary tree. 
            //Postcondition: Nodes are printed in preorder sequence.
        void postorderTraversal() const;
            //Function to do a postorder traversal of the binary tree. 
            //Postcondition: Nodes are printed in postorder sequence.


        void inorderTraversal(void (*visit) (elemType&)) const; 
            //Function to do an inorder traversal of the binary tree. 
            //The parameter visit, which is a function, specifies the action to be taken at each node.
            //Postcondition: The action specified by the function visit is applied to each node of the
            //               binary tree


        int treeHeight() const;
            //Function to determine the height of a binary tree. 
            //Postcondition: Returns the height of the binary tree.
        int treeNodeCount() const;
            //Function to determine the number of nodes in a binary tree.
            //Postcondition: Returns the number of nodes in the binary tree.
        int singleParent() const;
        int treeLeavesCount() const;
            //Function to determine the number of leaves in abinary tree.
            //Postcondition: Returns the number of leaves in binary tree.
        void destroyTree();
            //Function to destroy the binary tree. 
            //Postcondition: Memory space occupied by each node is deallocated. 
            //root = nullptr;

        virtual bool search(const elemType& searchItem) const = 0; 
            //Function to determine if searchItem is in the binary tree.
            //Postcondition: Returns true if searchItem is found in the binary tree; otherwise, returns false.
        virtual void insert(const elemType& insertItem) = 0; 
            //Function to insert insertItem in the binary tree. 
            //Postcondition: If there is no node in the binary tree that has the same info as insertItem, a
            //               node with the info insertItem is created and inserted in the binary search tree.
        virtual void deleteNode(const elemType& deleteItem) = 0; 
            //Function to delete deleteItem from the binary tree.
            //Postcondition: If a node with the same info as deleteItem is found, it is deleted from the binary tree.
            // If the binary tree is empty or deleteItem is not in the binary tree, an appropriate message is printed.

        binaryTreeType(const binaryTreeType<elemType>& otherTree);  //Copy constructor
        binaryTreeType();                                           //Default constructor
        ~binaryTreeType();                                          //Destructor

    //protected:
        nodeType<elemType> *root;

    private:
        void copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot);
            //Makes a copy of the binary tree to which otherTreeRoot points.
            //Postcondition: The pointer copiedTreeRoot points to the root of the copied binary tree.
        void destroy(nodeType<elemType>* &p);
            //Function to destroy the binary tree to which p points. 
            //Postcondition: Memory space occupied by each node, in the binary tree to which p points, is deallocated.
            //p = nullptr;


        void inorder(nodeType<elemType> *p) const;
            //Function to do an inorder traversal of the binary tree to which p points.
            //Postcondition: Nodes of the binary tree, to which p points, are printed in inorder sequence.
        void preorder(nodeType<elemType> *p) const;
            //Function to do a preorder traversal of the binary tree to which p points.
            //Postcondition: Nodes of the binary tree, to which p points, are printed in preorder sequence.
        void postorder(nodeType<elemType> *p) const;
            //Function to do a postorder traversal of the binary tree to which p points.
            //Postcondition: Nodes of the binary tree, to which p points, are printed in postorder sequence.
        

        void inorder(nodeType<elemType> *p, void (*visit) (elemType&)) const;
            //Function to do an inorder traversal of the binary tree starting at the node specified 
            //by the parameter p. 
            //The parameter visit, which is a function, specifies the action to be taken at each node.
            //Postcondition: The action specified by the function visit is applied to each node of the binary tree
            //               to which p points.


        int height(nodeType<elemType> *p) const;
            //Function to determine the height of the binary tree to which p points.
            //Postcondition: Height of the binary tree to which p points is returned
        int max(int x, int y) const;
            //Function to determine the larger of x and y. 
            //Postcondition: Returns the larger of x and y.
        int nodeCount(nodeType<elemType> *p) const;
            //Function to determine the number of nodes in the binary tree to which p points. 
            //Postcondition: The number of nodes in the binary tree to which p points is returned.
        int leavesCount(nodeType<elemType> *p) const; 
            //Function to determine the number of leaves in the binary tree to which p points. 
            //Postcondition: The number of leaves in the binary tree to which p points is returned.
        int singleParent(nodeType<elemType> *p) const;

        void nonRecursiveInTraversal() const;
        void nonRecursivePreTraversal() const;
};

// Definitions of the functions

template <class elemType> // isEmpty?
bool binaryTreeType<elemType>::isEmpty() const { return (root == nullptr); };

template <class elemType> //constructor
binaryTreeType<elemType>::binaryTreeType() { root = nullptr; };

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const { inorder(root); };

template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const { preorder(root); };

template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const { postorder(root); };

template <class elemType>
int binaryTreeType<elemType>::treeHeight() const { return height(root); };

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const { return nodeCount(root); };

template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const { return leavesCount(root); };


template <class elemType>
void binaryTreeType<elemType>::inorder (nodeType<elemType> *p) const
{
    if (p != nullptr) 
    {
        inorder(p->lLink);
        cout << p->info << " ";
        inorder(p->rLink);
    }
};

template <class elemType>
void binaryTreeType<elemType>::preorder (nodeType<elemType> *p) const
{
    if (p != nullptr) 
    {
        cout << p->info << " ";
        preorder(p->lLink);
        preorder(p->rLink);
    } 
};

template <class elemType>
void binaryTreeType<elemType>::postorder (nodeType<elemType> *p) const
{
    if (p != nullptr) 
    {
        postorder(p->lLink);
        postorder(p->rLink);
        cout << p->info << " ";
    } 
}

template<class elemType>
int binaryTreeType<elemType>::height (nodeType<elemType> *p) const
{
    if (p == nullptr) { return 0; }
    else { return 1 + max(height(p->lLink), height(p->rLink)); }
};

template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const 
{
    if (x >= y) { return x; }
    else { return y; }
}

template<class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType> *p) const
{
   if (p==NULL)
      return 0;
   else
      return 1 + nodeCount(p->lLink) + nodeCount(p->rLink);
}


template<class elemType>
int binaryTreeType<elemType>::leavesCount(nodeType<elemType> *p) const
{
   if (p==NULL)
      return 0;
   else
      if ((p->lLink==NULL)&&(p->rLink==NULL))
         return 1;
      else return ( leavesCount(p->lLink) + leavesCount(p->rLink) );
} 

// ASSIGNMENT: SINGLE PARENT
template<class elemType>
int binaryTreeType<elemType>::singleParent() const
{
   return singleParent(root);
}

template<class elemType>
int binaryTreeType<elemType>::singleParent(nodeType<elemType> *p) const
{
   int start = 0;
   if(p == NULL) {
       return 0;
   } else 
   {
       
       if ( (p->lLink == NULL && p->rLink != NULL) || (p->lLink != NULL && p->rLink == NULL) ) 
       {
           return (1 + singleParent(p->lLink) + singleParent(p->rLink) );
       } else {
           return (0 + singleParent(p->lLink) + singleParent(p->rLink) );
       }
   }
}


template <class elemType>
void binaryTreeType<elemType>::copyTree(nodeType<elemType>* &copiedTreeRoot, nodeType<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr) {
        copiedTreeRoot = nullptr;
    }
    {
        copiedTreeRoot = new nodeType<elemType>; 
        copiedTreeRoot->info = otherTreeRoot->info; 
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink); 
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}; //end copyTree

template <class elemType>
void binaryTreeType<elemType>::destroy(nodeType<elemType>* &p) 
{
    if (p != nullptr) 
    {
        destroy(p->lLink); 
        destroy(p->rLink); 
        delete p;
        p = nullptr;
    } 
};

template <class elemType>
void binaryTreeType<elemType>::destroyTree() { destroy(root); };

//copy constructor
template <class elemType> binaryTreeType<elemType>::binaryTreeType (const binaryTreeType<elemType>& otherTree)
{
    if (otherTree.root == nullptr) { root = nullptr; }     //otherTree is empty 
    else { copyTree(root, otherTree.root); }
};

//Destructor
template <class elemType> binaryTreeType<elemType>:: ~binaryTreeType() { destroy(root); };

//Overload the assignment operator
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
    //avoid self-copy 
    if (this != &otherTree) 
    {
        //if the binary tree is not empty
        if (root != nullptr) { destroy(root); } //destroy the binary tree        
        //otherTree is empty
        if (otherTree.root == nullptr) { root = nullptr; }     
        else { copyTree(root, otherTree.root); }
        
    } //end else 
    
    return *this;
};


// Non recursive travel //


template <class elemType>
void binaryTreeType<elemType>::nonRecursiveInTraversal() const 
{
    stackType<nodeType<elemType>*> stack; 
    nodeType<elemType> *current;
    current = root;

    while ((current != nullptr) || (!stack.isEmptyStack())) 
    {
        if (current != nullptr)
        {
            stack.push(current);
            current = current->lLink;
        }
        else
        {
            current = stack.top();
            stack.pop();
            cout << current->info << " ";
            current = current->rLink;
        }
    }
    
    cout << endl;
}; //end nonRecursiveInTraversal

template <class elemType>
void binaryTreeType<elemType>::nonRecursivePreTraversal() const 
{
    stackType<nodeType<elemType>*> stack; 
    nodeType<elemType> *current;
    current = root;

    while ((current != nullptr) || (!stack.isEmptyStack())) 
    {   
        if (current != nullptr){
            cout << current->info << " ";
            stack.push(current);
            current = current->lLink;
        }
        else
        {
            current = stack.top();
            stack.pop();
            current = current->rLink;
        }
    }
    cout << endl;
}; //end nonRecursivePreTraversal

// We leave it as an exercise for you to write the definition of a C++ function to implement the 
// preceding postorder traversal algorithm. See Programming Exercise 6 at the end of this chapter.


// Overloaded Traversal //

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal(void (*visit) (elemType& item)) const 
{
    inorder(root, *visit);
};

template <class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType>* p,void (*visit) (elemType& item)) const
{
    if (p != nullptr) 
    {
        inorder(p->lLink, *visit);
        
        // makes a call to the function with one reference parameter of type elemType 
        // pointed to by the pointer visit.
        (*visit)(p->info);

        inorder(p->rLink, *visit);
    }

};

#endif