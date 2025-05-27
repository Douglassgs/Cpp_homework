#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <stdexcept>
#include <cstddef>

using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t count;
    size_t capacity;

    void resize(size_t newCapacity) {
        if (newCapacity == 0) newCapacity = 1;
        T* newData = new T[newCapacity];

        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray(size_t initialCapacity = 10) : count(0), capacity(initialCapacity) {
        if (initialCapacity == 0) capacity = 1;
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) : count(other.count), capacity(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data;

        count = other.count;
        capacity = other.capacity;
        data = new T[capacity];
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
        count = 0;
    }
};

#endif // DYNAMIC_ARRAY_HPP
