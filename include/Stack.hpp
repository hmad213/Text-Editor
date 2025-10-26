#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T value;
    Node* next;

    Node(T value, Node* next = nullptr) : value(value), next(next), prev(prev) {}
};

template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;
public:
    Stack(){

    }

    ~Stack(){

    }

    void push(T value){

    }

    T pop(){

    }

    T peek(){

    }

    bool isEmpty(){return topNode == nullptr;}
    int getSize(){return size;}
};