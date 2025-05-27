// inc/VIPCustomer.h++
#ifndef VIP_CUSTOMER_HPP
#define VIP_CUSTOMER_HPP

#include "Customer.h++"

using namespace std;

class VIPCustomer : public Customer {
private:
    double specialDiscountRate; // 特别折扣率 (例如 0.4 表示折扣40%，即按60%收费)

public:
    VIPCustomer(const std::string& id = "", const std::string& name = "", double discount = 0.0);

    double getSpecialDiscountRate() const;
    double applyDiscount(double originalPrice) const override;
    void display() const override;
    std::string getTypeString() const override;
    std::string getDiscountInfo() const override;
};

#endif // VIP_CUSTOMER_HPP

