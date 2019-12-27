// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 10: Linked Lists Part II
// sequence.cpp, sequence.h

// Description: This program implements a non templated linked list

// No documentation required for this project

#include "sequence.h"
using namespace std;

namespace cs_sequence {
    
    // postcondition: The Sequence has been initialized to an empty Sequence.
    Sequence::Sequence() {
        headPtr = nullptr;
        tailPtr = nullptr;
        precursor = nullptr;
        cursor = nullptr;
        numitems = 0;
    }

    // postcondition: The first item in the Sequence becomes the current item (but if the 
    // Sequence is empty, then there is no current item).
    void Sequence::start() {
        cursor = headPtr;
        precursor = nullptr;
    }
            
    // precondition: is_item() returns true
    // Postcondition: If the current item was already the last item in the Sequence, then there 
    // is no longer any current item. Otherwise, the new current item is the item immediately after 
    // the original current item.
    void Sequence::advance() {
        if (is_item()) {
            if (cursor == tailPtr) {
                cursor = nullptr;
            }
            else {
                precursor = cursor;
                cursor = cursor->next;
            }
        }
    }
           
    // Postcondition: Returns the number of items in the Sequence.
    size_type Sequence::size() const { return numitems; }
            
    // Postcondition: A true return value indicates that there is a valid "current" item that
    // may be retrieved by the current member function (listed below). A false return value
    // indicates that there is no valid current item.
    bool Sequence::is_item() const {
        return (cursor != nullptr);
    }
            
    // Precondition: is_item() returns true
    // Postcondition: The current item in the Sequence is returned.
    value_type Sequence::current() const {
        if (is_item()) {
            return cursor->data;
        }
        return 0;
    }
            
    // Postcondition: A new copy of entry has been inserted in the Sequence before the 
    // current item. If there was no current item, then the new entry has been inserted at the 
    // front. In either case, the new item is now the current item of the Sequence.
    void Sequence::insert(const value_type& entry) {
        
        node* new_node = new node;
        new_node->data = entry;
        numitems++;
        
        if (cursor == headPtr || cursor == nullptr) { 

            new_node->next = headPtr;                 
            headPtr = new_node;
            
            if (numitems == 1) {
                tailPtr = new_node;
            }
        } else {                                       
            new_node->next = cursor;                   
            precursor->next = new_node;
        }
        cursor = new_node;
    } 

    // Postcondition: A new copy of entry has been inserted in the Sequence after the current 
    // item. If there was no current item, then the new entry has been attached to the end of 
    // the Sequence. In either case, the new item is now the current item of the Sequence.
    void Sequence::attach(const value_type& entry) {

        // (1) attaching to an empty list
        if (!is_item()) {
            insert(entry);
            numitems = 1;
        }
        // (2) attaching at the end of a list with at least one item,
        else if (cursor == tailPtr) {
            
            // create the node
            node* new_node = new node;
            new_node->data = entry;
            new_node->next = nullptr;


            // make the current node point to it

            cursor->next = new_node;

            // advance all the other trackers 1 node
            precursor = cursor;
            cursor = new_node;
            tailPtr = new_node;
            
            numitems++;
        
        } 
        // (3) attaching anywhere else. 
        else {
            
            node* temp = cursor->next;

            // create the node
            node* new_node = new node;
            new_node->data = entry;

            // make the current node point to it
            cursor->next = new_node;

            // make it point to the next node
            new_node->next = temp;

            this->advance();
            numitems++;

        }

    }


    // Precondition: is_item returns true. 
    // Postcondition: The current item has been removed from the Sequence.  If the item removed 
    // was the last item in the Sequence, then there is now no current item.  Otherwise, the item
    // that was after the removed item is now the current item.
    // void Sequence::remove_current() {
    //     if (is_item()) {

    //         node* temp;
    //         temp = cursor;
            
