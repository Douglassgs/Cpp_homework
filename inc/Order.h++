// inc/Order.h++
#ifndef ORDER_HPP
#define ORDER_HPP

#include "Customer.h++" // 需要顾客信息
#include "OrderItem.h++"  // 订单项
#include "DynamicArray.h++" // 使用自定义的动态数组
#include <string>
#include <iostream> // 用于显示
#include <iomanip>  // 用于 std::fixed, std::setprecision
#include <sstream>  // 用于 getOrderSummaryForFile

class Order {
private:
    static int nextOrderId; // 用于生成唯一的订单ID
    int orderId;
    const Customer* customer; // 指向顾客对象的指针，不拥有该对象
    DynamicArray<OrderItem> items; // 存储订单项的动态数组
    double originalTotalPrice; // 折扣前总价
    double discountedTotalPrice; // 折扣后总价

    void calculateTotals(); // 私有辅助函数，用于计算总价

public:
    Order(); // 默认构造函数
    // 构造函数，顾客指针不能为空
    Order(const Customer* cust);
    // 订单类不应负责删除顾客指针，顾客对象的生命周期由Bookstore管理

    int getOrderId() const;
    const Customer* getCustomer() const;
    const DynamicArray<OrderItem>& getItems() const; // 返回对items的常量引用
    double getOriginalTotalPrice() const;
    double getDiscountedTotalPrice() const;

    void addItem(const OrderItem& item);

    void displayOrderDetails() const;
    std::string getOrderSummaryForFile() const; // 获取用于文件输出的订单摘要
};

#endif // ORDER_HPP

