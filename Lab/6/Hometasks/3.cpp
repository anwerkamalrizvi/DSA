#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    char* arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        arr = new char[capacity];


        top = -1;
    }

    void push(char c) {
        if (top < capacity - 1) {
            arr[++top] = c;
        }
    }

    char pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return '\0';
    }


    char peek() {
        if (top >= 0) {
            return arr[top];
        }
        return '\0';
    }

    bool isEmpty() {
        return top == -1;
    }

    ~Stack() {
        delete[] arr;
    }
};

int precedence(char op) {
    if (op == '^') return 3;


    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string infixToPostfix(string infix) {
    Stack s(100);
    string postfix = "";


    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isalpha(c)) {
            postfix += c;
        }
        else if (c == '(') {
            s.push(c);
        }


        else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        }
        else if (isOperator(c)) {
            if (c == '^') {
                while (!s.isEmpty() && precedence(s.peek()) > precedence(c)) {
                    postfix += s.pop();
                }
            }


            else {
                while (!s.isEmpty() && precedence(s.peek()) >= precedence(c)) {
                    postfix += s.pop();
                }
            }
            s.push(c);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }


    return postfix;
}

int main() {
    string infix = "a+b*(c^d-e)^(f+g*h)-i";

    cout << "Infix Expression: " << infix << endl;


    string postfix = infixToPostfix(infix);

    cout << "Postfix Expression: " << postfix << endl;

    return 0;
}