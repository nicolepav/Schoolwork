#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    
    // create an index for the new pair
    unsigned int j = ++size_;

    // if the index is larger than the allowed size of loop, do not add to queue
    if(j > max_size_) {
        std::cerr << "The heap is full, value cannot be inserted" << std::endl;
        return;
    }

    // otherwise, add new KVP to loop
    nodes_[j] = kv;

    // Heapify up since new nodes are placed at the bottom
    heapifyUp(j);
}

KeyValuePair PriorityQueue::min() {
    // returns the top of the queue which is always the minimum
    return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {
    
    // if the queue is empty, print an error and return an empty KVP
    if(size_ == 0){
        std::cerr << "Error: Queue is empty" << std::endl;
        return std::make_pair(0, std::make_pair(0,0)); 
    }
    // if the queue has only one item, it is the root already
    else if (size_ == 1) {
        size_--;
        return min();
    }

    // store root node in a temp KVP, then replace node with bottommost leftmost node
    KeyValuePair root = nodes_[1];
    nodes_[1] = nodes_[size_]; 
    size_--;

    // Heapify down the new root which was taken from the end of the queue
    heapifyDown(1);

    // return the original root
    return root;
}

bool PriorityQueue::isEmpty() const {
    // returns true if the size is 0 
    return size_ == 0;
}
	

size_t PriorityQueue::size() const {
	// returns the private size variable of the queue
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {

    // var to determine the location of the parent in a binary heap storage array
    int k = (i)/2; 

    // while node < its parent and not the root
    while (i != 1 && nodes_[i].first < nodes_[k].first) {    
        
        // swap the parent and child 
        std::swap(nodes_[i], nodes_[k]); 
        
        // update location of heapifying node and its parent
        i = k;
        k = (i)/2; 

    }
}

void PriorityQueue::heapifyDown(size_t i) {
	
    // var to determine the location of the child in a binary heap storage array
    unsigned int jR = (2*i) + 1;
    unsigned int jL = (2*i); 
    bool continueswapping = true;

    // If no children, no swaps can be done
    if(jL > size_) {
        continueswapping = false;
    }
  
    // Otherwise
    while (continueswapping) {

        // If there is only a left child, check, swap, and be done
        if (jL == size_) {
            if(nodes_[jL].first < nodes_[i].first){
                std::swap(nodes_[i], nodes_[jL]);
            }
            continueswapping = false;
        }


        // If there is a left and a right child, and at least one of them is less than the parent
        if( (nodes_[i].first > nodes_[jR].first) || (nodes_[i].first > nodes_[jL].first)) {
            
            // swap with right child if right child is smallest
            if(nodes_[jR].first < nodes_[jL].first) {
                std::swap(nodes_[i], nodes_[jR]); 
                i = jR;
            }
            // swap with left child if left child is smallest
            else {
                std::swap(nodes_[i], nodes_[jL]); 
                i = jL;
            }

            // update location of heapifying node and its parent
            jR = (2*i) + 1;
            jL = (2*i);

            // if JL > size, i has no children to swap with
            if(jL > size_) { continueswapping = false; }
        }
        else {
            // there was no need to swap so we are done swapping
            continueswapping = false;
        }

    }

}

void PriorityQueue::removeNode(size_t i) {


    // Method A: Overwrite the node with a value less than the current min, float to top, removeMin
    // -------------------- //
    // if(i == 1){
    //     removeMin();
    //     return;
    // }
    // else {
    //     // Make the element the minimum and then removeMin it
    //     nodes_[i].first = nodes_[1].first - 1;
        
    //     heapifyUp(i);    // since i now has the same value as the smallest element, it will need to go up
    //     removeMin();     // remove one of the duplicate minimums, leaving a copy or the original min and erasing the ith nod

    // }   


    // Method B: Overwrite the node with the bottommost leftmost node and heapify up
    // -------------------- //

    nodes_[i].first = nodes_[size_].first;      // change key
    nodes_[i].second = nodes_[size_].second;    // change value

    size_--;                                    // adjust the size to eliminate access to the moved node


    // Depending on the location of the node, heapify up or down
    if(i == 1) {
        heapifyDown(i);
    }
    else if(nodes_[i].first < nodes_[i/2].first){
        heapifyUp(i);
    }
    else {
        heapifyDown(i);
    }
    

}

Key PriorityQueue::getKey(size_t i) {
    // returns the key of the node at the given position
    return nodes_[i].first;
}
