// src/MemberCustomer.cpp
#include "MemberCustomer.h++"
#include <iostream>
#include <iomanip> // 用于 std::fixed, std::setprecision
#include <sstream> // 用于 std::ostringstream

MemberCustomer::MemberCustomer(const std::string& id, const std::string& name, int level)
    : Customer(id, name), starLevel(level) {
    if (starLevel < 1) starLevel = 1;
    if (starLevel > 5) starLevel = 5;
}

int MemberCustomer::getStarLevel() const {
    return starLevel;
}

double MemberCustomer::applyDiscount(double originalPrice) const {
    double discountRate = 1.0;
    switch (starLevel) {
        case 5: discountRate = 0.70; break; // 五星级 70%
        case 4: discountRate = 0.80; break; // 四星级 80%
        case 3: discountRate = 0.85; break; // 三星级 85%
        case 2: discountRate = 0.90; break; // 二星级 90%
        case 1: discountRate = 0.95; break; // 一星级 95%
        default: break;
    }
    return originalPrice * discountRate;
}

void MemberCustomer::display() const {
    Customer::display();
    std::cout << ", 类型: 会员顾客, 星级: " << starLevel << "星";
}

std::string MemberCustomer::getTypeString() const {
    std::ostringstream oss;
    oss << "会员顾客(" << starLevel << "星)";
    return oss.str();
}

std::string MemberCustomer::getDiscountInfo() const {
    double rate = 1.0;
    // 根据星级确定实际收费比例的描述
    std::string description;
    switch (starLevel) {
        case 5: description = "按原价70%收费"; break;
        case 4: description = "按原价80%收费"; break;
        case 3: description = "按原价85%收费"; break;
        case 2: description = "按原价90%收费"; break;
        case 1: description = "按原价95%收费"; break;
        default: description = "无效星级"; break; // 理论上不会发生
    }
    return description;
}

