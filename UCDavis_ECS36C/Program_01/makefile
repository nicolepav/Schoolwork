CC =  g++
CFLAGS = -g -Wall -Werror

default: SearchNewBooks

SearchNewBooks: SearchNewBooks.o book.o 
	$(CC) $(CFLAGS) -o SearchNewBooks book.o SearchNewBooks.o 

book.o: book.cc book.h
	$(CC) $(CFLAGS) -c book.cc

SearchNewBooks.o: SearchNewBooks.cc
	$(CC) $(CFLAGS) -c SearchNewBooks.cc

clean:
	$(RM) SearchNewBooks *.o *.dat *~