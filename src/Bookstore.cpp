// src/Bookstore.cpp
#include "Bookstore.h++"
#include <fstream>      // 用于文件读写
#include <sstream>      // 用于字符串解析
#include <limits>       // 用于 std::numeric_limits
#include <stdexcept>    // 用于 std::invalid_argument, std::stod, std::stoi
#include <algorithm>    // 用于 std::remove for string manipulation

// 辅助函数：去除字符串两端的空白字符
std::string trim(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return ""; // 全是空白
    }
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, (end - start + 1));
}

Bookstore::Bookstore(const std::string& booksFile, const std::string& customersFile, const std::string& ordersFile)
    : booksFilename(booksFile), customersFilename(customersFile), ordersFilename(ordersFile) {
    loadBooksFromFile();
    loadCustomersFromFile();
    // 订单通常在程序运行过程中创建并保存，启动时可能不需要加载旧订单到内存中进行操作，
    // 而是直接追加新订单到文件。如果需要加载历史订单，可以添加 loadOrdersFromFile()。
}

Bookstore::~Bookstore() {
    clearCustomers(); // 清理动态分配的顾客对象
    // saveOrdersToFile(); // 可以在析构时保存所有订单，或者在每次订单完成后保存
}

void Bookstore::clearCustomers() {
    for (size_t i = 0; i < customers.size(); ++i) {
        delete customers[i]; // 删除 Customer 对象
    }
    customers.clear(); // 清空数组
}

void Bookstore::loadBooksFromFile() {
    std::ifstream inFile(booksFilename.c_str()); // 使用 .c_str() 以兼容旧版C++标准
    if (!inFile) {
        std::cerr << "错误: 无法打开书籍文件 " << booksFilename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        line = trim(line);
        if (line.empty()) continue; // 跳过空行

        std::stringstream ss(line);
        std::string isbn, title, author, priceStr;

        std::getline(ss, isbn, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, priceStr, ',');

        isbn = trim(isbn);
        title = trim(title);
        author = trim(author);
        priceStr = trim(priceStr);

        if (isbn.empty() || title.empty() || author.empty() || priceStr.empty()) {
            std::cerr << "警告: 书籍文件行格式错误 (字段缺失): " << line << std::endl;
            continue;
        }

        try {
            double price = std::stod(priceStr); // std::stod 在 <string>
            books.add(Book(isbn, title, author, price));
        } catch (const std::invalid_argument& ia) {
            std::cerr << "警告: 书籍价格格式无效: " << priceStr << " 在行: " << line << std::endl;
        } catch (const std::out_of_range& oor) {
            std::cerr << "警告: 书籍价格超出范围: " << priceStr << " 在行: " << line << std::endl;
        }
    }
    inFile.close();
    std::cout << books.size() << " 本书籍信息已加载。" << std::endl;
}

void Bookstore::loadCustomersFromFile() {
    std::ifstream inFile(customersFilename.c_str());
    if (!inFile) {
        std::cerr << "错误: 无法打开顾客文件 " << customersFilename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        line = trim(line);
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, name, type, attributeStr;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, type, ',');
        std::getline(ss, attributeStr, ','); // 可能为空或包含特定属性

        id = trim(id);
        name = trim(name);
        type = trim(type);
        attributeStr = trim(attributeStr);

        if (id.empty() || name.empty() || type.empty()) {
            std::cerr << "警告: 顾客文件行格式错误 (字段缺失): " << line << std::endl;
            continue;
        }

        Customer* customer = nullptr;
        try {
            if (type == "Regular") {
                customer = new RegularCustomer(id, name);
            } else if (type == "Member") {
                int level = std::stoi(attributeStr); // std::stoi 在 <string>
                customer = new MemberCustomer(id, name, level);
            } else if (type == "VIP") {
                double discount = std::stod(attributeStr);
                customer = new VIPCustomer(id, name, discount);
            } else {
                std::cerr << "警告: 未知的顾客类型: " << type << " 在行: " << line << std::endl;
                continue;
            }
            customers.add(customer);
        } catch (const std::invalid_argument& ia) {
            std::cerr << "警告: 顾客属性格式无效: " << attributeStr << " 对于类型 " << type << " 在行: " << line << std::endl;
            if(customer) delete customer; // 如果部分创建失败，清理
        } catch (const std::out_of_range& oor) {
            std::cerr << "警告: 顾客属性超出范围: " << attributeStr << " 对于类型 " << type << " 在行: " << line << std::endl;
            if(customer) delete customer;
        }
    }
    inFile.close();
    std::cout << customers.size() << " 位顾客信息已加载。" << std::endl;
}

