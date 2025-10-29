#include <iostream>
using namespace std;

class Node{
    public:
    char data;
    Node* next;
    Node* prev;
     Node(){
        data= NULL;
        next=prev=nullptr;
    }
    Node(char a){
        data=a;
        next=prev=nullptr;
    }
};
//Logic assumed in Doubly Linked List that cptr (current pointer) will be maintained to address the curent position of cursor
//I have made insert and delete function at specific positon enteries, as they might be useful (which dosen't seems as so atm)
class doublylinkedlist{
    public:
    Node* head;
    Node* tail;
    Node* cptr;
    doublylinkedlist(){
        head=tail=cptr=nullptr;
    }
    doublylinkedlist(Node* a){
        head=a;
        cptr=head;
        tail=head;
    }
    void insert(char a){
        Node* temp=new Node(a);
        cptr->next=temp;
        temp->prev=cptr;
        cptr=temp;
        tail=cptr;
    }
    //size calculator
    int size(){
        Node* ptr=head;
        int temp=1;
        while(ptr!=nullptr){
            temp++;
            ptr=ptr->next;
        }
        return temp;
    }
    //used for setting position of the ptr
    Node* setpos(int a){
        Node* ptr=head;
        int temp=1;
        while(temp!=a){
            temp++;
            ptr=ptr->next;
        }
        return ptr;
    }
    void insert(char a, int b){
        cptr=setpos(b);
        Node* temp=new Node(a);
        cptr->next=temp;
        temp->prev=cptr;
        cptr=temp;
    }
    void del(){
        cptr=cptr->prev;
        tail=cptr;
        delete cptr->next;
    }
    void del(int a){
        cptr=setpos(a);
        cptr=cptr->prev;
        tail=cptr;
        delete cptr->next;
    }
~doublylinkedlist(){
    cptr=tail;
    while(cptr!=head){
        cptr=cptr->prev;
        delete cptr->next;
    }
    delete cptr;
    }
};
