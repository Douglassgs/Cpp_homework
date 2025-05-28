// main.cpp
#include "Bookstore.h++"
#include <iostream>
#include <fstream>

int main() {
    std::string booksFile = "./books.txt";
    std::string customersFile = "./customers.txt";
    std::string ordersFile = "./orders.txt";

    std::ofstream outFile;
    std::ifstream checkFile;

    checkFile.open(booksFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(booksFile.c_str());
        if (outFile.is_open()) {
            outFile << "9787111635626,C++ Primer Plus,Stephen Prata,99.00\n";
            outFile << "9787121374320,Effective C++,Scott Meyers,78.50\n";
            outFile << "9787030410243,算法导论,Thomas H. Cormen,128.00\n";
            outFile << "9787115495920,Python编程从入门到实践,Eric Matthes,89.00\n";
            outFile.close();
            std::cout << "示例 books.txt 已创建。" << std::endl;
        } else {
            std::cerr << "无法创建示例 books.txt。" << std::endl;
        }
    } else {
        checkFile.close();
    }

    checkFile.open(customersFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(customersFile.c_str());
        if (outFile.is_open()) {
            outFile << "R001,张三,Regular,0\n";
            outFile << "M001,李四,Member,5\n";
            outFile << "M002,赵敏,Member,3\n";
            outFile << "V001,王五,VIP,0.4\n";
            outFile << "R002,王二麻子,Regular,0\n";
            outFile.close();
            std::cout << "示例 customers.txt 已创建。" << std::endl;
        } else {
            std::cerr << "无法创建示例 customers.txt。" << std::endl;
        }
    } else {
        checkFile.close();
    }

    checkFile.open(ordersFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(ordersFile.c_str());
        if (outFile.is_open()) {
            std::cout << "空的 orders.txt 已创建。" << std::endl;
            outFile.close();
        } else {
             std::cerr << "无法创建 orders.txt。" << std::endl;
        }
    } else {
        checkFile.close();
    }

    Bookstore bookstore(booksFile, customersFile, ordersFile);
    bookstore.run();

    return 0;
}

