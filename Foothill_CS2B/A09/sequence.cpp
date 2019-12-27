// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 9.1: Linked Lists Part I
// sequence.cpp, sequence.h

// Description: This program implements a non templated linked list

// No documentation required for this project

#include "sequence.h"

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
    }
            
    // Postcondition: A new copy of entry has been inserted in the Sequence before the 
    // current item. If there was no current item, then the new entry has been inserted at the 
    // front. In either case, the new item is now the current item of the Sequence.
    void Sequence::insert(const value_type& entry) {
        
        // define a new node of the node struct type
        node* new_node = new node;
        new_node->data = entry;
        numitems++;
        
        // if the cursor is at the front and the list is not empty
        if (cursor == headPtr || cursor == nullptr) { 
            // the new node points to the old front
            // precursor remains nullptr 
            new_node->next = headPtr;                 
            // the headPtr points to the new node
            headPtr = new_node;
            
            // if this is the only item in the list
            if (numitems == 1) {
                // tail also points to the new node
                tailPtr = new_node;
            }
        // if the list is not empty or cursor not at front
        // inserting anywhere else
        } else {                                       
            // tailPtr, headPtr and precursor don't change.
            // the cursor is at the node after this one
            new_node->next = cursor;                   
            // the precursor points to this node
            precursor->next = new_node;
        }
        
        // the cursor is at this node
        cursor = new_node;
    } 
}
    