void Bookstore::saveOrderToFile(const Order& order) const {
    // 以追加模式打开文件
    std::ofstream outFile(ordersFilename.c_str(), std::ios::app);
    if (!outFile) {
        std::cerr << "错误: 无法打开订单文件 " << ordersFilename << " 进行写入。" << std::endl;
        return;
    }
    outFile << order.getOrderSummaryForFile() << std::endl;
    outFile.close();
}

// 如果需要一次性保存所有内存中的订单 (当前设计是逐个保存)
void Bookstore::saveOrdersToFile() const {
    std::ofstream outFile(ordersFilename.c_str()); // 会覆盖旧文件
    if (!outFile) {
        std::cerr << "错误: 无法打开订单文件 " << ordersFilename << " 进行写入。" << std::endl;
        return;
    }
    for (size_t i = 0; i < orders.size(); ++i) {
        outFile << orders[i].getOrderSummaryForFile() << std::endl;
    }
    outFile.close();
    std::cout << orders.size() << " 条订单已保存到 " << ordersFilename << std::endl;
}

void Bookstore::displayBooks() const {
    std::cout << "\n-------------------- 书籍列表 --------------------" << std::endl;
    if (books.isEmpty()) {
        std::cout << "书库中没有书籍。" << std::endl;
    } else {
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << i + 1 << ". ";
            books[i].display();
            std::cout << std::endl;
        }
    }
    std::cout << "--------------------------------------------------\n" << std::endl;
}

void Bookstore::displayCustomers() const {
    std::cout << "\n-------------------- 顾客列表 --------------------" << std::endl;
    if (customers.isEmpty()) {
        std::cout << "系统中没有顾客信息。" << std::endl;
    } else {
        for (size_t i = 0; i < customers.size(); ++i) {
            std::cout << i + 1 << ". ";
            customers[i]->display(); // 通过指针调用虚函数
            std::cout << std::endl;
        }
    }
    std::cout << "--------------------------------------------------\n" << std::endl;
}

Book* Bookstore::findBookByIsbn(const std::string& isbn) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getIsbn() == isbn) {
            return &books[i]; // 返回指向数组中对象的指针
        }
    }
    return nullptr; // 未找到
}

Book* Bookstore::findBookByIndex(int index) {
    if (index >= 0 && static_cast<size_t>(index) < books.size()) {
        return &books[static_cast<size_t>(index)];
    }
    return nullptr;
}

Customer* Bookstore::findCustomerById(const std::string& customerId) {
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i]->getCustomerId() == customerId) {
            return customers[i]; // 返回存储的指针
        }
    }
    return nullptr; // 未找到
}

Customer* Bookstore::findCustomerByIndex(int index) {
    if (index >= 0 && static_cast<size_t>(index) < customers.size()) {
        return customers[static_cast<size_t>(index)];
    }
    return nullptr;
}

