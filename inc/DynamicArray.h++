// inc/DynamicArray.h++
#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <stdexcept> // 用于 std::out_of_range, std::bad_alloc
#include <cstddef>   // 用于 size_t

using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t count;    // 实际元素数量
    size_t capacity; // 已分配的内存大小

    void resize(size_t newCapacity) {
        if (newCapacity == 0) newCapacity = 1; // 确保容量至少为1
        T* newData = new T[newCapacity]; // 可能抛出 std::bad_alloc

        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[i]; // 假设 T 有可用的赋值运算符
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray(size_t initialCapacity = 10) : count(0), capacity(initialCapacity) {
        if (initialCapacity == 0) capacity = 1;
        data = new T[capacity]; // 可能抛出 std::bad_alloc
    }

    ~DynamicArray() {
        delete[] data;
    }

    // 拷贝构造函数
    DynamicArray(const DynamicArray& other) : count(other.count), capacity(other.capacity) {
        data = new T[capacity]; // 可能抛出 std::bad_alloc
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    // 拷贝赋值运算符
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data; // 释放旧资源

        count = other.count;
        capacity = other.capacity;
        data = new T[capacity]; // 可能抛出 std::bad_alloc
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    void add(const T& element) {
        if (count == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[count++] = element;
    }

    T& get(size_t index) {
        if (index >= count) {
            throw std::out_of_range("索引越界 (get())");
        }
        return data[index];
    }

    const T& get(size_t index) const {
        if (index >= count) {
            throw std::out_of_range("索引越界 (const get())");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= count) {
            // 对于 operator[]，有些人为了发布版本的性能更倾向于使用断言或未定义行为，
            // 但边界检查更安全。
            throw std::out_of_range("索引越界 (operator[])");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= count) {
            throw std::out_of_range("索引越界 (const operator[])");
        }
        return data[index];
    }

    size_t size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void clear() {
        // 这仅重置数量，不显式释放内存或调用所含对象的析构函数。
        // 如果 T 是原始指针，用户需要在调用 clear 前负责删除所指向的对象（如果需要）。
        // 如果 T 是对象，它们的析构函数不会在这里被调用，仅在 DynamicArray 被销毁或重新分配时调用。
        count = 0;
        // 可选：缩小容量：resize(初始容量_或_某个默认值);
    }
};

#endif // DYNAMIC_ARRAY_HPP
