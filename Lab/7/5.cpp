#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void push(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if ((*newHead) == nullptr) {
                (*newHead) = cur;
            }
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) {
                prev->next = cur->next;
            }
            Node* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == nullptr) {
        (*newHead) = pivot;
    }

    (*newEnd) = tail;
    return pivot;
}

Node* quickSortRec(Node* head, Node* end) {
    if (!head || head == end) {
        return head;
    }

    Node *newHead = nullptr, *newEnd = nullptr;
    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        newHead = quickSortRec(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRec(pivot->next, newEnd);
    return newHead;
}

void quickSort(Node** headRef) {
    (*headRef) = quickSortRec(*headRef, getTail(*headRef));
    return;
}

int main() {
    Node* head = nullptr;
    push(&head, 3);
    push(&head, 5);
    push(&head, 1);
    push(&head, 9);
    push(&head, 8);
    push(&head, 7);
    push(&head, 10);

    cout << "Linked list before sorting:" << endl;
    printList(head);

    quickSort(&head);

    cout << "Linked list after sorting:" << endl;
    printList(head);

    return 0;
}