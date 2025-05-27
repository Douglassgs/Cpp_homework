// src/Book.cpp
#include "Book.h++"
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision

Book::Book(const std::string& isbn, const std::string& title, const std::string& author, double price)
    : isbn(isbn), title(title), author(author), price(price) {}

std::string Book::getIsbn() const {
    return isbn;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

double Book::getPrice() const {
    return price;
}

void Book::display() const {
    std::cout << "ISBN: " << isbn << ", 书名: " << title
              << ", 作者: " << author << ", 价格: "
              << std::fixed << std::setprecision(2) << price << "元";
    // Removed std::endl to allow Bookstore to format list numbers.
}

