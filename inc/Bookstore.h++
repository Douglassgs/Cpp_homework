// inc/Bookstore.h++
#ifndef BOOKSTORE_HPP
#define BOOKSTORE_HPP

#include "DynamicArray.h++"
#include "Book.h++"
#include "Customer.h++"
#include "RegularCustomer.h++"
#include "MemberCustomer.h++"
#include "VIPCustomer.h++"
#include "Order.h++"
#include <string>
#include <iostream> // 用于输出提示和错误信息

using namespace std;

class Bookstore {
private:
    DynamicArray<Book> books;
    DynamicArray<Customer*> customers; // 存储顾客对象的指针，以支持多态
    DynamicArray<Order> orders;      // 存储已完成的订单

    std::string booksFilename;
    std::string customersFilename;
    std::string ordersFilename;

    // 私有辅助方法
    void loadBooksFromFile();
    void loadCustomersFromFile();
    void saveOrdersToFile() const; // 保存所有已处理的订单
    void saveOrderToFile(const Order& order) const; // 追加单个订单到文件

    // 清理动态分配的顾客对象
    void clearCustomers();

public:
    Bookstore(const std::string& booksFile, const std::string& customersFile, const std::string& ordersFile);
    ~Bookstore();

    // 禁止拷贝构造和拷贝赋值，因为我们管理了裸指针 customers
    Bookstore(const Bookstore&) = delete;
    Bookstore& operator=(const Bookstore&) = delete;

    void displayBooks() const;
    void displayCustomers() const;

    Book* findBookByIsbn(const std::string& isbn); // 返回指针，允许修改或仅读取
    Book* findBookByIndex(int index);
    Customer* findCustomerById(const std::string& customerId); // 返回指针
    Customer* findCustomerByIndex(int index);

    // 运行主交互流程
    void run();
};

#endif // BOOKSTORE_HPP

