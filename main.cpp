// main.cpp
#include "Bookstore.h++"
#include <iostream>
#include <fstream> // �����ļ����ʹ���

int main() {
    // ���������ļ���
    // ȷ����Щ�ļ����ִ���ļ���ͬһĿ¼�������ṩ����/���·��
    // Ϊ�˼���������Ǽ��������ڳ���Ĺ���Ŀ¼��
    std::string booksFile = "books.txt";
    std::string customersFile = "customers.txt";
    std::string ordersFile = "orders.txt";

    // ׼��һЩʾ�������ļ���������ǲ����ڵĻ�
    std::ofstream outFile;
    std::ifstream checkFile;

    // ��鲢���� books.txt (���������)
    checkFile.open(booksFile.c_str());
    if (!checkFile.good()) {
        checkFile.close(); // �رռ����
        outFile.open(booksFile.c_str());
        if (outFile.is_open()) {
            outFile << "9787111635626,C++ Primer Plus,Stephen Prata,99.00\n";
            outFile << "9787121374320,Effective C++,Scott Meyers,78.50\n";
            outFile << "9787030410243,�㷨����,Thomas H. Cormen,128.00\n";
            outFile << "9787115495920,Python��̴����ŵ�ʵ��,Eric Matthes,89.00\n";
            outFile.close();
            std::cout << "ʾ�� books.txt �Ѵ�����" << std::endl;
        } else {
            std::cerr << "�޷�����ʾ�� books.txt��" << std::endl;
        }
    } else {
        checkFile.close();
    }

    // ��鲢���� customers.txt (���������)
    checkFile.open(customersFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(customersFile.c_str());
        if (outFile.is_open()) {
            outFile << "R001,����,Regular,0\n";
            outFile << "M001,����,Member,5\n"; // 5�ǻ�Ա
            outFile << "M002,����,Member,3\n"; // 3�ǻ�Ա
            outFile << "V001,����,VIP,0.4\n";   // 40%�ۿ� (����60%�շ�)
            outFile << "R002,������,Regular,0\n";
            outFile.close();
            std::cout << "ʾ�� customers.txt �Ѵ�����" << std::endl;
        } else {
            std::cerr << "�޷�����ʾ�� customers.txt��" << std::endl;
        }
    } else {
        checkFile.close();
    }

    // �����յ� orders.txt (���������)
    // ��ǰ�����׷�Ӷ�������������ļ������ڣ��״�����ʱ���Զ�������
    checkFile.open(ordersFile.c_str());
    if (!checkFile.good()) {
        checkFile.close();
        outFile.open(ordersFile.c_str()); // �������ļ�
        if (outFile.is_open()) {
            std::cout << "�յ� orders.txt �Ѵ��� (���֮ǰ������)��" << std::endl;
            outFile.close();
        } else {
             std::cerr << "�޷����� orders.txt��" << std::endl;
        }
    } else {
        checkFile.close();
    }


    Bookstore bookstore(booksFile, customersFile, ordersFile);
    bookstore.run();

    return 0;
}

