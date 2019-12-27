// PAVLOVICH, NICOLE
// PROJECT 06 - Rewriting program from Chapter 17, page 1184 using STL


#include <iostream>  
#include <iomanip>
#include <fstream>
#include <string>

#include <queue>

using namespace std;

int main()
{
    double GPA;
    double highestGPA;
    string name;

    queue<string> q;

    ifstream infile;
    infile.open("HighestGPAData.txt");          

    if (!infile)
    {
        cout << "The input file does not exist. Program terminates!" << endl;
        return 1;
    }

    cout << fixed << showpoint;                 
    cout << setprecision(2);                    
    infile >> GPA >> name;                      
    highestGPA = GPA;                           

    while (infile)                              
    {
        if (GPA > highestGPA)                   
        {
            while (!q.empty())              
            {
                // clear the stack of the lower gpas
                q.pop();
            }

            q.push(name);
            highestGPA = GPA;                  
        }
        else if (GPA == highestGPA)
        {
            q.push(name);
        }             
            
        infile >> GPA >> name;                  
    }

    cout << "Highest GPA = " << highestGPA << endl;
    cout << "The students holding the highest GPA are:" << endl;

    while (!q.empty())              
    {
        cout << q.front() << endl;
        q.pop();
    }

    cout << endl;
    return 0;
}