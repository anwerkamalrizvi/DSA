#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE 100

class Stack {
private:
    char arr[MAX_SIZE];
    int top;

public:
    Stack(){
        top = -1;
    }
    void push(char item){
        if (top >= MAX_SIZE - 1) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        top++;
        arr[top] = item;
        cout << "Pushed '" << item << "' to stack at index " << top << endl;
    }
    char pop(){
        if (isEmpty()){
            cout << "Stack Underflow!" << endl;
            return '\0';
        }
        char item = arr[top];
        top--;
        cout <<"Popped '" << item<< "' from stack" << endl;
        return item;
    }
    bool isEmpty(){
        return (top == -1);
    }
    void display(){
        if (isEmpty()){
            cout<< "Stack is empty!" <<endl;
            return;
        }
        cout << "Stack contents: ";
        for (int i = 0; i <= top; i++){
            cout << arr[i] << " ";
        }
        cout <<endl;
    }
    int getTop(){
        return top;
    }
};
bool checkPalindrome(string str){
    Stack stack;
    
    cout<< "\n"<< string(60, '=') << endl;
    cout<< "Checking if '" << str << "' is a PALINDROME" << endl;
    cout <<string(60, '=') << endl;
    cout <<"\nSTEP 1: Pushing all characters to stack" << endl;
    cout<< string(60, '-') << endl;
    
    for (int i =0; i <str.length(); i++){
        stack.push(str[i]);
    }
    
    cout<< "\nCurrent ";
    stack.display();
    cout << "\nSTEP 2: Popping characters to build reversed string" << endl;
    cout<<string(60, '-') << endl;
    
    string reversedStr = "";
    while (!stack.isEmpty()) {
        reversedStr += stack.pop();
    }
    cout<<"\nSTEP 3: Comparison" << endl;
    cout<<string(60, '-') << endl;
    cout<< "Original string:  " << str << endl;
    cout <<"Reversed string:  " << reversedStr << endl<<endl<<endl;

    if (str == reversedStr) {
        cout <<"Result: '" << str << "' IS a PALINDROME!" << endl;
        return true;
    } 
    else 
    {
        cout<< "Result: '" << str <<"' IS NOT a PALINDROME!" << endl;
        return false;
    }
}

int main() 
{
    string word = "BORROWROB";
    
    cout << "\n*** PALINDROME CHECKER USING STACK ***" << endl;
    cout << "Stack Implementation using Arrays" << endl;
    
    bool isPalindrome = checkPalindrome(word);
    
    cout << string(60, '=') << endl;
    cout << "\nFinal Answer: " << (isPalindrome ? "PALINDROME" : "NOT PALINDROME") << endl;
    
    // Additional test cases
    cout << "\n\n*** TESTING OTHER EXAMPLES ***" << endl;
    
    checkPalindrome("RACECAR");
    checkPalindrome("HELLO");
    checkPalindrome("MADAM");
    
    return 0;
}