#pragma once
#include <iostream>
#include <exception>
using namespace std;

template <typename T>
class DynamicArray{
private:
    T* arr;
    int capacity;
    int length;

    void resize() {
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        T* newArr = new T[newCap];

        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];

        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

public:
    DynamicArray() {
        arr = nullptr;
        capacity = 0;
        length = 0;
    }

    DynamicArray(int capacity) {
        if(capacity < 0) throw invalid_argument("Capacity must be greater than 0");
        arr = new int[capacity];
        this->capacity = capacity;
        length = capacity;
    }

    DynamicArray(DynamicArray& other){
        capacity = other.capacity;
        length = other.length;
        arr = new T[capacity];
        for(int i = 0; i < capacity; i++){
            arr[i] = other.arr[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (*this != other) {
            delete[] arr;
            arr = new T[other.capacity];
            capacity = other.capacity;
            length = other.length;
            for (int i = 0; i < capacity; i++)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void push_back(const T& value) {
        if (length == capacity)
            resize();

        arr[length] = value;
        length++;
    }

    void pop_back(){
        if (length > 0) length--;
    }

    T& operator[](int index) {
        if(index < 0 || index >= length) throw invalid_argument("Index not in range");
        return arr[index];
    }

    int size() const {
        return length;
    }
};