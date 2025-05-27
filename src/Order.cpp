// src/Order.cpp
#include "Order.h++"
#include <iostream>
#include <iomanip> // 用于 std::fixed, std::setprecision
#include <sstream> // 用于 std::ostringstream

// 初始化静态成员变量
int Order::nextOrderId = 1;

// 添加默认构造函数的实现
Order::Order()
    : orderId(nextOrderId++), customer(nullptr), originalTotalPrice(0.0), discountedTotalPrice(0.0) {
    // items (DynamicArray<OrderItem>) 成员会自动调用其默认构造函数
    // customer 初始化为 nullptr，表示此订单当前没有关联顾客
    // 价格初始化为0
    // orderId 像其他构造函数一样被分配
}

Order::Order(const Customer* cust)
    : customer(cust), originalTotalPrice(0.0), discountedTotalPrice(0.0) {
    if (!cust) {
        // 在实际应用中，这里应该抛出异常或有更健壮的错误处理
        std::cerr << "错误：订单尝试关联一个空顾客指针！" << std::endl;
        // 为简单起见，这里不立即中止，但customer将是nullptr，后续操作可能失败
    }
    orderId = nextOrderId++; // 分配唯一订单ID并递增
}

void Order::calculateTotals() {
    originalTotalPrice = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        originalTotalPrice += items[i].getTotalPrice();
    }
    if (customer) { // 确保顾客指针有效
        discountedTotalPrice = customer->applyDiscount(originalTotalPrice);
    } else {
        discountedTotalPrice = originalTotalPrice; // 如果顾客无效，则无折扣
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
    calculateTotals(); // 每次添加商品???重新计算总价
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

// 获取用于文件输出的订单摘要
// 格式: 订单ID,顾客ID,书籍ISBN:数量;书籍ISBN:数量...,原总价,折扣描述,实付总价
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

