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
class LinkedList{
    private:
        Node<T>* head;
        int size;
    public:
        LinkedList(){

        }
        ~LinkedList(){

        }

        void insertAtHead(T value){

        }

        void insertAtTail(T value){

        }

        void insertAtIndex(T value){

        }

        void removeFromHead(){

        }

        void removeFromTail(){

        }

        void removeFromIndex(){

        }

        Node<T>* operator[](int index){

        }

        bool isEmpty(){

        }

        int getSize(){
            
        }
};