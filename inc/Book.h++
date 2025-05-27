// inc/Book.h++
#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    double price;

public:
    Book(const string& isbn = "", const string& title = "", const string& author = "", double price = 0.0);

    string getIsbn() const;
    string getTitle() const;
    string getAuthor() const;
    double getPrice() const;

    void display() const;
};

#endif // BOOK_HPP

