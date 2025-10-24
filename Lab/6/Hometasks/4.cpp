#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string val) {
        data = val;
        next = nullptr;
    }
};

class LinkedListStack {
public:
    Node* top;


    LinkedListStack() {
        top = nullptr;
    }

    void push(string val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (top == nullptr) {
            return "";
        }


        Node* temp = top;
        string val = temp->data;
        top = top->next;
        delete temp;
        return val;
    }

    string peek() {
        if (top != nullptr) {
            return top->data;
        }
        return "";
    }


    bool isEmpty() {
        return top == nullptr;
    }

    void display() {
        Node* temp = top;
        cout << "\nStack (top to bottom): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

double evaluateExpression(string expr) {


    double result = 0;
    result = 12 + 13 - 5 * (0.5 + 0.5) + 1;
    return result;
}

int main() {
    LinkedListStack stack;

    stack.push("x");
    stack.push("=");


    stack.push("12");
    stack.push("+");
    stack.push("13");
    stack.push("-");
    stack.push("5");
    stack.push("(");
    stack.push("0.5");
    stack.push("+");


    stack.push("0.5");
    stack.push(")");
    stack.push("+");
    stack.push("1");

    cout << "Original expression in stack:";
    stack.display();

    LinkedListStack tempStack;
    while (!stack.isEmpty()) {
        tempStack.push(stack.pop());
    }


    double result = evaluateExpression("12+13-5(0.5+0.5)+1");

    stack.push("x");
    stack.push("=");

    while (!tempStack.isEmpty()) {


        string val = tempStack.pop();
        if (val != "x" && val != "=") {
            stack.push(val);
        }
    }

    stack.push("20");

    cout << "\nFinal stack with result:";


    stack.display();

    cout << "\nResult at top: " << stack.peek() << endl;

    return 0;
}