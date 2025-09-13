#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void printList(Node* head) 
{
    if (head == nullptr) return;
    cout<<endl;
    Node* temp = head;
    while (temp != nullptr){
        cout << temp->data << "\n";
        temp = temp->next;
    }
    cout << endl;
}

void insertAtEnd(Node* &head, int value){
    Node* newNode = new Node{value, nullptr};
    if (head == nullptr){
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtPosition(Node* &head, int value, int position){
    
    Node* newNode = new Node{value, nullptr};
    
    if (position == 1){
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    for (int i=1; i<position-1 && temp!= nullptr; i++){
        temp= temp->next;
    }
    if (temp ==nullptr)
    {
        cout << "Posution out of bounds!" <<endl;
       
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertAtFront(Node* &head, int value){
    Node* newNode = new Node{value, head};
      head = newNode;
}

void deleteNode(Node* &head, int value){
    if (head == nullptr) return;

    if (head->data == value){
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
     while (temp->next!= nullptr && temp->next->data!= value) 
    {
       temp=temp->next;
    }

    if (temp->next == nullptr) return;
    
    Node* nodeDelete=temp->next;
    temp->next =temp->next->next;
    delete nodeDelete;

}

int main(){
    int arr[] = {3, 1, 2, 5, 8};
    int size = 5;
    
    cout << "Our Given Array is: "<<endl;
    for (int i=0; i<size; i++){
        cout << arr[i] << "\n";
    }
    cout << endl;
    
    Node* head = nullptr;
    for (int i= 0; i<size; i++) 
    {
         insertAtEnd(head ,arr[i]);
    }
    
    insertAtEnd(head, 9);
    insertAtPosition(head, 11, 3);
    insertAtFront(head, 4);
    
    deleteNode(head, 1);
    deleteNode(head, 2);
    deleteNode(head, 5);
    insertAtEnd(head, 6);



    cout << "LINKED LIST: ";
   
     printList(head);
    /*delete head;
    delete head->next;
    delete head->next->next;
    delete head->next->next->next;
    delete head->next->next->next->next;
    delete head->next->next->next->next->next;
    delete head->next->next->next->next->next->next;
    delete head->next->next->next->next->next->next->next;  
    delete head->next->next->next->next->next->next->next->next;
    delete head->next->next->next->next->next->next->next->next->next;
    */

    return 0;
}