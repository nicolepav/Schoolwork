#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>

#include "json.hpp"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"

// For each sample, collect and print these statistics to the screen in CSV format
// Your header row for your CSV file must have the following column names 
    // Sample   InsertionSortTime   InsertionSortCompares   InsertionSortMemaccess
    //          MergeSortTime       MergeSortCompares       MergeSortMemaccess
    //          QuickSortTime       QuickSortCompares       QuickSortMemaccess


int main(int argc, char** argv) {

    if(argc!=2){
        std::cerr << "Error: Wrong amount of arguments passed" << std::endl;
        return 1;
    }

    // Open the provided JSON file
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }
    else {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }


    // Collect the data from the JSON file
    std::vector<std::vector<int>> insertiondata;
    std::vector<std::vector<int>> mergesortdata;
    std::vector<std::vector<int>> quicksortdata;
    std::vector<std::string> samplenames;

    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        std::vector<int> temp;
        if(itr.key() != "metadata") {
            for( auto itr2 = itr.value().begin(); itr2 != itr.value().end(); ++itr2) {
                temp.push_back(itr2.value());
            }
            samplenames.push_back(itr.key());
            insertiondata.push_back(temp);
            mergesortdata.push_back(temp);
            quicksortdata.push_back(temp);      
        }       
    }

    // Create results vector and prefill with blanks to allocate data
    std::vector<std::vector<int>> resultsbysample;
    std::vector<int> temp(9, 0);
    for(int i = 0; i < insertiondata.size(); i++) {
        resultsbysample.push_back(temp);
    }

    int numcomparisons = 0, memaccess = 0;
    // Perform insertion sort on all samples
    for(int i = 0; i < insertiondata.size(); i++) {
        clock_t t = clock();
        numcomparisons = 0;
        memaccess = 0;

        InsertionSort(&insertiondata[i], numcomparisons, memaccess);

        t = clock() - t;
        resultsbysample[i][0] = ((float)t)/CLOCKS_PER_SEC;
        resultsbysample[i][1] = numcomparisons;
        resultsbysample[i][2] = memaccess;
    }

    
    // Perform merge sort on all samples
    for(int i = 0; i < mergesortdata.size(); i++) {
        clock_t t = clock();
        numcomparisons = 0;
        memaccess = 0;

        MergeSort(&mergesortdata[i], numcomparisons, memaccess);

        t = clock() - t;
        resultsbysample[i][3] = ((float)t)/CLOCKS_PER_SEC;
        resultsbysample[i][4] = numcomparisons;
        resultsbysample[i][5] = memaccess;
    }


    // Perform quicksort on all samples
    for(int i = 0; i < quicksortdata.size(); i++) {
        clock_t t = clock();
        numcomparisons = 0;
        memaccess = 0;

        QuickSort(&quicksortdata[i], numcomparisons, memaccess);

        t = clock() - t;
        resultsbysample[i][6] = ((float)t)/CLOCKS_PER_SEC;
        resultsbysample[i][7] = numcomparisons;
        resultsbysample[i][8] = memaccess;
    }


    std::cout << "Sample,InsertionTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;

    for(int i = 0; i < samplenames.size(); i++) {
        
        std::cout << samplenames[i] << ',';
        for(int j = 0; j < 9; j++) {
            if ( j < 8) {   
                std::cout << resultsbysample[i][j] << ',';
            }
            else {
                std::cout << resultsbysample[i][j];
            }    
        }
        std::cout << std::endl;
        
    }  

}