void Bookstore::run() {
    std::cout << "欢迎来到网上购书结账系统!" << std::endl;
    bool running = true;
    while (running) {
        std::cout << "\n请选择操作:" << std::endl;
        std::cout << "1. 显示所有书籍" << std::endl;
        std::cout << "2. 显示所有顾客" << std::endl;
        std::cout << "3. 开始新的订单" << std::endl;
        std::cout << "0. 退出" << std::endl; // 修改退出选项
        std::cout << "请输入选项 (0-3): "; // 修改提示

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入数字。" << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) { // 修改退出条件
            running = false;
            std::cout << "感谢使用，再见!" << std::endl;
            break;
        }

        switch (choice) {
            case 1: {
                displayBooks();
                break;
            }
            case 2: {
                displayCustomers();
                break;
            }
            case 3: {
                if (customers.isEmpty()) {
                    std::cout << "系统中没有顾客信息，无法创建订单。请先添加顾客。" << std::endl;
                    break;
                }
                displayCustomers();
                std::cout << "请输入顾客序号以选择顾客 (输入 0 返回主菜单): ";
                int customerIndexInput;
                std::cin >> customerIndexInput;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "输入无效，请输入数字。" << std::endl;
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (customerIndexInput == 0) {
                    break;
                }

                Customer* selectedCustomer = findCustomerByIndex(customerIndexInput - 1); // 序号转索引
                if (!selectedCustomer) {
                    std::cout << "未找到序号为 " << customerIndexInput << " 的顾客。" << std::endl;
                    break;
                }

                std::cout << "已选择顾客: ";
                selectedCustomer->display();
                std::cout << std::endl;

                Order newOrder(selectedCustomer);
                bool addingBooks = true;
                while (addingBooks) {
                    displayBooks();
                    std::cout << "请输入要购买的书籍序号 (输入 0 完成订单): ";
                    int bookIndexInput;
                    std::cin >> bookIndexInput;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "输入无效，请输入数字。" << std::endl;
                        continue;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (bookIndexInput == 0) {
                        addingBooks = false;
                        break;
                    }

                    Book* selectedBook = findBookByIndex(bookIndexInput - 1); // 序号转索引
                    if (!selectedBook) {
                        std::cout << "未找到序号为 " << bookIndexInput << " 的书籍。" << std::endl;
                        continue;
                    }

                    std::cout << "请输入购买数量: ";
                    int quantity;
                    std::cin >> quantity;
                    if (std::cin.fail() || quantity < 1) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "数量无效，请输入一个正整数。" << std::endl;
                        continue;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    newOrder.addItem(OrderItem(*selectedBook, quantity));
                    std::cout << "已添加: " << selectedBook->getTitle() << " x" << quantity << std::endl;
                    newOrder.displayOrderDetails();

                    // 购买后不直接退出到书籍列表，询问是否继续添加
                    std::cout << "是否继续添加其他书籍到当前订单? (y/n，输入0完成订单): ";
                    char continueChoice;
                    std::cin >> continueChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (continueChoice == '0') {
                        addingBooks = false;
                    } else if (continueChoice == 'n' || continueChoice == 'N') {
                        addingBooks = false;
                    } else if (continueChoice == 'y' || continueChoice == 'Y') {
                        // 继续循环添加书籍
                    } else {
                        std::cout << "无效输入，默认继续添加书籍。" << std::endl;
                    }
                }

                if (newOrder.getItems().isEmpty()) {
                    std::cout << "订单为空，未进行任何操作。" << std::endl;
                } else {
                    std::cout << "\n当前订单详情:" << std::endl;
                    newOrder.displayOrderDetails();
                    std::cout << "确认购买以上商品吗? (y/n，输入0取消订单): ";
                    char confirmChoice;
                    std::cin >> confirmChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (confirmChoice == '0' || confirmChoice == 'n' || confirmChoice == 'N') {
                        std::cout << "订单已取消。" << std::endl;
                    } else if (confirmChoice == 'y' || confirmChoice == 'Y') {
                        orders.add(newOrder);
                        saveOrderToFile(newOrder);
                        std::cout << "订单 " << newOrder.getOrderId() << " 已确认并保存。" << std::endl;
                    } else {
                        std::cout << "无效输入，订单已取消。" << std::endl;
                    }
                }
                break;
            }
            // case 4 was removed due to exit condition change
            default: {
                std::cout << "无效选项，请输入0-3之间的数字。" << std::endl; // 更新提示
                break;
            }
        }
    }
}
