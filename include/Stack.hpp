#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct StackNode{
    T value;
    StackNode* next;
    StackNode(){
        next=nullptr;
    };
    StackNode(T value, StackNode* next = nullptr) : value(value), next(next) {}
};

template <typename T>
class Stack {
    private:
        StackNode<T>* top;
        int size;
    public:
        Stack(){
            top = nullptr;
            size = 0;
        }

        ~Stack(){
            StackNode<T>* cur = top;
            while(cur != nullptr){
                StackNode<T>* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }  
        
        void push(T value){
            StackNode<T>* newNode = new StackNode<T>(value, top);
            top = newNode;
            size++;
        }

        T pop(){
            if(isEmpty()){
                throw invalid_argument("Stack is empty");
            }
            StackNode<T>* temp = top;
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