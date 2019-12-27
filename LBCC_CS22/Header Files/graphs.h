#ifndef GRAPHS_H
#define GRAPHS_H

#include <fstream>
#include <iostream>
#include <cfloat>
#include <iomanip>

#include <list>
#include <queue>


class graphType {
    public:
        std::list<int> *graph; //array to create adjacency lists

        bool isEmpty() const;
            //Function to determine whether the graph is empty. 
            //Postcondition: Returns true if the graph is empty; otherwise, returns false.
        void createGraph();
            //Function to create a graph.
            //Postcondition: The graph is created using the adjacency list representation.
        void clearGraph();
            //Function to clear graph.
            //Postcondition: The memory occupied by each vertex s deallocated.
        void printGraph() const;
            //Function to print graph. 
            //Postcondition: The graph is printed.
        void depthFirstTraversal();
            //Function to perform the depth first traversal of the entire graph.
            //Postcondition: The vertices of the graph are printed 
            // using depth first traversal algorithm.
        void dftAtVertex(int vertex);
            //Function to perform the depth first traversal of
            //the graph at a
            //Postcondition: node specified by the parameter vertex. Starting at vertex, the vertices 
            // are printed using depth first traversal algorithm.
        void breadthFirstTraversal();
            //Function to perform the breadth first traversal of the entire graph.
            //Postcondition: The vertices of the graph are printed
            // using breadth first traversal algorithm.
        graphType(int size = 0);
            //Constructor
            //Postcondition: gSize = 0; maxSize = size; graph is an array of pointers to linked lists.
            
    protected:
        int maxSize; //maximum number of vertices
        int gSize; //current number of vertices 

    private:
        void dft(int v, bool visited[]);
            //Function to perform the depth first traversal of the graph at a node specified by the parameter vertex. 
            //This function is used by the public member functions depthFirstTraversal and dftAtVertex.
            //Postcondition: Starting at vertex, the vertices are printed using depth first traversal
};

bool graphType::isEmpty() const { return (gSize == 0); }

void graphType::createGraph() {
    std::ifstream infile; 
    std::string fileName;
    int index;
    int vertex;
    int adjacentVertex;

    if (gSize != 0) { clearGraph(); } //if the graph is not empty, make it empty
    
    std::cout << "Enter input file name: ";
    std::cin >> fileName;
    std::cout << std::endl;
    infile.open(fileName);
    
    if (!infile) {
        std::cout << "Cannot open input file." << std::endl;
        return; 
    }
    
    infile >> gSize; //get the number of vertices
    
    graph =  new std::list<int>[gSize];
    

    for (index = 0; index < gSize; index++) {
        
        infile >> vertex;
        infile >> adjacentVertex;
        
        while (adjacentVertex != -999) {
            graph[vertex].push_back(adjacentVertex);
            infile >> adjacentVertex;
        } 

    }

    infile.close();
}


void graphType::printGraph() const {
    int index;
    for (index = 0; index < gSize; index++) {
        std::cout << index << " "; 
        
        for (auto v : graph[index]){
            std::cout << v << " ";
        }
        
        std::cout << std::endl;
    }
    std::cout << std::endl;
} 

graphType::graphType(int size) {
    maxSize = size;
    gSize = 0;
    graph = new std::list<int>[size];
}

void graphType::dft(int v, bool visited[]) {
    
    visited[v] = true;
    std::cout << " "<< v << " ";             //visitthevertex
    std::list<int>::iterator graphIt;
    
    //for each vertex adjacent to v
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt; 
        if (!visited[w])
            dft(w, visited);
    }
}

void graphType::depthFirstTraversal() {
    
    bool *visited; //pointer to create the array to keep track of the visited vertices
    visited = new bool[gSize];

    int index;
   
    for (index = 0; index < gSize; index++) 
        visited[index] = false;
    
    //For each vertex that is not visited, do a depth first traverssal
    for (index = 0; index < gSize; index++) {
        if (!visited[index])
            dft(index,visited); 
    }

    delete [] visited;

} 

void graphType::dftAtVertex(int vertex) {
    bool *visited;
    visited = new bool[gSize];

    for (int index = 0; index < gSize; index++) 
        visited[index] = false;
    
    dft(vertex, visited); 
    delete [] visited;

}

void graphType::breadthFirstTraversal() {
    std::queue<int> q; 
    bool *visited;
    visited = new bool[gSize];

    for (int ind = 0; ind < gSize; ind++) 
        visited[ind] = false; //initialize the array visited to false

    std::list<int>::iterator graphIt;
    
    for (int index = 0; index < gSize; index++) 
    {
        if (!visited[index])
        {
            q.push(index); 
            visited[index] = true;
            std::cout << " " << index << " ";

            while (!q.empty()) {
                int u = q.front(); 
                q.pop();
                
                for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt; 
                    if (!visited[w]) {
                        q.push(w); 
                        visited[w] = true;
                        std::cout << " " << w << " ";
                    }
                }
            }
        }

    }
}

void graphType::clearGraph() {
    int index;
    for (index = 0; index < gSize; index++) {
            graph[index].clear();
    }   
    
    gSize = 0;

} 



#endif