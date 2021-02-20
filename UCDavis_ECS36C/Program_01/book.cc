#include "book.h"

// Default constructor for the Book class
Book::Book() {
    ISBN = 0;
    lang = "none";
    type = "none";
}


// Constructor with arguments for the Book class
Book::Book(int giveISBN, std::string giveLang, std::string giveType) {
    ISBN = giveISBN;
    lang = giveLang;
    type = giveType;
}


// Setters and Getters for the Book class
int Book::getISBN(){ return ISBN; }
std::string Book::getLang(){ return lang; }
std::string Book::getType(){ return type; }
void Book::setISBN(int i){ ISBN = i; }
void Book::setLang(std::string s){ lang = s; }
void Book::setType(std::string t){ type = t; }


// Overload the stream operator to print the objects neatly
std::ostream& operator << (std::ostream& os, const Book& book) {
    std::string details = std::to_string(book.ISBN) + " " + book.lang + " " + book.type;
    os << details;
    return os;
}


// Compare by ISBN, if same compare reverse alphabetically
// string.compare returns - if A is alphabetically first returns + if A is alphabetically second
bool operator < (const Book& A, const Book& B) {

    // if A.ISBN is smallest, then A is < B
    if(A.ISBN < B.ISBN) {
        return true;
    }
    // If they have the same ISBN
    else if (A.ISBN == B.ISBN) {      
         
        // if A and B are different languages, check for reverse alphabetization
        // if A.compare(B) > 0, then they are reverse alphabetized and A is < B (return true)
        if(A.lang.compare(B.lang) != 0) {
            return (A.lang.compare(B.lang) > 0);
        }

        // If A(new), then A < B 
        if(A.type == B.type) {
            return false;
        }
        // If A(digital) && B != (new), then A < B
        else if (A.type == "digital" && B.type != "new") {
            return true;
        }
        // If the types are the same, then A !< B
        else if (A.type == "new") {
            return true;
        }
               
    }
    return false;
}


// Compare by ISBN, if same compare reverse alphabetically
bool operator > (const Book& A, const Book& B) { return B < A; };


// Compare all data points and determine if two books are identical
bool operator == (Book& A, Book& B) {
    if(A.ISBN == B.ISBN && A.lang == B.lang && A.type == B.type) {
        return true;
    }
    return false;
}
