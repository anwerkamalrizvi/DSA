#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    bool isEmpty;
    
    Student() {
        rollNumber = -1;
        name = "";
        isEmpty = true;
    }
    
    Student(int roll, string n) {
        rollNumber = roll;
        name = n;
        isEmpty = false;
    }
};

class StudentHashTable {
private:
    Student* table;
    int tableSize;
    
    int hashFunction(int rollNumber) {
        return rollNumber % tableSize;
    }
    
public:
    StudentHashTable() {
        tableSize = 15;
        table = new Student[tableSize];
    }
    
    void InsertRecord(int rollNumber, string name) {
        int index = hashFunction(rollNumber);
        int attempt = 0;
        int originalIndex = index;
        
        while (!table[index].isEmpty) {
            if (table[index].rollNumber == rollNumber) {
                cout << "Roll number " << rollNumber << " already exists!" << endl;
                return;
            }
            
            attempt++;
            index = (originalIndex + attempt * attempt) % tableSize;
            
            if (attempt >= tableSize) {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        
        table[index] = Student(rollNumber, name);
        cout << "Record inserted at index " << index << endl;
    }
    
    void SearchRecord(int rollNumber) {
        int index = hashFunction(rollNumber);
        int attempt = 0;
        int originalIndex = index;
        
        while (!table[index].isEmpty) {
            if (table[index].rollNumber == rollNumber) {
                cout << "Record found: Roll Number = " << table[index].rollNumber;
                cout << ", Name = " << table[index].name << endl;
                return;
            }
            
            attempt++;
            index = (originalIndex + attempt * attempt) % tableSize;
            
            if (attempt >= tableSize) {
                break;
            }
        }
        
        cout << "Record not found" << endl;
    }
    
    void Display() {
        cout << "\nHash Table Contents:" << endl;
        for (int i = 0; i < tableSize; i++) {
            if (!table[i].isEmpty) {
                cout << "Index " << i << ": Roll Number = " << table[i].rollNumber;
                cout << ", Name = " << table[i].name << endl;
            }
        }
    }
    
    ~StudentHashTable() {
        delete[] table;
    }
};

int main() {
    StudentHashTable hashTable;
    
    hashTable.InsertRecord(101, "Ali");
    hashTable.InsertRecord(102, "Ahmed");
    hashTable.InsertRecord(116, "Sara");
    hashTable.InsertRecord(131, "Fatima");
    hashTable.InsertRecord(146, "Hassan");
    
    hashTable.Display();
    
    cout << "\nSearching for roll number 102:" << endl;
    hashTable.SearchRecord(102);
    
    cout << "\nSearching for roll number 999:" << endl;
    hashTable.SearchRecord(999);
    
    return 0;
}