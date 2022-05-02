#include <iostream>     // COUT
#include <fcntl.h>      // OPEN
#include <unistd.h>     // STDOUT_FILENO


/*
The program wcat is a simple program. Generally, it reads a file as
specified by the user and prints its contents. 

- required to use open, read, write, close
- if no files are on the command line, wcat should exit and return 0
- if multiple files are specificied, the files should be printed out
  in order until the end of the file list is reached or an error occurs
*/

// You'll need to learn how to use a few library routines from the C++ standard
// library (often called **libc++**) to implement the source code for this program

// reading in a line with read() into a variable buffer and keeping
// track of the number of bytes that you read in a variable bytesRead
// you can just print out the buffer as follows
// write(fd, buffer, bytesRead)


using namespace std;

int main(int argc, char *argv[]){

    int fd;
    char buffer[4096];
    int bytesRead = 0;

    // For as many files as are passed
    for(int i = 1; i < argc; i++){

        // open the file in read only mode
        fd = open(argv[i], O_RDONLY);

        // if file fails to open, return error
        if (fd == -1) {
            cout << "wcat: cannot open file" << endl;
            return 1;
        }

        // read returns 0 when finished, num bytes read otherwise (lec 47:00)
        // while there are bytes read to the buffer, write them to STDOUT
        while((bytesRead = read(fd, buffer, 4096)) > 0) {     
            write(STDOUT_FILENO, buffer, bytesRead);
        }
        
        // Close file, move to next
        close(fd);
    }

    return 0;
}