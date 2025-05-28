// src/RegularCustomer.cpp
#include "RegularCustomer.h++"
#include <iostream>

using namespace std;

RegularCustomer::RegularCustomer(const std::string& id, const std::string& name)
    : Customer(id, name) {}

double RegularCustomer::applyDiscount(double originalPrice) const {
    return originalPrice;
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

