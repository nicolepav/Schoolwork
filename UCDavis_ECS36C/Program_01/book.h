#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
    private:
        int ISBN;
        std::string lang;
        std::string type;

    public:
        Book();
        Book(int giveISBN, std::string giveLang, std::string giveType);

        int getISBN();
        std::string getLang();
        std::string getType();

        void setISBN(int i);
        void setLang(std::string s);
        void setType(std::string t);

        friend std::ostream& operator << (std::ostream& os, const Book& book);
        friend bool operator < (const Book& A, const Book&B);
        friend bool operator > (const Book& A, const Book&B);
        friend bool operator == (Book& A, Book& B);

};

#endif