    //         if (cursor == headPtr && cursor == tailPtr) {
    //             cursor = nullptr;
    //             precursor = nullptr;
    //             headPtr = nullptr;
    //             tailPtr = nullptr;
    //         }
    //         else if (cursor == headPtr) {
    //             headPtr = cursor->next;
    //             cursor = headPtr;
    //             precursor = nullptr;
    //         }
    //         else {
    //             if (cursor == tailPtr) {
    //                 tailPtr = precursor;
    //                 precursor = nullptr;
    //                 cursor = nullptr;
    //             } 
    //             else {      
    //                 precursor->next = cursor->next;
    //                 cursor = cursor->next;
                    
    //             }     
    //         }
    //         delete temp;
    //         numitems--;	
    //     }
    // }


    void Sequence::remove_current() {
        if (is_item()) {

            node* temp;
            temp = cursor;

            if (cursor == headPtr && cursor == tailPtr) {
                cursor = nullptr;
                precursor = nullptr;
                headPtr = nullptr;
                tailPtr = nullptr;
            }
            else if (cursor == headPtr) {
                headPtr = cursor->next;
                cursor = headPtr;
                precursor = nullptr;
            }
            else {
                if (cursor == tailPtr) {
                    precursor->next = nullptr;
                    tailPtr = precursor;
                    cursor = precursor;
                    if (precursor == headPtr) {
                        precursor = nullptr;
                    }
                    else {
                        for(precursor = headPtr; precursor->next->next; precursor = precursor->next);
                    }
                }
                else {      
                    precursor->next = cursor->next;
                    cursor = cursor->next;

                }    
            }
            delete temp;
            numitems--;
        }
    }

    //post: a Sequence object is created and initialized to "copyMe".
    void Sequence::copy(const Sequence& copyMe) {

        numitems = 0;

        if (copyMe.headPtr == nullptr) {
            cursor = precursor = headPtr = tailPtr = nullptr;
        }
        else {

            // allocate a new node for the new sequence
            node* newPtr = new node;
            newPtr -> data = copyMe.headPtr -> data;
            numitems++;

            // start the new sequence with this node
            headPtr = newPtr;
            precursor = nullptr;
            cursor = headPtr;
            tailPtr = headPtr;

            // create a node to traverse the origin sequence
            node* originPtr = copyMe.headPtr -> next;

            while (originPtr != nullptr) {
                
                // add node to the new list, make it the current, & assign data
                newPtr->next = new node;
                newPtr = newPtr->next;
                newPtr->data = originPtr->data;
                numitems++;
                
            
                // Correct cursor and precursor positions
                if(originPtr == copyMe.cursor) {
                    this->cursor = newPtr;
                }
                if (originPtr == copyMe.precursor) {
                    this->precursor = newPtr;
                }
                originPtr = originPtr->next;

                // if (originPtr != nullptr) {
                //     cout << "newPtr is: " << newPtr << " and originPtr is: " << originPtr << endl;
                // }
                // else {
                //     cout << "NULL" << endl;
                // }
                

                // if the thing being copied is the last thing, make it tailptr    
                if (originPtr == nullptr) {
                    
                    // tailPtr = newPtr->next;
                    tailPtr = newPtr;
                    cout << "tail assigned is: " << tailPtr->data<< endl;
                    
                    newPtr->next = nullptr;
                    originPtr = nullptr;
                }         
            }     
        }
    }


    // post: the sequence is destroyed without memory leaks
    void Sequence::clear() {
        node* temp = headPtr;
       
        while (temp != nullptr) {
            node* del = temp;
            temp = temp->next;
            delete del;
        }
        headPtr = tailPtr = nullptr;

    }
    
    
    //post: a Sequence object is created and initialized to "copyMe".
    Sequence::Sequence(const Sequence& copyMe) {
        copy(copyMe);
    }

    // post: A copy of "right" is stored in the calling object.
    Sequence Sequence::operator=(const Sequence& right) {
        this->clear();
        copy(right);
        return *this;
    }

    // post: the sequence is destoryed without memory leaks
    Sequence::~Sequence() {
        clear();
    }
   
}
    