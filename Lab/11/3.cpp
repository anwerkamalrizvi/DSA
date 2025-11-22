#include <iostream>
#include <list>
#include <string>
using namespace std;

class Hash {
    list<pair<string,string>>* table;
    int size;

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) sum += int(c);
        return sum % size;
    }

public:
    Hash(int s = 10) : size(s) {
        table = new list<pair<string,string>>[size];
    }

    void insert(string key, string value) {
        int index = hashFunction(key);
        for (auto& p : table[index]) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }

    void search(string key) {
        int index = hashFunction(key);
        for (auto& p : table[index]) {
            if (p.first == key) {
                cout << "Key: " << p.first << ", Value: " << p.second << endl;
                return;
            }
        }
        cout << "Key " << key << " not found!" << endl;
    }

    void deleteKey(string key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if (it->first == key) {
                table[index].erase(it);
                cout << "Key " << key << " deleted successfully!" << endl;
                return;
            }
        }
        cout << "Key " << key << " not found!" << endl;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            if (!table[i].empty()) {
                cout << "Index " << i << ": ";
                for (auto& p : table[i])
                    cout << "(" << p.first << ", " << p.second << ") ";
                cout << endl;
            }
        }
    }

    ~Hash() { delete[] table; }
};

int main() {
    Hash hashTable(10);
    
    hashTable.insert("A", "Apple");
    hashTable.insert("B", "Banana");
    hashTable.insert("C", "Cherry");
    hashTable.insert("D", "Date");
    
    cout << "Hash Table:" << endl;
    hashTable.display();
    
    cout << "\nSearch B:" << endl;
    hashTable.search("B");
    
    cout << "\nDelete C:" << endl;
    hashTable.deleteKey("C");
    
    cout << "\nAfter deletion:" << endl;
    hashTable.display();
    
    return 0;
}