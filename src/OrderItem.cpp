// src/OrderItem.cpp
#include "OrderItem.h++"
#include <iostream>
#include <iomanip> // 用于 std::fixed, std::setprecision

OrderItem::OrderItem() : book(), quantity(0) {
    // book 成员将使用 Book 类的默认构造函数进行初始化
    // quantity 初始化为 0
}

OrderItem::OrderItem(const Book& b, int qty)
    : book(b), quantity(qty) {
    if (this->quantity < 1) { // 确保数量至少为1
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
    std::cout << "书籍: " << book.getTitle() << " (ISBN: " << book.getIsbn() << ")"
              << ", 数量: " << quantity
              << ", 单价: " << std::fixed << std::setprecision(2) << book.getPrice()
              << ", 小计: " << std::fixed << std::setprecision(2) << getTotalPrice() << "元";
}

