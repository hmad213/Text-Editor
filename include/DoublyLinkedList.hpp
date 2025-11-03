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
            head = nullptr;
            tail = nullptr;
        }

        DoublyLinkedList(Node<T>* a){
            head = a;
            tail = head;
        }

        ~DoublyLinkedList(){
            Node<T>* cptr = head;
            while (cptr != nullptr) {
                Node<T>* temp = cptr;
                cptr = cptr->next;
                delete temp;
            }
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

        DoublyLinkedList<T> splitList(int index){
            
        }

        // This is the setpos function. Made for more efficiency
        Node<T>* operator[](int index){
            if (index < 0) throw out_of_range("Negative index");
            Node* ptr = head;
            int temp = 0;
            while(temp != index){
                temp++;
                ptr = ptr->next;
            }

            if (ptr == nullptr)
                throw std::out_of_range("Index out of range");

            return ptr;
        }

        bool isEmpty(){
            return size == 0;
        }

        int getSize(){
            return size;
        }
};