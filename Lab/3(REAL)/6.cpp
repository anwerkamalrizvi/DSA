#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* createNode(int value){
   
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

void printList(Node* head) 
{

     Node* temp = head;
    while(temp != nullptr){
        cout<<temp->data<<"\n";
        temp= temp->next;
    }
    cout<<endl;
}

void deleteValue(Node* &head, int value){
    if(head== nullptr){
        cout << "Empty Air Deleted!!; List is empty how can I delete?" << value << endl;
        return;
    }
    
    if(head->data == value){
        Node* temp = head;
        head = head->next;
        delete temp;
        cout<< value<< " deleted and thrown in trash bin\n";
        return;
    }
    
    Node *current = head;
    Node* prev= nullptr;
    
    while(current!=nullptr && current->data!= value) {
        prev = current;
         current = current->next;
    }
    
    if(current == nullptr){
        cout<<value<< " maybe is your lucky number?; not exists in the list!" << endl;
        return;
    }
   //  prev->data = current->data;
     prev->next = current->next;
    delete current;
    cout<<value<< " deleted and moved to recycle bin. " << endl;
}

int main(){
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);
    cout<<"Original and Genuine list: ";
    printList(head);
    int valueToDelete;
    cout<< "Enter a value to delete: ";
    cin>>valueToDelete;
    deleteValue(head, valueToDelete);
    cout<<"new Updated list: ";
    printList(head);
    return 0;
}