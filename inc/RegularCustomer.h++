// inc/RegularCustomer.h++
#ifndef REGULAR_CUSTOMER_HPP
#define REGULAR_CUSTOMER_HPP

#include "Customer.h++"

using namespace std;

class RegularCustomer : public Customer {
public:
    RegularCustomer(const std::string& id = "", const std::string& name = "");

    double applyDiscount(double originalPrice) const override;
    void display() const override;
    std::string getTypeString() const override;
    std::string getDiscountInfo() const override;
};

#endif // REGULAR_CUSTOMER_HPP

