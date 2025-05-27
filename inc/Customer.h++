// inc/Customer.h++
#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <iostream> // 用于std::ostream

using namespace std;

// 前向声明，避免循环依赖
class Order;

class Customer {
protected:
    string customerId;
    string name;

public:
    Customer(const string& id = "", const string& name = "");
    virtual ~Customer() = default; // 虚析构函数，确保派生类对象正确销毁

    string getCustomerId() const;
    string getName() const;

    // 纯虚函数，用于计算折扣后的价格
    // 参数：原始总价
    // 返回：折扣后的价格
    virtual double applyDiscount(double originalPrice) const = 0;

    // 虚函数，用于显示顾客信息，派生类可以覆盖以显示特定信息
    virtual void display() const;

    // 获取顾客类型描述，用于订单输出等
    virtual string getTypeString() const = 0;

    // 获取折扣描述，用于订单输出
    virtual string getDiscountInfo() const = 0;
};

#endif // CUSTOMER_HPP

