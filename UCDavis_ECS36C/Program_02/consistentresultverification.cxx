#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

// This program takes two command-line arguments file1.json and file2.json
// that contain JSON objects representing the output of two sorting algorithms,
// and verifies that these files represent the same samples or reports their differences.

using namespace std;

int main(int argc, char** argv) {
    std::ifstream file1;
    file1.open(argv[1]);
    nlohmann::json file1JSON;
    if (file1.is_open()) {
        file1 >> file1JSON;
    }

    std::ifstream file2;
    file2.open(argv[2]);
    nlohmann::json file2JSON;
    if (file2.is_open()) {
        file2 >> file2JSON;
    }
    
    //results
    nlohmann::json newObj;
    
    //samplesWithConflictingResults will be put in metadata later
    int samplesWithConflictingResults = 0;
    
    //iterates through each key in file2JSON
    for(auto itr = file2JSON.begin(); itr != file2JSON.end(); ++itr){
        if(itr.key() == "metadata"){
            break;
        }
        bool ind = false;
        for(int i = 0; i < file2JSON["metadata"]["arraySize"]; i++){
            
            //makes comparison between JSONs
            if(file1JSON[itr.key()][i] != file2JSON[itr.key()][i]){
                    
                //sets first key i.e. AlmostSampleExample
                if(!ind){
                    newObj[itr.key()][argv[2]] = itr.value();
                }

                //convert i to str
                char str[8];
                sprintf(str, "%d", i);

                //creates Mismatches
                newObj[itr.key()]["Mismatches"][str][0] = file1JSON[itr.key()][i];
                newObj[itr.key()]["Mismatches"][str][1] = file2JSON[itr.key()][i];

                //sets last key i.e. SampleExample, also updates indicator and samplesWithConflictingResults
                if(!ind){
                    ind = true;
                    samplesWithConflictingResults++;
                    newObj[itr.key()][argv[1]] = file1JSON[itr.key()];
                }
            }
        }
    }

    //creates lots of happy metadata fields
    newObj["metadata"]["File1"]["arraySize"] = file1JSON["metadata"]["arraySize"];
    newObj["metadata"]["File2"]["arraySize"] = file2JSON["metadata"]["arraySize"];
    newObj["metadata"]["File1"]["name"] = argv[1];
    newObj["metadata"]["File2"]["name"] = argv[2];
    newObj["metadata"]["File1"]["numSamples"] = file1JSON["metadata"]["numSamples"];
    newObj["metadata"]["File2"]["numSamples"] = file2JSON["metadata"]["numSamples"];
    newObj["metadata"]["samplesWithConflictingResults"] = samplesWithConflictingResults;

    //let's test it
    cout << newObj.dump(2) << "\n";
    return 0;
}