#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T value;
    Node* next;

    Node(T value, Node* next = nullptr) : value(value), next(next) {}
};

template <typename T>
class Stack {
    private:
        Node<T>* top;
        int size;
    public:
        Stack(){
            top = nullptr;
            size = 0;
        }

        ~Stack(){
            Node<T>* cur = top;
            while(cur != nullptr){
                Node<T>* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }

        void push(T value){
            Node<T>* newNode = new Node<T>(value, top);
            top = newNode;
            size++;
        }

        T pop(){
            if(isEmpty()){
                throw out_of_range("Stack is empty");
            }
            
            Node<T>* temp = top;
            T value = top->value;
            top = top->next;
            delete temp;
            size--;
            
            return value;
        }

        T peek(){
            if(isEmpty()){
                throw out_of_range("Stack is empty");
            }
            return top->value;
        }

        bool isEmpty(){return top == nullptr;}
        int getSize(){return size;}
};