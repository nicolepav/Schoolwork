/*
The next tools you will build come in a pair, because one (**wzip**) is a
file compression tool, and the other (**wunzip**) is a file decompression
tool. 

The type of compression used here is a simple form of compression called
*run-length encoding* (*RLE*). RLE is quite simple: when you encounter **n**
characters of the same type in a row, the compression tool (**wzip**) will
turn that into the number **n** and a single instance of the character.

However, the exact format of the compressed file is quite important; here,
you will write out a 4-byte integer in binary format followed by the single
character in ASCII. Thus, a compressed file will consist of some number of
5-byte entries, each of which is comprised of a 4-byte integer (the run
length) and the single character. 

To write out an integer in binary format (not ASCII), you should use
**write()**. Read the man page for more details. For **wzip**, all
output should be written to standard output (the **STDOUT_FILENO** file descriptor,
which, is already open when the program starts running). 

**Details**

* Correct invocation should pass one or more files via the command line to the 
  program; if no files are specified, the program should exit with return code
  1 and print "wzip: file1 [file2 ...]" (followed by a newline) or
* The format of the compressed file must match the description above exactly
  (a 4-byte integer followed by a character for each run).
* Do note that if multiple files are passed to **wzip*, they are compressed
  into a single compressed output, (thus, the information that multiple files were
  originally input into **wzip** is lost).
*/

#include <iostream>     // COUT
#include <fcntl.h>      // OPEN
#include <unistd.h>     // STDOUT_FILENO
#include <string>       // STRINGS
#include <cstring>      // STRING OUTPUT

using namespace std;

int main(int argc, char *argv[]){

    if(argc < 2) {
        cout << "wzip: file1 [file2 ...]" << endl;
        return 1;
    }

	char buffer[1];
	int fd;
	int reading = 0;

	string current = "";
	string next = "";
	int byteint[4];
	int multiple = -1;
	int sizeofbyte = 4;

	for(int i = 1; i < argc; i++) {
        
		// if can't open return error
        fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            cout << "wzip: cannot open file" << endl;
            return 1;
        }

		while((reading = read(fd, buffer, 1)) > 0) {
			
			next = buffer[0];
			
			if(multiple == -1){
				// this is the first iteration
				current = next;
				multiple = 1;
			}
			else {

				if(next != current) {
					
					// Make a 4 byte int
					byteint[0] = multiple;
					byteint[1] = (multiple << 8);
					byteint[2] = (multiple << 16);
					byteint[3] = (multiple << 24);

					// send out
					write(STDOUT_FILENO, byteint, sizeofbyte);
					write(STDOUT_FILENO, current.c_str(), current.length());

					// clear
					current = next;
					multiple = 1;
				}
				else {
					multiple++;
				}
			}
		}

		// If it is the last file
		if(i == (argc - 1)) {
			
			// Make a 4 byte int
			byteint[0] = multiple;
			byteint[1] = (multiple << 8);
			byteint[2] = (multiple << 16);
			byteint[3] = (multiple << 24);

			// send out
			write(STDOUT_FILENO, byteint, sizeofbyte);
			write(STDOUT_FILENO, current.c_str(), current.length());

			// clear
			current = next;
			multiple = 1;
		}
			
		close(fd);
	}
    return 0;
}