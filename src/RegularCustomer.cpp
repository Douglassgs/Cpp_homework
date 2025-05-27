// src/RegularCustomer.cpp
#include "RegularCustomer.h++"
#include <iostream>

RegularCustomer::RegularCustomer(const std::string& id, const std::string& name)
    : Customer(id, name) {}

double RegularCustomer::applyDiscount(double originalPrice) const {
    return originalPrice; // 普通顾客无折扣
}

void RegularCustomer::display() const {
    Customer::display();
    std::cout << ", 类型: 普通顾客";
}

std::string RegularCustomer::getTypeString() const {
    return "普通顾客";
}

std::string RegularCustomer::getDiscountInfo() const {
    return "无折扣";
}

