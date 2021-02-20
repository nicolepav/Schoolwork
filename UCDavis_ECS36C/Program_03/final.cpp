#include <iostream>
#include <fstream>
#include "json.hpp"

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

    // Create vector of vectors to store the arrays
    std::vector<std::vector<int>> vectorOfArrayVectors[3];
    // Get the size of the arrays
    int arraySize = file["metadata"]["arraySize"];

    // iterate through JSON file
    for(auto itr = file.begin(); itr != file.end(); ++itr){
        // if at metadata, break look
        if(itr.key() == "metadata") {
            break;
        }

        // For each of the three arrays
        for(int i = 0; i < 3; i++) {
            // for every value stored in the key's array, push it to the vector
            for(int j = 0; j < arraySize; j++) {
                vectorOfArrayVectors[i].push_back(itr.value()[j]);
            }
            
        }
    }

    // If the last element of every vector is equal return true
    if( (vectorOfArrayVectors[0][arraySize-1] == vectorOfArrayVectors[1][arraySize-1]) &&  
        (vectorOfArrayVectors[0][arraySize-1] == vectorOfArrayVectors[2][arraySize-1])) {
            return true;
        }
    // Otherwise return false
    else {
        return false;
    }

}