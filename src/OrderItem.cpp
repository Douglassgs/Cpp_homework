// src/OrderItem.cpp
#include "OrderItem.h++"
#include <iostream>
#include <iomanip>

using namespace std;

OrderItem::OrderItem() : book(), quantity(0) {
}

OrderItem::OrderItem(const Book& b, int qty)
    : book(b), quantity(qty) {
    if (this->quantity < 1) {
        this->quantity = 1;
    }
}

Book OrderItem::getBook() const {
    return book;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getTotalPrice() const {
    return book.getPrice() * quantity;
}

void OrderItem::display() const {
    cout << "书籍: " << book.getTitle() << " (ISBN: " << book.getIsbn() << ")"
         << ", 数量: " << quantity
         << ", 单价: " << fixed << setprecision(2) << book.getPrice()
         << ", 小计: " << fixed << setprecision(2) << getTotalPrice() << "元";
}

