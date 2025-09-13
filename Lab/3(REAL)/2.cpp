#include <iostream>
using namespace std;

struct Node{
    int value;
    Node* next;
};

Node* makeNode(int val) 
{
    Node* n = new Node();
    n->value = val;
    n->next= nullptr;
    return n;

}

void displayList(Node* start ) 
{
    if (start == nullptr) return;
    cout << endl;
    Node* curr = start;
    while (curr!= nullptr) 
    {
        cout << curr->value << "\n";
        curr = curr->next;
    }
    cout << endl;
}

Node* shiftElements(Node* start , int count){
    if (start == nullptr || count == 0) {return start;}
    Node* marker = start;
    Node* tail = start;
    
    for (int i= 1; i<count && marker!= nullptr; i++){
        marker = marker->next;
    }
    
    if (marker==nullptr || marker->next== nullptr){
        
        return start;
    }
    
    while(tail->next!= nullptr){
        tail = tail->next;
    }
    
    Node *newStart = marker->next;
    marker->next= nullptr;
    tail->next = start;
    return newStart;

}

int main(){

    Node* first = makeNode(5);
    first->next = makeNode(3);
    first->next->next = makeNode(1);
    first->next->next->next = makeNode(8);
    first->next->next->next->next = makeNode(6);
    first->next->next->next->next->next = makeNode(4);
    first->next->next->next->next->next->next = makeNode(2);
    
    cout<<"list at strt:  ";
    displayList(first);
    int number;
    cout << "Enter number of elements for shifting: ";
    cin >> number;
    
    first = shiftElements(first, number);
    
    cout << "Modified list: ";
    displayList(first);
    
    return 0;
}