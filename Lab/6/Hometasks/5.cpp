#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;
    int front;
    int rear;
    int capacity;
    int count;

public:


    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(int customerId) {
        if (count >= capacity) {
            cout << "Queue full!" << endl;


            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = customerId;
        count++;
        cout << "Customer " << customerId << " added to queue today sucessfully with 0 errors!" << endl;
    }

    int dequeue() {


        if (count == 0) {
            cout << "Queue empty ha!" << endl;
            return -1;
        }
        int customerId = arr[front];
        front = (front + 1) % capacity;
        count--;
        cout << "Customer " << customerId << " checked out" << endl;


        return customerId;
    }

    void display() {
        if (count == 0) {
            cout << "Queue empty ha" << endl;
            return;
        }
        cout << "\nCurrent Queue: ";


        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % capacity;
        }
        cout << endl;
    }

    bool isEmpty() {
        return count == 0;
    }


    ~Queue() {
        delete[] arr;
    }
};

int main() {
    Queue checkoutQueue(10);

    int customers[] = {13, 7, 4, 1, 6, 8, 10};


    cout << "Supermarket Checkout System " << endl;
    cout << "\nAdding customers...... \nto queue...." << endl;

    for (int i = 0; i < 7; i++) {
        checkoutQueue.enqueue(customers[i]);
    }

    checkoutQueue.display();


    cout << "\n\nProcessing checkouts:" << endl;
    checkoutQueue.dequeue();
    checkoutQueue.dequeue();

    checkoutQueue.display();

    cout << "\n\nProcessing remaining customers:" << endl;


    while (!checkoutQueue.isEmpty()) {
        checkoutQueue.dequeue();
    }

    checkoutQueue.display();

    return 0;
}