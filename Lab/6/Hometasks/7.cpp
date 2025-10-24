#include <iostream>
#include <string>
using namespace std;

class Patron {
public:
    int patronId;
    string name;
    int numBooks;


    string transactionType;

    Patron() {
        patronId = 0;
        name = "";
        numBooks = 0;
        transactionType = "";
    }

    Patron(int id, string n, int books, string type) {


        patronId = id;
        name = n;
        numBooks = books;
        transactionType = type;
    }
};

class LibraryQueue {
private:
    Patron* queue;
    int front;


    int rear;
    int capacity;
    int count;

public:
    LibraryQueue(int size) {
        capacity = size;
        queue = new Patron[capacity];


        front = 0;
        rear = -1;
        count = 0;
    }

    void addPatron(Patron p) {
        if (count >= capacity) {
            cout << "Queue is full! Please wait." << endl;


            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = p;
        count++;
        cout << "Patron " << p.name << " (ID: " << p.patronId << ") added to queue" << endl;
    }

    void servicePatron() {


        if (count == 0) {
            cout << "No patrons in queue" << endl;
            return;
        }
        Patron p = queue[front];
        front = (front + 1) % capacity;
        count--;


        cout << "\nServicing Patron: " << p.name << " (ID: " << p.patronId << ")" << endl;
        cout << "Transaction: " << p.transactionType << " " << p.numBooks << " book(s)" << endl;
        cout << "Transaction completed!" << endl;
    }

    void displayQueue() {
        if (count == 0) {


            cout << "\nNo patrons waiting in queue" << endl;
            return;
        }
        cout << "\n=== Current Queue ===" << endl;
        int idx = front;
        for (int i = 0; i < count; i++) {


            Patron p = queue[idx];
            cout << "Position " << (i+1) << ": " << p.name;
            cout << " (ID: " << p.patronId << ") - ";
            cout << p.transactionType << " " << p.numBooks << " book(s)" << endl;
            idx = (idx + 1) % capacity;
        }
    }


    void removePatron(int patronId) {
        if (count == 0) {
            cout << "Queue is empty" << endl;
            return;
        }

        int idx = front;


        bool found = false;
        for (int i = 0; i < count; i++) {
            if (queue[idx].patronId == patronId) {
                found = true;
                cout << "Patron " << queue[idx].name << " removed from queue" << endl;


                for (int j = i; j < count - 1; j++) {
                    int currentIdx = (front + j) % capacity;
                    int nextIdx = (front + j + 1) % capacity;
                    queue[currentIdx] = queue[nextIdx];
                }
                rear = (rear - 1 + capacity) % capacity;


                count--;
                break;
            }
            idx = (idx + 1) % capacity;
        }
        if (!found) {
            cout << "Patron not found in queue" << endl;
        }
    }


    bool isEmpty() {
        return count == 0;
    }

    ~LibraryQueue() {
        delete[] queue;
    }
};

void displayMenu() {


    cout << "\n=== Library Queue Management System ===" << endl;
    cout << "1. Add patron to queue" << endl;
    cout << "2. Service next patron\n3. Display current queue\n4. Remove patron from queue" << endl;


    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    LibraryQueue library(20);
    int choice;


    library.addPatron(Patron(101, "Anwer Kamal", 3, "Borrow"));
    library.addPatron(Patron(102, "Baqar Laghari", 2, "Return"));
    library.addPatron(Patron(103, "Kashif Pasha Bajway", 1, "Borrow"));
    library.addPatron(Patron(104, "Omer Siddiqui", 4, "Return"));

    library.displayQueue();

    while (true) {


        displayMenu();
        cin >> choice;

        switch(choice) {
            case 1: {
                int id, books;
                string name, type;


                cout << "Enter Patron ID: ";
                cin >> id;
                cout << "Enter Patron Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter number of books: ";


                cin >> books;
                cout << "Enter transaction type (Borrow/Return): ";
                cin >> type;
                library.addPatron(Patron(id, name, books, type));
                break;
            }


            case 2:
                library.servicePatron();
                break;
            case 3:
                library.displayQueue();
                break;
            case 4: {
                int id;


                cout << "Enter Patron ID to remove: ";
                cin >> id;
                library.removePatron(id);
                break;
            }
            case 5:


                cout << "Exiting system..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}