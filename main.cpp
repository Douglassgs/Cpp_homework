// main.cpp
#include "Bookstore.h++"
#include <iostream>
#include <fstream> // 用于文件检查和创建

int main() {
    // 定义数据文件名
    // 确保这些文件与可执行文件在同一目录，或者提供完整/相对路径
    // 为了简单起见，我们假设它们在程序的工作目录下
    std::string booksFile = "books.txt";
    std::string customersFile = "customers.txt";
    std::string ordersFile = "orders.txt";

    // 准备一些示例数据文件，如果它们不存在的话
    std::ofstream outFile;
    std::ifstream checkFile;

    // 检查并创建 books.txt (如果不存在)
    checkFile.open(booksFile.c_str());
    if (!checkFile.good()) {
        checkFile.close(); // 关闭检查流
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

    // 检查并创建 customers.txt (如果不存在)
    checkFile.open(customersFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(customersFile.c_str());
        if (outFile.is_open()) {
            outFile << "R001,张三,Regular,0\n";
            outFile << "M001,李四,Member,5\n"; // 5星会员
            outFile << "M002,赵敏,Member,3\n"; // 3星会员
            outFile << "V001,王五,VIP,0.4\n";   // 40%折扣 (即按60%收费)
            outFile << "R002,周芷若,Regular,0\n";
            outFile.close();
            std::cout << "示例 customers.txt 已创建。" << std::endl;
        } else {
            std::cerr << "无法创建示例 customers.txt。" << std::endl;
        }
    } else {
        checkFile.close();
    }

    // 创建空的 orders.txt (如果不存在)
    // 当前设计是追加订单，所以如果文件不存在，首次运行时会自动创建。
    checkFile.open(ordersFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(ordersFile.c_str()); // 创建空文件
        if (outFile.is_open()) {
            std::cout << "空的 orders.txt 已创建 (如果之前不存在)。" << std::endl;
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

