// inc/OrderItem.h++
#ifndef ORDER_ITEM_HPP
#define ORDER_ITEM_HPP

#include "Book.h++"
#include <string>
#include <iostream> // 用于 display
#include <iomanip>  // 用于 std::fixed, std::setprecision

class OrderItem {
private:
    Book book;      // 购买的书籍对象
    int quantity;   // 购买数量

public:
    OrderItem(); // 默认构造函数
    OrderItem(const Book& b, int qty);

    Book getBook() const;
    int getQuantity() const;
    double getTotalPrice() const; // 获取该订单项的总价（原价）

    void display() const;
};

#endif // ORDER_ITEM_HPP

