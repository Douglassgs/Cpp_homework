// inc/MemberCustomer.h++
#ifndef MEMBER_CUSTOMER_HPP
#define MEMBER_CUSTOMER_HPP

#include "Customer.h++"

class MemberCustomer : public Customer {
private:
    int starLevel; // 会员星级 (1-5)

public:
    MemberCustomer(const std::string& id = "", const std::string& name = "", int level = 1);

    int getStarLevel() const;
    double applyDiscount(double originalPrice) const override;
    void display() const override;
    std::string getTypeString() const override;
    std::string getDiscountInfo() const override;
};

#endif // MEMBER_CUSTOMER_HPP

