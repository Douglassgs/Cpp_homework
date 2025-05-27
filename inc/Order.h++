#ifndef ORDER_HPP
#define ORDER_HPP

#include "Customer.h++"
#include "OrderItem.h++"
#include "DynamicArray.h++"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Order {
private:
    static int nextOrderId;
    int orderId;
    const Customer* customer;
    DynamicArray<OrderItem> items;
    double originalTotalPrice;
    double discountedTotalPrice;

    void calculateTotals();

public:
    Order();
    Order(const Customer* cust);

    int getOrderId() const;
    const Customer* getCustomer() const;
    const DynamicArray<OrderItem>& getItems() const;
    double getOriginalTotalPrice() const;
    double getDiscountedTotalPrice() const;

    void addItem(const OrderItem& item);

    void displayOrderDetails() const;
    string getOrderSummaryForFile() const;
};

#endif // ORDER_HPP

