#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* createNode(int value)
 {
    Node *newNode = new Node();
    newNode->data= value;
    newNode->next = nullptr; 
     return newNode; // return the crested node
}

void printList(Node* head) 
{
     Node *temp = head;
    while (temp != nullptr) {
        cout<<temp->data << "\n";
        temp = temp->next;
    }
    
    cout << endl;
}

 Node* segregateEvenOdd(Node* head) 
{
    if(head== nullptr || head->next==nullptr) {return head;}
    
    Node*  evenStart = nullptr;
    Node*  evenEnd= nullptr;
    Node* oddStart = nullptr;
    Node* oddEnd=nullptr;
    Node* curr = head;
    while(curr!= nullptr){
        if(curr->data%2== 0){
            if(evenStart==nullptr){
                evenStart= curr;
                evenEnd =evenStart;
            } 
            else{
                evenEnd->next = curr;
                evenEnd = evenEnd->next;
            }
        } 
        else{
            if(oddStart== nullptr){
                oddStart =curr;
                oddEnd = oddStart;
            } 

            else{
                oddEnd->next = curr;
                oddEnd = oddEnd->next;
            }
        }

        curr = curr->next;
    }
    
    if (evenStart== nullptr)return oddStart;
    if (oddStart == nullptr) return evenStart;
    evenEnd->next = oddStart;

    oddEnd->next = nullptr;
    return evenStart;
}

int main(){

    Node* head = createNode(17);
    head->next = createNode(15);
    head->next->next = createNode(8);
    head->next->next->next = createNode(12);
    head->next->next->next->next = createNode(10);
    head->next->next->next->next->next = createNode(5);
    head->next->next->next->next->next->next = createNode(4);
    head->next->next->next->next->next->next->next = createNode(1);
    head->next->next->next->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->next->next->next->next = createNode(6);
    cout << "Input: ";
    printList(head);
    
    head = segregateEvenOdd(head);
    
    cout << "Output is: ";
    printList(head);
    
    return 0;
}