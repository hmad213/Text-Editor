#pragma once
#include <iostream>
using namespace std;

struct Operation{
    char letter;
    int nodepos;
    int linepos;
    Operation(){};
    Operation(char a, int b, int c):letter(a),nodepos(b),linepos(c){}
};
template <typename T>
struct Nodes{
    T value;
    Nodes* next;
    Nodes(){
        next=nullptr;
    };
    Nodes(T value, Nodes* next = nullptr) : value(value), next(next) {}
};

template <typename T>
class Stack {
    private:
        Nodes<T>* top;
        int size;
    public:
        Stack(){
            top = nullptr;
            size = 0;
        }

        ~Stack(){
            Nodes<T>* cur = top;
            while(cur != nullptr){
                Nodes<T>* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }  
        
        void push(T value){
            Nodes<T>* newNode = new Nodes<T>(value, top);
            top = newNode;
            size++;
        }

        Nodes<T>* pop(){
            if(isEmpty()){
                return new Nodes<T>();
            }
            Nodes<T>* temp = top;
            T value = top->value;
            top = top->next;
            //delete temp;
            size--;
            return temp;
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