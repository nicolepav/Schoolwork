#include <iostream>
#include <fstream>
#include <cmath>
#include "priorityqueue.h"

using namespace std;

//usage: createteams.exe jsonfile.json
int main(int argc, char** argv) {
    // throw error if incorrect number of files
    if(argc != 2) {
        std::cerr << "Usage: Wrong amount of files provided" << endl;
        return 1;
    }
    
    // opens the jsonfile
    ifstream jsonsource;
    jsonsource.open(argv[1]);
    nlohmann::json jsonObj;

    // makes sure the jsonfile opened correctly
    if(!jsonsource.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    } // if it opened correctly, put it into jsonObj
    else {
        jsonsource >> jsonObj;
    }
    
    // sets max size
    int sizeofqueue = 0;
    for(auto itr = jsonObj["teamStats"].begin(); itr != jsonObj["teamStats"].end(); ++itr){
        sizeofqueue++;
    }
    // makes a queue
    PriorityQueue queue(sizeofqueue);

    // sets up the queue by adding appropriate key-value pairs
    for(auto itr = jsonObj["teamStats"].begin(); itr != jsonObj["teamStats"].end(); ++itr){
        // put winPercentage into priorityqueue key
        Key newkey = itr.value()["winPercentage"];
        // edits key so the minimum of the heap will always be the team closest to 50% wins
        newkey = abs(newkey-50);
        // puts player one, player two into value of queue
        Value newval = make_pair(itr.value()["playerOne"], itr.value()["playerTwo"]);
        // makes the key value pair
        KeyValuePair newkvpair = make_pair(newkey, newval);
        // inserts the key value pair we made
        queue.insert(newkvpair);
    }
    
    // new object for later printing
    nlohmann::json newJsonObj;
    int i = 0;
    // sets the first element in the newjsonobj
    KeyValuePair newnode = queue.removeMin();
    newJsonObj["teams"][i++] = newnode.second;
    // in this loop, while the queue still has elements,
    // check if the removed min has any matching values to those already in the newjsonobj;
    // if it does, move on,
    // if it does not, add it to the newjsonobj.
    while(!queue.isEmpty()){
        bool cont = false;  // this is our check variable for if the players are already in the newjsonobject
        newnode = queue.removeMin();

        //this loop performs the check for every iteration in newjsonobject
        for(auto itr = newJsonObj["teams"].begin(); itr != newJsonObj["teams"].end(); itr++){
            if((*itr)[0] == newnode.second.first ||
                (*itr)[1] == newnode.second.first ||
                (*itr)[0] == newnode.second.second ||
                (*itr)[1] == newnode.second.second){
                    cont = true;
                    break;
            }
        }
        // continues with the loop, not saving the minimum value, if there was a match
        if(cont){
            continue;
        }

        newJsonObj["teams"][i++] = newnode.second;
    }

    // outputs our json
    cout << newJsonObj.dump(2);
}
