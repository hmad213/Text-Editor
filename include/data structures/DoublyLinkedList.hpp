#include <iostream>
using namespace std;

class Node{
    public:
    char data;
    Node* fpoint;
    Node* bpoint;
     Node(){
        data= NULL;
        fpoint=bpoint=nullptr;
    }
    Node(char a){
        data= a;
        fpoint=bpoint=nullptr;
    }
};
class doublylinkedlist{
    public:
    Node* head;
    Node* tail;
    doublylinkedlist(){
        head=tail=nullptr;
    }
    doublylinkedlist(Node* a){
        head=a;
        tail=nullptr;
    }
};