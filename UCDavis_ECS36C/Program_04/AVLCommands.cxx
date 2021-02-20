#include "AVL.h"
#include <iostream>
#include <fstream>

// Function to create a JSON object from an AVL Tree
nlohmann::json makeJSONobject(AVLTree T);

// Function to make an AVL Tree from a JSON file
AVLTree makeAVLfromFile(nlohmann::json file);


// Accepts a JSON file, creates an AVL tree, and dumps the tree to std::cout
int main(int argc, char** argv) {

    // Check that the correct amount of file were provided
    if(argc != 2) {
        std::cerr << "Usage: Wrong amount of files provided" << std::endl;
        return 1;
    }
    // Create a json object and open the provided file
    std::ifstream jsonsource;
    jsonsource.open(argv[1]);
    nlohmann::json file;

    // check that the file can be opened, if it can then read the file to the json object
    if(!jsonsource.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }
    else {
        jsonsource >> file;
    }

    // Create output object by running JSON -> AVL and AVL -> object functions
    nlohmann::json outputObj =  makeJSONobject(makeAVLfromFile(file));

    // Print final JSON result to stream
    std::cout << outputObj.dump(2);

    
}

// Function to create a JSON from a Tree
nlohmann::json makeJSONobject(AVLTree T){

    // Object to return results
    nlohmann::json results;
    // Traverse the tree, traversal function adds to passed json file
    T.preorderTraversal(T.getRoot(), T.getRoot()->key, results);
    // Include size field
    results["size"] = T.Size();
    // Return results
    return results;
}

// Function to create a tree from a json
AVLTree makeAVLfromFile(nlohmann::json file) {
    
    // Create tree that will be returned
    AVLTree T = AVLTree();

    // Iterate through JSON file inserting to tree
    for(auto itr = file.begin(); itr != file.end(); ++itr){
        if(itr.key() == "metadata"){
            break;
        }
        T.setRoot(T.Insert(itr.value()["key"], T.getRoot()));
    }

    // Return tree
    return T;
}