#include <iostream>
#include <string>
using namespace std;

class Message {
public:
    int messageId;
    string content;


    int processingTime;

    Message() {
        messageId = 0;
        content = "";
        processingTime = 0;
    }

    Message(int id, string msg, int time) {
        messageId = id;


        content = msg;
        processingTime = time;
    }
};

class MessageQueue {
private:
    Message* queue;
    int front;
    int rear;


    int capacity;
    int count;

public:
    MessageQueue(int size) {
        capacity = size;
        queue = new Message[capacity];
        front = 0;


        rear = -1;
        count = 0;
    }

    void enqueue(Message msg) {
        if (count >= capacity) {
            cout << "Queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;


        queue[rear] = msg;
        count++;
        cout << "Message " << msg.messageId << " added to queue" << endl;
    }

    Message dequeue() {
        Message msg;
        if (count == 0) {
            cout << "Queue is empty!" << endl;


            return msg;
        }
        msg = queue[front];
        front = (front + 1) % capacity;
        count--;
        return msg;
    }

    void processMessages() {


        cout << "\n=== Processing Messages ===" << endl;
        while (count > 0) {
            Message msg = dequeue();
            cout << "Processing Message " << msg.messageId << ": " << msg.content;
            cout << " (Time: " << msg.processingTime << "s)" << endl;
        }
    }


    ~MessageQueue() {
        delete[] queue;
    }
};

int main() {
    cout << "=== Messaging Application ===" << endl;
    cout << "Queue Type: Simple FIFO Queue (First In First Out)" << endl;


    cout << "\nThis is suitable because:" << endl;
    cout << "1. Messages are processed in order of arrival" << endl;
    cout << "2. Fair processing - first message received is first processed" << endl;
    cout << "3. Simple and efficient for sequential processing" << endl;

    MessageQueue msgQueue(10);

    msgQueue.enqueue(Message(1, "Hello", 2));


    msgQueue.enqueue(Message(2, "How are you?", 3));
    msgQueue.enqueue(Message(3, "Meeting at 5", 1));
    msgQueue.enqueue(Message(4, "Kese ho bhai sahib, kidher gaib?", 4));

    msgQueue.processMessages();

    return 0;
}