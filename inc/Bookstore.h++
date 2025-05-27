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
#include <iostream>

using namespace std;

class Bookstore {
private:
    DynamicArray<Book> books;
    DynamicArray<Customer*> customers;
    DynamicArray<Order> orders;

    std::string booksFilename;
    std::string customersFilename;
    std::string ordersFilename;

    void loadBooksFromFile();
    void loadCustomersFromFile();
    void saveOrderToFile(const Order& order) const;

    void clearCustomers();

public:
    Bookstore(const std::string& booksFile, const std::string& customersFile, const std::string& ordersFile);
    ~Bookstore();

    Bookstore(const Bookstore&) = delete;
    Bookstore& operator=(const Bookstore&) = delete;

    void displayBooks() const;
    void displayCustomers() const;

    Book* findBookByIsbn(const std::string& isbn);
    Book* findBookByIndex(int index);
    Customer* findCustomerById(const std::string& customerId);
    Customer* findCustomerByIndex(int index);

    void run();
};

#endif // BOOKSTORE_HPP

