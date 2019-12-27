// Nicole Pavlovich, CS 2B, Section 20407, Professor Harden
// Assignment 8.1: Vectors & Iterators
// A8_1.cpp

// Description: This program reworks the original highestscore program
// to use an STL vector & a struct instead of two parallel arrays to store
// pairs of names and scores. It sorts the entries by highest to lowest score

// No documentation required for this project

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct highscore {
    int score;
    char name[24];
};

void initializeData(vector<highscore>& scores);
void sortData(vector<highscore>& scores);
void displayData(const vector<highscore>& scores);


int main() {

    int vectorSize;
    cout << "How many scores will you enter?: ";
    cin >> vectorSize;

    vector<highscore> scores(vectorSize);

    initializeData(scores);
    sortData(scores);
    displayData(scores);
}



void initializeData(vector<highscore>& scores) {
    for (vector<highscore>::iterator i = scores.begin(); i != scores.end(); i++) {
        cout << "Enter the name this entry: ";
        cin >> i->name;
        cout << "Enter the score this entry: ";
        cin >> i->score;
    }
    cout << endl;

}
void sortData(vector<highscore>& scores) {
    
    highscore tempscore;

    for(vector<highscore>::iterator j = scores.begin(); j != scores.end()-1; j++) {
        for(vector<highscore>::iterator i = scores.begin(); i != scores.end(); i++) {
            
            if (i->score < (i+1)->score) {
                
                tempscore = *i;
                *i = *(i+1);
                *(i+1) = tempscore;

            }
        }
    }
}

void displayData(const vector<highscore>& scores) {
    cout << "Top Scorers:" << endl;
    for(vector<highscore>::const_iterator i = scores.begin(); i != scores.end(); i++) {
        cout << i->name << ": " << i->score << endl;
    }
}


/* Expected Output

Last login: Sun Nov 17 15:13:30 on ttys000
Nicole-Pav:~ nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A8/" && 
g++ a8_1.cpp -o a8_1 && "/Users/nicolepavlovich/Desktop/CS_Foothill/A8/"a8_1

How many scores will you enter?: 4
Enter the name this entry: Suzy
Enter the score this entry: 600
Enter the name this entry: Kim
Enter the score this entry: 9900
Enter the name this entry: Armando
Enter the score this entry: 8000
Enter the name this entry: Tim
Enter the score this entry: 514

Top Scorers:
Kim: 9900
Armando: 8000
Suzy: 600
Tim: 514
Nicole-Pav:A8 nicolepavlovich$ 
*/