#include <iostream>
using namespace std;

template <typename T>
struct QueueNode{
    T value;
    QueueNode<T>* next;

    QueueNode(T value, QueueNode<T>* next = nullptr) : value(value), next(next) {}
};

template <typename T>
class Queue{
    private:
        QueueNode<T>* front;
        QueueNode<T>* rear;
    public:
        Queue(){
            front = nullptr;
            rear = nullptr;
        }

        ~Queue(){
            while(!isEmpty()) {
                dequeue();
            }
        }

        void enqueue(T value){
            QueueNode<T>* newNode = new QueueNode<T>(value);

            if(rear == nullptr){
                rear = newNode;
                front = newNode;
            }else{
                rear->next = newNode;
                rear = newNode;
            }
        }

        void dequeue(){
            if(isEmpty()) return;

            QueueNode<T>* temp = front;
            if(rear == front){
                rear = nullptr;
                front = nullptr;
            }else{
                front = front->next;
            }
            delete temp;
        }

        T peek(){
            if(isEmpty()) throw invalid_argument("Queue empty");

            return front->value;
        }

        bool isEmpty(){
            return front == nullptr;
        }
};