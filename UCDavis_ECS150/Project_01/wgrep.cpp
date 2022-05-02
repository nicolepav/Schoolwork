#include <iostream>     // COUT
#include <fcntl.h>      // OPEN
#include <unistd.h>     // STDOUT_FILENO
#include <string>       // STRINGS
#include <cstring>      // STRING OUTPUT

/*
This tool looks through a file, line by line, trying to find a
user-specified search term in the line. If a line has the word within it, the
line is printed out, otherwise it is not.

./wgrep searchTerm file.txt

- always passed searchterm and 0 or more files
- matching is case sensitive
- lines can be arbitrarily long, may want to write a function that reads
  from a file descriptor and buffers data until you reach a newline char

- search term but no file means read from the standard input. 
- for simplicity, is passed the empty string wgrepcan match no lines or match all lines

- if no arguments, print "wgrep: searchterm [file...]" and exit 1
- if file cant open, print "wgrep: cannot open file" and exit 1
- all other cases exit return 0

*/

using namespace std;

int main(int argc, char *argv[]){


    int fd;
    char buffer[1];
    string searchterm = "";
    string currentline = "";


    // For as many files as are passed
    for(int i = 0; i < argc; i++){

        // if there is no searchterm provided
        if (argc ==  1){
            cout << "wgrep: searchterm [file ...]" << endl;
            return 1;
        }
        
        if(i == 0) {
            i += 2;
        }

        // open the file in read only mode (or open STDIN)
        if(argc == 2){
            fd = STDIN_FILENO;
        }
        else {
            fd = open(argv[i], O_RDONLY);
            // if file fails to open, return error
            if (fd == -1) {
                cout << "wgrep: cannot open file" << endl;
            return 1;
            }
        }
            
        searchterm = argv[1];
        // If given empty string, match no lines
        if (searchterm == "") {
            return 0;
        }

        while((read(fd, buffer, 1) > 0)) {

            if(buffer[0] != '\n') {
                currentline.push_back(buffer[0]);
            }
            else if(buffer[0] == '\n') {

                // do the search,  print if necessary
                if(currentline.find(searchterm) != string::npos) { 
                    currentline.push_back('\n');
                    write(STDOUT_FILENO, currentline.c_str(), currentline.length());
                }

                // reset currentline
                currentline = "";
            }
        }

        // Close file, move to next
        close(fd);
    }

    return 0;
}
