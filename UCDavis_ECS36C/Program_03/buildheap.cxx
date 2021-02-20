#include <iostream>
#include <fstream>
#include "priorityqueue.h"

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

    // Create a queue with a size based on the information from the json file
    // and initialize the variable newKey
    signed int queuesize = file["metadata"]["maxHeapSize"];
    PriorityQueue queue(queuesize);
    Key newkey = 0.0;

    // iterate through the file until reaching the metadata
    for(auto itr = file.begin(); itr != file.end(); ++itr){
        // if at metadata, break look
        if(itr.key() == "metadata") {
            break;
        }

        // if file says to insert, perform insertion
        if(file[itr.key()]["operation"] == "insert") {
            newkey = file[itr.key()]["key"];
            queue.insert(newkey);
        }
        // if file says to remove the minimum, perform removeMin
        else if (file[itr.key()]["operation"] == "removeMin") {
            queue.removeMin();
        }

        // reset the newkey variable
        newkey = 0.0;
    }
    
    // create a json object to store the results
    nlohmann::json results = queue.JSON();
    // add metadata to the results object
    results["metadata"]["maxHeapSize"] = file["metadata"]["maxHeapSize"];
    results["metadata"]["numOperations"] = file["metadata"]["numOperations"];
    // print results object to stream
    std::cout << results.dump(2);

}
