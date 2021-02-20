#include "json.hpp"
#include <fstream>
#include <iostream>

// Takes JSON file as command-line argument file.json that represents output of a sorting algorithm,
// verifies each sample is a sorted array. 

using namespace std;

int main(int argc, char** argv) {
    if(argc!=2){
        std::cerr << "Error: Wrong amount of arguments passed" << std::endl;
        return 1;
    }

    ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    
    //checks that file can be put into jsonObject
    if(file.is_open()){
        file >> jsonObject;
    }
    else {
        return 1;
    }
        

    //the array size for use later
    int size = jsonObject["metadata"]["arraySize"];

    //newObj is what we'll be printing later
    nlohmann::json newObj;

    //for tracking in newObj[metadata]
    int samplesWithInversions;

    //outer loop: iterates through keys in jsonObject
    for(auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr){
            
            //ensures metadata key is skipped
            if(itr.key() == "metadata") {
                break;
            }
            
            //for tracking whether we have already seen an inversion within this key
            bool ind = false;
            
            //inner loop: checks for consecutive inversions, adds any to newObj
            for(int i = 0; i < size-1; i++){
                if(jsonObject[itr.key()][i] > jsonObject[itr.key()][i+1]){
                    ind = true;
                    char str[8];
                    sprintf(str,"%d",i);
                    newObj[itr.key()]["ConsecutiveInversions"][str][0] = itr.value()[i];
                    newObj[itr.key()]["ConsecutiveInversions"][str][1] = itr.value()[i+1];
                }
            }

            //adds final data field and updates tracker of number of samples with inversions
            if(ind == true){
                newObj[itr.key()]["sample"] = itr.value();
                samplesWithInversions++;
            }
    }


    //creating the metadata fields
    newObj["metadata"]["arraySize"] = jsonObject["metadata"]["arraySize"];
    newObj["metadata"]["file"] = argv[1];
    newObj["metadata"]["numSamples"] = jsonObject["metadata"]["numSamples"];
    newObj["metadata"]["samplesWithInversions"] = samplesWithInversions;

    //prints newObj in human readable format
    cout <<  newObj.dump(2) << "\n";
    return 0;
}