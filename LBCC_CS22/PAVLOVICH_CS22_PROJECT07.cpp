// Pavlovich, Nicole
// CS22 Project 07
// Write a program that outputs the nodes of a graph in a breadth first traversal


#include <iostream>
#include <iomanip>

#include "graphs.h"


int main() {

    graphType G;
    G.createGraph();

    std::cout << "The graph is:" << std::endl;
    G.printGraph();

    std::cout<< "The breadth first nodes are" << std::endl;
    G.breadthFirstTraversal();
    std::cout << std::endl;

    std::cout<< "the depth first nodes are" << std::endl;
    G.depthFirstTraversal();
    std::cout << std::endl;
}
