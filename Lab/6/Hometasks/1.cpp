#include <iostream>
#include <string>
using namespace std;

class TodoStack {
private:
    string* items;
    int top;
    int capacity;

public:
    TodoStack(int size) {
        capacity = size;
        items = new string[capacity];
        top = -1;
    }

    void addItem(string task) {
        if (top >= capacity - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        items[++top] = task;
        cout << "Added: " << task << endl;
    }


    bool isEmpty() {
        return top == -1;
    }

    void removeTopItem() {
        if (isEmpty()) {
            cout << "Stack khali ha!" << endl;
            return;
        }
        cout << "Removed: " << items[top] << endl;
        top--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No tasks in the list" << endl;
            return;
        }
        cout << "\nCurrent To-Do List:" << endl;
        for (int i = top; i >= 0; i--) {
            cout << items[i] << endl;
        }
    }

    ~TodoStack() {
        delete[] items;
    }
};

int main() {
    TodoStack tasks(10);

    tasks.addItem("Complete project report");


    tasks.addItem("Attend meeting at 3 30 PM");
    tasks.addItem("Review emails !");
    tasks.addItem("Call the client");

    tasks.display();

    cout << "\nIs stack empty? " << (tasks.isEmpty() ? "Yes" : "No") << endl;

    tasks.removeTopItem();


    tasks.removeTopItem();

    tasks.display();

    return 0;
}