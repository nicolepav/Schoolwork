#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "book.h"

int linearSearch(std::vector<Book> &Books, std::vector<Book> &requests);
int binarySearch(std::vector<Book> &Books, std::vector<Book> &requests, int l, int r);

void gather(std::ifstream& infile, std::vector<Book> &list);
void printLists(std::vector<Book> &newBooksList, std::vector<Book> &requestsList);



int main(int argc, char *argv[]) {
    
    // Check that user provided all necessary arguments
    if(argc != 4) {
        std::cerr << "Usage: .SearchNewBooks <newBooks.dat> <request.dat> <result_file.dat>" << std::endl;
        return 1;
    }

    // Open filestream for each of the provided arguments
    std::ifstream newBooks;
    std::ifstream requests; 
    
    newBooks.open(argv[1]);
    requests.open(argv[2]);

    std::ofstream results;
    results.open(argv[3]);
    
    // Check that all provided files open correctly
    if(!newBooks.is_open()) {
        std::cout << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }
    if(!requests.is_open()) {
        std::cout << "Error: cannot open file " << argv[2] << std::endl;
        return 1;
    }
    if(!results.is_open()) {
        std::cout << "Error: cannot open file " << argv[3] << std::endl;
        return 1;
    }

    // Create vector of books for each data type
    std::vector<Book> newBooksList;
    std::vector<Book> requestsList;
    
    // Import data from file stream into the vectors
    gather(newBooks, newBooksList);
    gather(requests, requestsList);


    // Allow user to select binary or linear search
    char userinput = ' ';
    int resultsfound = 0;
    std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;

    // Clock objects for code analysis
    std::chrono::high_resolution_clock::time_point start;
    

    // Run until the user selects a valid input
    while (userinput != '!') {
        
        std::cin >> userinput;
        if (userinput == 'l') {

            // Start clock and perform linear search
            start = std::chrono::high_resolution_clock::now();
            resultsfound = linearSearch(newBooksList, requestsList);
            
            // Finish and print clock
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>(end-start).count();
            std::cout << "CPU time " << elapsed_us << " microseconds" << std::endl;
            userinput = '!';
        }
        else if (userinput == 'b') {
            // Sort list for binary search
            std::sort(newBooksList.begin(), newBooksList.end());   

            // Start the clock and perform a binary search
            start = std::chrono::high_resolution_clock::now();    
            resultsfound = binarySearch(newBooksList, requestsList, 0, newBooksList.size()-1);

            // Finish and print clock
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>(end-start).count();
            std::cout << "CPU time " << elapsed_us << " microseconds" << std::endl;
            userinput = '!';
        }
        else {
            std::cout << "Incorrect choice" << std::endl;
            std::cerr << "User inputed incorrect choice" << std::endl;
        }

    };

    // Print results to file and close all file streams
    results << resultsfound;
    results.close();

    newBooks.close();
    requests.close();

}






// Functions to import data from a given file into a vector of books
void gather(std::ifstream& infile, std::vector<Book> &list) {
    
    std::string tempISBN, language, type, line;

    while(std::getline (infile, line)) {
        std::stringstream ss(line);
        std::getline(ss, tempISBN, ',');
        std::getline(ss, language, ',');
        std::getline(ss, type);

        list.push_back(Book(std::stoi(tempISBN), language, type));
    }
}



// Function to print the two vectors of books (newbooks and requests)    
void printLists(std::vector<Book> &newBooksList, std::vector<Book> &requestsList) {
    
    for(unsigned int i = 0; i < newBooksList.size();i++) {
        std::cout << "i:" << i << "\t" << newBooksList[i] << std::endl;
    }
    for(unsigned int i = 0; i < requestsList.size();i++) {
        std::cout << "i:" << i << "\t" << requestsList[i] << std::endl;
    }
}

    

// Compare each book in requests to every book in Books
int linearSearch(std::vector<Book> &Books, std::vector<Book> &requests) {

    int count = 0;
    for(unsigned int i = 0; i < requests.size(); i++) {
        for(unsigned int j = 0; j < Books.size(); j++) {            
            if(requests[i] == Books[j]) {
                count++;
                j = Books.size();
            }
        }
    } 
    return count;  

}



// Execute a binary search on Books, for every request in requests in between a user-submitted
// range of bounds on the Books vector
int binarySearch(std::vector<Book> &Books, std::vector<Book> &requests, int l, int r) {
    
    int count = 0;
    bool searching;
    for(unsigned int z = 0; z < requests.size(); z++) {        

        int i = l;
        int j = r;
        searching = true;

        while(searching) {
                     
            // If all bounds checked and it doesnt exist, stop searching
            if ( j < i) { searching = false;}
            int m = (i + j) / 2;

            // If the data is bigger than mid, change low bound to mid + 1
            if (requests[z] > Books[m]) {
                i = m + 1;
            }
            // If the data is smaller than mid, change the high bound to mid
            else if (requests[z] < Books[m]) {
                j = m - 1;
            }
            // If the data is the same as at mid, then it is found
            else if (requests[z] == Books[m]) {
                count++;
                searching = false;
            }       
        }       
    }
    return count;

}