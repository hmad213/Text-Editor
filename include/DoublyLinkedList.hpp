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

        ~DoublyLinkedList(){
            Node<T>* cptr = head;
            while (cptr != nullptr) {
                Node<T>* temp = cptr;
                cptr = cptr->next;
                delete temp;
            }
        }

        void insertAtHead(T value){
            Node<T>* newNode = new Node<T>(value);
            size++;
            if(head == nullptr){
                head = newNode;
                tail = newNode;
                return;
            }

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        void insertAtTail(T value){
            Node<T>* newNode = new Node<T>(value);
            size++;
            if(tail == nullptr){
                head = newNode;
                tail = newNode;
                return;
            }

            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        void insertAtIndex(int index, T value){
            if(index < 0) throw out_of_range("Negative index");
            if(index > size) throw out_of_range("Index out of range");

            if(index == 0){
                insertAtHead(value);
                return;
            }
            if(index == size){
                insertAtTail(value);
                return;
            }

            Node<T>* cur = head;
            for(int i = 0; i < index - 1; i++){
                cur = cur->next;
            }

            Node<T>* newNode = new Node<T>(value);
            newNode->next = cur->next;
            newNode->prev = cur;
            current->next->prev = newNode;
            current->next = newNode;
            size++;
        }

        void removeFromHead(){
            if(head == nullptr) throw out_of_range("List is empty");
            
            Node<T>* temp = head;
            head = head->next;
            if(head == nullptr){
                tail = nullptr
            }
            else{
                head->prev = nullptr;
            }
            delete temp;
            size--;
        }

        void removeFromTail(){
            if(tail == nullptr) throw out_of_range("List is empty");
            
            Node<T>* temp = tail;
            tail = tail->prev;
            if(tail != nullptr){
                tail->next = nullptr;
            }
            else{
                head = nullptr;
            }
            delete temp;
            size--;
        }

        void removeFromIndex(int index){
            if(index < 0) throw out_of_range("Negative index");
            if(index >= size) throw out_of_range("Index out of range");
            
            if(index == 0){
                removeFromHead();
                return;
            }
            
            if(index == size - 1){
                removeFromTail();
                return;
            }
            
            Node<T>* current = head;
            for(int i = 0; i < index; i++){
                current = current->next;
            }
            
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size--;
        }

        DoublyLinkedList<T> splitList(int index){
            
        }

        Node<T>* operator[](int index){
            if (index < 0) throw out_of_range("Negative index");
            if(index > size) throw out_of_range("Index out of range");

            Node* ptr = head;
            int temp = 0;
            while(temp != index){
                temp++;
                ptr = ptr->next;
            }

            return ptr;
        }

        bool isEmpty(){
            return size == 0;
        }

        int getSize(){
            return size;
        }
};