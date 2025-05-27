// inc/Book.h++
#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    double price;

public:
    Book(const std::string& isbn = "", const std::string& title = "", const std::string& author = "", double price = 0.0);

    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    double getPrice() const;

    void display() const;
};

#endif // BOOK_HPP

