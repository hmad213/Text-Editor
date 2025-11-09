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
            
            if(index == 0){
                insertAtHead(value);
                return;
            }

            Node<T>* cur = head;
            int currentIndex = 0;
            
            while(cur != nullptr && currentIndex < index - 1){
                cur = cur->next;
                currentIndex++;
            }
            
            if(cur == nullptr) throw out_of_range("Index out of range");
            
            if(cur == tail){
                insertAtTail(value);
                return;
            }

            Node<T>* newNode = new Node<T>(value);
            newNode->next = cur->next;
            newNode->prev = cur;
            cur->next->prev = newNode;
            cur->next = newNode;
        }

        void removeFromHead(){
            if(head == nullptr) throw out_of_range("List is empty");
            
            Node<T>* temp = head;
            head = head->next;
            if(head == nullptr){
                tail = nullptr;
            }
            else{
                head->prev = nullptr;
            }
            delete temp;
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
        }

        void removeFromIndex(int index){
            if(index < 0) throw out_of_range("Negative index");
            
            if(index == 0){
                removeFromHead();
                return;
            }
            
            Node<T>* current = head;
            int currentIndex = 0;
            
            while(current != nullptr && currentIndex < index){
                current = current->next;
                currentIndex++;
            }
            
            if(current == nullptr) throw out_of_range("Index out of range");
            
            if(current == tail){
                removeFromTail();
                return;
            }
            
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }

        DoublyLinkedList<T> splitList(int index){
            
        }

        Node<T>* operator[](int index){
            if (index < 0) throw out_of_range("Negative index");

            Node<T>* ptr = head;
            int currentIndex = 0;
            while(ptr != nullptr && currentIndex < index){
                currentIndex++;
                ptr = ptr->next;
            }
            
            if(ptr == nullptr) return tail;
            return ptr;
        }

        bool isEmpty(){
            return head == nullptr;
        }

        int getSize(){
            int count = 0;
            Node<T>* current = head;
            while(current != nullptr){
                count++;
                current = current->next;
            }
            return count;
        }

        Node<T>* getHead(){
            return head;
        }

        Node<T>* getTail(){
            return tail;
        }

        Node<T>* insertAtNode(Node<T>* node, T value){
            if(node == tail || !node){ 
                insertAtTail(value);
                return tail;
            }
            
            Node<T>* newNode = new Node<T>(value);
            newNode->next = node->next;
            newNode->prev = node;
            node->next->prev = newNode;
            node->next = newNode;
            return newNode;
        }

        Node<T>* removeFromNode(Node<T>* node){
            if(node == nullptr) return nullptr;
            if(node == tail){
                removeFromTail();
                return tail;
            }

            if(node == head){
                removeFromHead();
                return nullptr;
            }

            Node<T>* temp = node->prev;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            return temp;
        }
};