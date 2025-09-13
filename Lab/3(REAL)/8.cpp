#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* head = nullptr;

void concatenateDoubleLinkedLists(Node* h1, Node* h2) {
    if (!h1){    h1 = h2;   return;}
    if (!h2){    return;}
    Node* tail1 = h1;
    while(tail1->next!= h1){
        tail1 = tail1->next;
    }
    Node* tail2=h2;
    while(tail2->next!= h2){
        tail2 = tail2->next;
    }

    tail1->next = h2;
    tail2->next = h1;
}

void printList(Node *head){
    if(head == nullptr){
        cout << "Nothing in the list!" << endl;
        return;
    }
    Node* temp = head;
    do{
        cout<<temp->data<<" ";
        temp= temp->next;
    } 
    while(temp!=head);
    cout<<endl;
}

int main(void){

    Node* h1 = new Node{1, nullptr};
    Node* s1 = new Node{2, nullptr};
    Node* t1 = new Node{3, nullptr};
    h1->next = s1; s1->next = t1; t1->next = h1;
    Node* h2 = new Node{4, nullptr};
    Node* s2 = new Node{5, nullptr};
    Node* t2 = new Node{6, nullptr};
    h2->next = s2; s2->next = t2; t2->next = h2; 
    cout << "List #1  before concatenate: ";
    printList(h1);
    cout << "List #2 before concetanate: ";
    printList(h2);
    concatenateDoubleLinkedLists(h1, h2);
    cout << "Merge List, After concatenate : ";
    printList(h1);
    return 0;
}