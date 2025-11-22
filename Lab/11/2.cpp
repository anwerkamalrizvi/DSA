#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key;
    string value;
    Node* next;
    
    Node(string k, string v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class Dictionary {
private:
    Node** table;
    int tableSize;
    
    int hashFunction(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += (int)key[i];
        }
        return sum % tableSize;
    }
    
public:
    Dictionary() {
        tableSize = 100;
        table = new Node*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }
    
    void Add_Record(string key, string value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);
        
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* temp = table[index];
            while (temp != nullptr) {
                if (temp->key == key) {
                    temp->value = value;
                    delete newNode;
                    return;
                }
                if (temp->next == nullptr) {
                    temp->next = newNode;
                    return;
                }
                temp = temp->next;
            }
        }
    }
    
    void Word_Search(string key) {
        int index = hashFunction(key);
        Node* temp = table[index];
        
        while (temp != nullptr) {
            if (temp->key == key) {
                cout << "search key " << key << ": " << temp->value << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Error: Key " << key << " not found!" << endl;
    }
    
    void Delete_Record(string key) {
        int index = hashFunction(key);
        Node* temp = table[index];
        Node* prev = nullptr;
        
        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr) {
                    table[index] = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                cout << "key " << key << " deleted successfully !" << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Error: Key " << key << " not found!" << endl;
    }
    
    void Print_Dictionary() {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != nullptr) {
                Node* temp = table[i];
                while (temp != nullptr) {
                    cout << "index " << i << ": (" << temp->key << ", " << temp->value << ")" << endl;
                    temp = temp->next;
                }
            }
        }
    }
    
    ~Dictionary() {
        for (int i = 0; i < tableSize; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] table;
    }
};

int main() {
    Dictionary dict;
    
    dict.Add_Record("AB", "FASTNU");
    dict.Add_Record("CD", "CS");
    dict.Add_Record("EF", "Engineering");
    
    dict.Word_Search("AB");
    
    dict.Delete_Record("EF");
    
    dict.Print_Dictionary();
    
    return 0;
}