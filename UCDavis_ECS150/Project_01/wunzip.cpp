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

The **wunzip** tool simply does the reverse of the **wzip** tool, taking
in a compressed file and writing (to standard output again) the uncompressed
results. For example, to see the contents of **file.txt**, you would type:

prompt> ./wunzip file.z

**wunzip** should read in the compressed file (using **read()**)
and print out the uncompressed output to standard output using **write()**.

**Details**

* Correct invocation should pass one or more files via the command line to the 
  program; if no files are specified, the program should exit with return code
  1 and print "wunzip: file1 [file2 ...]" (followed by a newline) 
* The format of the compressed file must match the description above exactly
  (a 4-byte integer followed by a character for each run).
* Do note that if multiple files are passed to **wzip*, they are compressed
  into a single compressed output, and when unzipped, will turn into a single
  uncompressed stream of text (thus, the information that multiple files were
  originally input into **wzip** is lost). The same thing holds for
  **wunzip**. 

*/

#include <iostream>     // COUT
#include <fcntl.h>      // OPEN
#include <unistd.h>     // STDOUT_FILENO
#include <string>       // STRINGS
#include <cstring>      // STRING OUTPUT

using namespace std;

int main(int argc, char *argv[]){

    if(argc < 2) {
        cout << "wunzip: file1 [file2 ...]" << endl;
        return 1;
    }

	char buffer[1];
	int fd;

	// for as many files as are provided
    for(int i = 1; i < argc; i++) {
        
		// if can't open return error
        fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            cout << "wunzip: cannot open file" << endl;
            return 1;
        }

		// Variables & Storage
		int reading = 0;
		string printable = "";
		int multiple = 0;
		int tracker = 0;
		char tempbuffer[4];

		// While still content to read from file
		while ((reading = read(fd, buffer, 1 ) > 0)) {
			
			// every 4/5 bytes are part of the char
			if(tracker < 4) {
				tempbuffer[tracker] = buffer[0];
				tracker++;
			}
			// once all bytes collected, convert, add to string, and write
			else {
				multiple = (int)(tempbuffer[0] | tempbuffer[1] << 8 | tempbuffer[2] << 16 | tempbuffer[3] << 24);
				for(int j = 0; j < multiple; j++){
					printable.push_back(buffer[0]);
				}

				write(STDOUT_FILENO, printable.c_str(), printable.length());

				// reset vars
				printable = "";
				multiple = 0;
				tracker = 0;
			}

		}
		close(fd);
    }
    return 0;
}
