// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 9.1: Linked Lists Part I
// sequence.cpp, sequence.h

// Description: This program implements a non templated linked list

// No documentation required for this project


#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>

typedef int value_type;
typedef int size_type;

namespace cs_sequence {
    class Sequence {

    private:
        // numItems. Stores the number of items in the Sequence.
        size_type numitems;

        // In other words, there should not be a node class; rather, a node struct should 
        // be defined inside the Sequence class.
        struct node {
            value_type data;
            node* next;
        };

        node* headPtr;
        node* tailPtr;

        node* cursor;
        node* precursor;


    public:
        Sequence();
            // postcondition: The Sequence has been initialized to an empty Sequence.
            
        void start();
            // postcondition: The first item in the Sequence becomes the current item (but if the 
            // Sequence is empty, then there is no current item).
            
        void advance();
            // precondition: is_item() returns true
            // Postcondition: If the current item was already the last item in the Sequence, then there 
            // is no longer any current item. Otherwise, the new current item is the item immediately after 
            // the original current item.
            
        void insert(const value_type& entry);
            // Postcondition: A new copy of entry has been inserted in the Sequence before the 
            // current item. If there was no current item, then the new entry has been inserted at the 
            // front. In either case, the new item is now the current item of the Sequence.
            
        void attach(const value_type& entry);
            // Not required this week
            // Postcondition: A new copy of entry has been inserted in the Sequence after the current 
            // item. If there was no current item, then the new entry has been attached to the end of 
            // the Sequence. In either case, the new item is now the current item of the Sequence.
            
        void remove_current();
            // Not required this week
            // Precondition: is_item returns true. 
            // Postcondition: The current item has been removed from the Sequence.  If the item removed 
            // was the last item in the Sequence, then there is now no current item.  Otherwise, the item
            // that was after the removed item is now the current item.
             
        size_type size() const;
            // Postcondition: Returns the number of items in the Sequence.
            
        bool is_item() const;
            // Postcondition: A true return value indicates that there is a valid "current" item that
            // may be retrieved by the current member function (listed below). A false return value
            // indicates that there is no valid current item.
            
        value_type current() const;
            // Precondition: is_item() returns true
            // Postcondition: The current item in the Sequence is returned.

    };
}

#include "sequence.cpp"

#endif