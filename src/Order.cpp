// src/Order.cpp
#include "Order.h++"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int Order::nextOrderId = 1;

Order::Order()
    : orderId(nextOrderId++), customer(nullptr), originalTotalPrice(0.0), discountedTotalPrice(0.0) {
}

Order::Order(const Customer* cust)
    : customer(cust), originalTotalPrice(0.0), discountedTotalPrice(0.0) {
    if (!cust) {
        std::cerr << "错误：订单尝试关联一个空顾客指针！" << std::endl;
    }
    orderId = nextOrderId++;
}

void Order::calculateTotals() {
    originalTotalPrice = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        originalTotalPrice += items[i].getTotalPrice();
    }
    if (customer) {
        discountedTotalPrice = customer->applyDiscount(originalTotalPrice);
    } else {
        discountedTotalPrice = originalTotalPrice;
    }
}

int Order::getOrderId() const {
    return orderId;
}

const Customer* Order::getCustomer() const {
    return customer;
}

const DynamicArray<OrderItem>& Order::getItems() const {
    return items;
}

double Order::getOriginalTotalPrice() const {
    return originalTotalPrice;
}

double Order::getDiscountedTotalPrice() const {
    return discountedTotalPrice;
}

void Order::addItem(const OrderItem& item) {
    items.add(item);
    calculateTotals();
}

void Order::displayOrderDetails() const {
    std::cout << "\n-------------------- 订单详情 --------------------" << std::endl;
    std::cout << "订单ID: " << orderId << std::endl;
    if (customer) {
        std::cout << "顾客: " << customer->getName() << " (" << customer->getCustomerId() << ") - " << customer->getTypeString() << std::endl;
        std::cout << "折扣信息: " << customer->getDiscountInfo() << std::endl;
    } else {
        std::cout << "顾客: 信息无效" << std::endl;
    }
    std::cout << "\n订单项目:" << std::endl;
    if (items.isEmpty()) {
        std::cout << "  (订单为空)" << std::endl;
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "  " << i + 1 << ". ";
            items[i].display();
            std::cout << std::endl;
        }
    }
    std::cout << "\n原总价: " << std::fixed << std::setprecision(2) << originalTotalPrice << "元" << std::endl;
    std::cout << "折扣后总价 (应付金额): " << std::fixed << std::setprecision(2) << discountedTotalPrice << "元" << std::endl;
    std::cout << "--------------------------------------------------\n" << std::endl;
}

std::string Order::getOrderSummaryForFile() const {
    std::ostringstream oss;
    oss << orderId << ",";
    if (customer) {
        oss << customer->getCustomerId() << ",";
    } else {
        oss << "UNKNOWN_CUSTOMER_ID" << ",";
    }

    for (size_t i = 0; i < items.size(); ++i) {
        oss << items[i].getBook().getIsbn() << ":" << items[i].getQuantity();
        if (i < items.size() - 1) {
            oss << ";";
        }
    }
    oss << ",";

    oss << std::fixed << std::setprecision(2) << originalTotalPrice << ",";
    if (customer) {
        oss << customer->getDiscountInfo() << ",";
    } else {
        oss << "无折扣信息" << ",";
    }
    oss << std::fixed << std::setprecision(2) << discountedTotalPrice;

    return oss.str();
}

