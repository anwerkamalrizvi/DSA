#include <iostream>
#include <string>

using namespace std;

struct Node {
    string name;
    int score;
    Node* next;

    Node(string n, int s) : name(n), score(s), next(nullptr) {}
};

void addNode(Node** head, string name, int score) {
    Node* newNode = new Node(name, score);
    newNode->next = *head;
    *head = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->name << " " << temp->score << endl;
        temp = temp->next;
    }
}

int getMax(Node* head) {
    int maxScore = 0;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->score > maxScore) {
            maxScore = temp->score;
        }
        temp = temp->next;
    }
    return maxScore;
}

void countingSort(Node** head, int exp) {
    Node* buckets[10] = {nullptr};
    Node* tails[10] = {nullptr};
    Node* current = *head;

    while (current != nullptr) {
        Node* next = current->next;
        current->next = nullptr;
        int digit = (current->score / exp) % 10;

        if (buckets[digit] == nullptr) {
            buckets[digit] = current;
            tails[digit] = current;
        } else {
            tails[digit]->next = current;
            tails[digit] = current;
        }
        current = next;
    }

    *head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < 10; i++) {
        if (buckets[i] != nullptr) {
            if (*head == nullptr) {
                *head = buckets[i];
                tail = tails[i];
            } else {
                tail->next = buckets[i];
                tail = tails[i];
            }
        }
    }
}

void radixSort(Node** head) {
    int maxScore = 100;

    for (int exp = 1; maxScore / exp > 0; exp *= 10) {
        countingSort(head, exp);
    }
}

void deleteNode(Node** head, string name, int score) {
    Node* temp = *head;
    Node* prev = nullptr;

    if (temp != nullptr && temp->name == name && temp->score == score) {
        *head = temp->next;
        delete temp;
        cout << "\nRecord found and deleted." << endl;
        return;
    }

    while (temp != nullptr && (temp->name != name || temp->score != score)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "\nRecord not found." << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "\nRecord found and deleted." << endl;
}

int main() {
    Node* head = nullptr;

    addNode(&head, "Baqar", 90);
    addNode(&head, "Zameer", 60);
    addNode(&head, "Sara", 70);
    addNode(&head, "Sohail", 30);
    addNode(&head, "Ahmed", 20);

    cout << "Original list:" << endl;
    printList(head);

    radixSort(&head);

    cout << "\nSorted list:" << endl;
    printList(head);

    string nameToSearch;
    int scoreToSearch;
    cout << "\nEnter name to delete: ";
    cin >> nameToSearch;
    cout << "Enter score to delete: ";
    cin >> scoreToSearch;

    deleteNode(&head, nameToSearch, scoreToSearch);

    cout << "\nUpdated list:" << endl;
    printList(head);

    return 0;
}