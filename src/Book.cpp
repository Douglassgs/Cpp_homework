// src/Book.cpp
#include "Book.h++"
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision

using namespace std;

Book::Book(const string& isbn, const string& title, const string& author, double price)
    : isbn(isbn), title(title), author(author), price(price) {}

string Book::getIsbn() const {
    return isbn;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

double Book::getPrice() const {
    return price;
}

void Book::display() const {
    cout << "ISBN: " << isbn << ", 书名: " << title
         << ", 作者: " << author << ", 价格: "
         << fixed << setprecision(2) << price << "元";
    // Removed std::endl to allow Bookstore to format list numbers.
}

