/*
Task#7:
Create a circular link list and perform the mentioned tasks.
a. Insert a new node at the end of the list.
b. Insert a new node at the beginning of list.
c. Insert a new node at given position.
d. Delete any node.
e. Print the complete circular link list*/
#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* head = nullptr;

void insertAtEnd(int value){
    Node* newNode= new Node();
    newNode->data = value;
    
    if(head==nullptr) 
    {
        head = newNode;
        newNode->next = head;
        return;
    }
    
    Node* temp = head;
    while(temp->next!= head){
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->next = head;
}

void insertAtBeginning(int value){
    Node *newNode = new Node();
    newNode->data = value;
    
    if(head == nullptr){

        head = newNode;
        newNode->next = head;   
        return;
    }
    Node* temp = head;
    while(temp->next!= head){
        temp = temp->next;
    }
    
    newNode->next = head;
    temp->next = newNode;
    head = newNode;
}

void insertAtPosition(int value, int position) 
{
    if(position<=0){
        cout << "Wow! what a position! This is not a coordinate system!; Invalid position entered." << endl;
        return;
    }   
    if(position == 1){
        insertAtBeginning(value);
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;
    Node* temp = head;
    for(int i=1; i<position-1 && temp->next!=head; i++) {
        temp= temp->next;
    }
    if(temp->next==head) {
        cout<<"OutOfBoundsException::Position " << endl;
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void printList() {
    if(head == nullptr) {
        cout<<"Void:Nothing in the list?"<<endl;
        return;
    }
    Node* temp= head;
    do 
    {
        cout << temp->data << "\n";
        temp = temp->next;
    } while(temp!= head);
    cout << endl;
}
void deleteNode(int value) 
{
    if(head == nullptr) 
    {
        cout<<"Empty list.. Do u want to enter?"<<endl;
        return;
    }   
    Node* current = head;
     Node* prev = nullptr;   
    do{
        if(current->data == value){
            if(prev == nullptr){
                if(head->next== head) {
                    delete head;

                    head = nullptr;
                    cout<<value<< " deleted and thrown to trash bin" << endl;
                     return;
                }
                Node* temp =
                 head;
                 while(temp->next!= head){
                    temp = temp->next;
                }

                temp->next = head->next;
                head = head->next;
                delete temp;
                cout<<value<< " deleted and thrown in dustbin"<< endl;
                return;

            } 
            else if(current->next == head){
                prev->next = head;
                delete current;
                cout<<value<<" deleted and thrown in public dustbin" << endl;
                return;
            } 
            else{
                prev->next = current->next;
                delete current;
                cout<<value << " thrown as a garbage and deleted" << endl;
                return;
            }
        }
        prev = current;
        current = current->next;
    } while(current != head);
    
    cout<<value << "Is this your age?; Not found in the list." << endl;
}   


int main() {
    int choice, value, position;
    do {
        cout<< "1. Insert at End\n2. Insert at Beginning\n3. Insert at Position\n4. Delete Node\n5. Print List\n6. Exit\n";
        cout<<"Enter your choice(1-6): ";
        cin>>choice;
        switch(choice) 
        {
            case 1:
                cout<<"Enter value to insert at end: ";
                cin>>value;
                insertAtEnd(value);
                break;
            case 2:
                cout<< "Enter value to insert at beginning: ";
                cin>>value;
                insertAtBeginning(value);
                break;
            case 3:
                cout<< "Enter value to insert: ";
                cin>>value;
                cout<< "Enter position to insert at: ";
                cin>> position;
                insertAtPosition(value, position);
                break;
            case 4:
                cout<< "Enter value to delete: ";
                cin>>value;
                deleteNode(value);
                break;
            case 5:
                printList();
                break;
            case 6:
                cout<< "Zipping Resources...\nThanks for using our program!(Now I can rest!)\nExiting..."<<endl;
                break;
            default:
                cout<< "Our software is not a game!; Invalid choice, try again." << endl;
        }
    } 
    while(choice!= 6);
    return 0;
}