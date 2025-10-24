#include <iostream>
#include <string>
using namespace std;

class StackNode {
public:
    string url;
    StackNode* next;

    StackNode(string u) {
        url = u;
        next = nullptr;
    }
};

class BrowserStack {
public:
    StackNode* top;

    BrowserStack() {
        top = nullptr;
    }

    void push(string url) {
        StackNode* newNode = new StackNode(url);
        newNode->next = top;
        top = newNode;
    }


    string pop() {
        if (top == nullptr) {
            return "";
        }
        StackNode* temp = top;
        string url = temp->url;
        top = top->next;
        delete temp;
        return url;
    }

    void display() {
        StackNode* temp = top;
        cout << "Stack: ";
        while (temp != nullptr) {
            cout << temp->url << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class ListNode {
public:
    string url;


    ListNode* next;

    ListNode(string u) {
        url = u;
        next = nullptr;
    }
};

class BrowserList {
public:
    ListNode* head;

    BrowserList() {
        head = nullptr;
    }

    void addFront(string url) {
        ListNode* newNode = new ListNode(url);
        newNode->next = head;
        head = newNode;
    }

    void removeFront() {
        if (head == nullptr) {
            return;
        }


        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    void display() {
        ListNode* temp = head;
        cout << "List: ";
        while (temp != nullptr) {
            cout << temp->url << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

void goBack(BrowserStack& stack, BrowserList& list, int times) {
    cout << "\nGoing back " << times << " times..." << endl;


    for (int i = 0; i < times; i++) {
        stack.pop();
        list.removeFront();
    }
}

int main() {
    BrowserStack historyStack;
    BrowserList historyList;

    string websites[] = {"Wikipedia", "Chatgpt", "X", "LinkedIn", "Instagram"};

    for (int i = 0; i < 5; i++) {
        historyStack.push(websites[i]);


        historyList.addFront(websites[i]);
    }

    cout << "Initial state:" << endl;
    historyStack.display();
    historyList.display();

    goBack(historyStack, historyList, 2);

    cout << "\nAfter going back:" << endl;


    historyStack.display();
    historyList.display();

    return 0;
}