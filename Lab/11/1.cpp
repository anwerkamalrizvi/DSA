#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key, value;
    Node* next;
    Node(string k, string v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
    Node** table;
    int size;

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) sum += int(c);
        return sum % size;
    }
    
public:
    HashTable(int s = 10) : size(s) {
        table = new Node*[size]();
    }

    void insert(string key, string value) {
        int index = hashFunction(key);
        Node* temp = table[index];

        while (temp) {
            if (temp->key == key) {  
                temp->value = value;
                return;
            }
            temp = temp->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    string search(string key) {
        int index = hashFunction(key);
        Node* temp = table[index];
        while (temp) {
            if (temp->key == key) return temp->value;
            temp = temp->next;
        }
        return "Not found";
    }

    void display() {
        for (int i = 0; i < size; i++) {
            if (table[i]) {
                cout << "Bucket " << i << ": ";
                Node* t = table[i];
                while (t) {
                    cout << "(" << t->key << ", " << t->value << ") ";
                    t = t->next;
                }
                cout << endl;
            }
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* t = table[i];
            while (t) {
                Node* d = t;
                t = t->next;
                delete d;
            }
        }
        delete[] table;
    }
};

int main() {
    HashTable myhash;
    myhash.insert("A", "aaaaa");
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    myhash.insert("A", "zzzzz");
    
    myhash.display();
    cout << "\nSearch A: " << myhash.search("A") << endl;
    cout << "Search B: " << myhash.search("B") << endl;
    
    return 0;
}