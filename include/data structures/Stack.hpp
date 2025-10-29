#pragma once
#include "DynamicArray.hpp"
class Stack{
    public:
    Node* head;
    Node* cptr;
    int count;
    Stack(){
        head=new Node();
        cptr= NULL;
        count=0;
    }
    void push(char a){
        if(count!=1){
            head->data=a;
            cptr= head;
            count=1;
        }
        else{
            cptr->next=new Node(a);
            cptr->next->prev=cptr;
            cptr=cptr->next;
        }
    }
    char pop(){
        if(cptr==head){
            count=0;
            char temp=cptr->data;
            cptr=NULL;
            return temp;
        }
        else{
            char temp=cptr->data;
            cptr=cptr->prev;
            delete cptr->next;
            cptr->next=nullptr;
            return temp;
        }
    }
    ~Stack(){
        delete head;
    }
};