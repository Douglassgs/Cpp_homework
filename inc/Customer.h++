#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <iostream>

using namespace std;

class Order;

class Customer {
protected:
    string customerId;
    string name;

public:
    Customer(const string& id = "", const string& name = "");
    virtual ~Customer() = default;

    string getCustomerId() const;
    string getName() const;

    virtual double applyDiscount(double originalPrice) const = 0;

    virtual void display() const;

    virtual string getTypeString() const = 0;

    virtual string getDiscountInfo() const = 0;
};

#endif // CUSTOMER_HPP

