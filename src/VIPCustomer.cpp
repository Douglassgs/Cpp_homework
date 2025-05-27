// src/VIPCustomer.cpp
#include "VIPCustomer.h++"
#include <iostream>
#include <iomanip> // For std::fixed, std::setprecision
#include <sstream> // For std::ostringstream

VIPCustomer::VIPCustomer(const std::string& id, const std::string& name, double discount)
    : Customer(id, name), specialDiscountRate(discount) {
    if (specialDiscountRate < 0.0) specialDiscountRate = 0.0;
    if (specialDiscountRate > 1.0) specialDiscountRate = 1.0; // 折扣率不能超过100%
}

double VIPCustomer::getSpecialDiscountRate() const {
    return specialDiscountRate;
}

double VIPCustomer::applyDiscount(double originalPrice) const {
    return originalPrice * (1.0 - specialDiscountRate);
}

void VIPCustomer::display() const {
    Customer::display();
    std::cout << ", 类型: 贵宾顾客, 特别折扣率: "
              << std::fixed << std::setprecision(2) << (specialDiscountRate * 100) << "%";
}

std::string VIPCustomer::getTypeString() const {
    return "贵宾顾客";
}

std::string VIPCustomer::getDiscountInfo() const {
    std::ostringstream oss;
    oss << "享受 " << std::fixed << std::setprecision(0) << (specialDiscountRate * 100) << "% 折扣 (按原价 "
        << std::fixed << std::setprecision(2) << (1.0 - specialDiscountRate) * 100 << "% 收费)";
    return oss.str();
}

