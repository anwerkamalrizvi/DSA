#include <iostream>
  #include <string>
  using namespace std;

  struct Node{
      string data;
      Node* next;
  };

  Node* createNode(string value){
      Node*  newNode = new Node;
      
      newNode->data = value;
      newNode->next = nullptr;
      return newNode;
  }

Node* reverse(Node* head) 
{
      Node* prev = nullptr;
      Node* current = head;
      while (current!= nullptr) {
          Node* next = current->next;
          current->next = prev;
          prev = current;
          current = next;
      }
      return prev;
  }

  bool isPalindrome(Node* head){
      if (head == nullptr || head->next == nullptr) return true;

      Node* slow = head;
      Node* fast = head;

      while (fast!= nullptr && fast->next!= nullptr){
          slow = slow->next;
          fast = fast->next->next;
      }

      if(fast!=nullptr){

          slow= slow->next;
      }

      Node* secondHalf = reverse(slow);
      Node* firstHalf = head;

      while (secondHalf!= nullptr){
          if (firstHalf->data != secondHalf->data) 
          {
              return false;
          }

          firstHalf = firstHalf->next;
          secondHalf = secondHalf->next;
      }

      return true;
  }

  int main(){
      
    Node* head1 = createNode("1");
      head1->next = createNode("0");
      head1->next->next = createNode("2");
       head1->next->next->next = createNode("0");
      head1->next->next->next->next = createNode("1");

      cout << "Given Example 1: ";
      if (isPalindrome(head1)) {
          cout << "Linked List is a Palindrome" << endl;
      } else {
          cout << "Linked List is not a Palindrome" << endl;
      }

      //Node 2 is a string
      Node* head2 = createNode("B");
      head2->next = createNode("O");
      head2->next->next = createNode("R");
      head2->next->next->next = createNode("R");
      head2->next->next->next->next = createNode("O");
      head2->next->next->next->next->next = createNode("W");
      head2->next->next->next->next->next->next = createNode("O");
      head2->next->next->next->next->next->next->next = createNode("R");
      head2->next->next->next->next->next->next->next->next = createNode("R");
      head2->next->next->next->next->next->next->next->next->next = createNode("O");
      head2->next->next->next->next->next->next->next->next->next->next = createNode("B");

      cout<<"Example 2: ";
      if (isPalindrome(head2)) 
      {
          cout << "Linked List is a Palindrome" << endl;
      } 
      else 
      {
          cout << "Linked List is not a Palindrome" << endl;
      }

      Node* head3 = createNode("C");
      head3->next = createNode("A");
      head3->next->next = createNode("T");
      head3->next->next->next = createNode("A");
        head3->next->next->next->next = createNode("R");
        cout << "Node 3 Checkup: ";
        if (isPalindrome(head3)) {
            cout << "THis Linked List is a Palindrome" << endl;
        } 
        else{
            cout << "This Linked List is not a Palindrome" << endl;
        }
        //free memory
        delete head1;
      delete head2;
      delete head3; 
    //  cout<<head1;

    Node* head4 = createNode("R");
      head4->next = createNode("A");                        
        head4->next->next = createNode("C");
        head4->next->next->next = createNode("E");
        head4->next->next->next->next = createNode("C");
        head4->next->next->next->next->next = createNode("A");          
        head4->next->next->next->next->next->next = createNode("R");
        cout << "Node 4 Checkup: ";     
        if (isPalindrome(head4)) {
            cout << "This Linked List is a Palindrome" << endl;
        } 
        else{
            cout << "This Linked List is not a Palindrome" << endl;
        }

        delete head4;
        return 0;
  }