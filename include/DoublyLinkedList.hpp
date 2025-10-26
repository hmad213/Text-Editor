#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T value;
    Node* next;
    Node* prev;

    Node(T value, Node* next = nullptr, Node* prev = nullptr) : value(value), next(next), prev(prev) {}
};

template <typename T>
class DoublyLinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        DoublyLinkedList(){

        }

        ~DoublyLinkedList(){

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