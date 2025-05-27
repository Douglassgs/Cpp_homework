#include "Customer.h++"

using namespace std;

Customer::Customer(const std::string& id, const std::string& name)
    : customerId(id), name(name) {}

std::string Customer::getCustomerId() const {
    return customerId;
}

std::string Customer::getName() const {
    return name;
}

void Customer::display() const {
    std::cout << "顾客ID: " << customerId << ", 姓名: " << name;
}

