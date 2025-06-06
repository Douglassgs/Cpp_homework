#ifndef MEMBER_CUSTOMER_HPP
#define MEMBER_CUSTOMER_HPP

#include "Customer.h++"

using namespace std;

class MemberCustomer : public Customer {
private:
    int starLevel;

public:
    MemberCustomer(const std::string& id = "", const std::string& name = "", int level = 1);

    int getStarLevel() const;
    double applyDiscount(double originalPrice) const override;
    void display() const override;
    std::string getTypeString() const override;
    std::string getDiscountInfo() const override;
};

#endif // MEMBER_CUSTOMER_HPP

