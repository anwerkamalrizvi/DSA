/*
================================================================================
    SMART RAILWAY SCHEDULING SYSTEM - KARACHI, PAKISTAN
    Advanced Data Structures & Algorithms Project
    100% MANUAL IMPLEMENTATION - NO STL CONTAINERS
    
    Manual Data Structures:
    - Custom Vector (Dynamic Array)
    - Custom Map (AVL Tree)
    - Custom HashTable (Quadratic Probing)
    - Custom Set (AVL Tree)
    - Custom Queue
    - Custom PriorityQueue (Heap)
    - Custom Pair
    - Dijkstra's Algorithm
    - DFS for All Paths
================================================================================
*/

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// ==================== MANUAL PAIR IMPLEMENTATION ====================

template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    
    Pair() {}
    Pair(T1 f, T2 s) : first(f), second(s) {}
    
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    
    bool operator<(const Pair& other) const {
        if (first != other.first) return first < other.first;
        return second < other.second;
    }
    
    bool operator>(const Pair& other) const {
        return other < *this;
    }
};

template<typename T1, typename T2>
Pair<T1, T2> makePair(T1 f, T2 s) {
    return Pair<T1, T2>(f, s);
}

// ==================== MANUAL VECTOR IMPLEMENTATION ====================

template<typename T>
class Vector {
private:
    T* data;
    int capacity;
    int size;
    
    void resize() {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    
public:
    Vector() : data(nullptr), capacity(0), size(0) {}
    
    Vector(int initialCapacity) : capacity(initialCapacity), size(0) {
        data = new T[capacity];
    }
    
    Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    ~Vector() {
        delete[] data;
    }
    
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }
    
    void pop_back() {
        if (size > 0) size--;
    }
    
    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }
    
    T& at(int index) {
        if (index < 0 || index >= size) {
            throw runtime_error("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
    bool empty() const { return size == 0; }
    void clear() { size = 0; }
    
    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }
    
    void erase(T* pos) {
        int index = pos - data;
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
    
    T& back() { return data[size - 1]; }
    void reserve(int newCapacity) {
        if (newCapacity > capacity) {
            T* newData = new T[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }
};

// ==================== MANUAL MAP IMPLEMENTATION (AVL TREE) ====================

template<typename K, typename V>
class Map {
private:
    struct Node {
        Pair<K, V> data;
        Node* left;
        Node* right;
        int height;
        
        Node(K key, V value) : data(key, value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    int count;
    
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }
    
    Node* insert(Node* node, K key, V value, bool& updated) {
        if (!node) {
            if (!updated) count++;
            return new Node(key, value);
        }
        
        if (key < node->data.first) {
            node->left = insert(node->left, key, value, updated);
        } else if (key > node->data.first) {
            node->right = insert(node->right, key, value, updated);
        } else {
            node->data.second = value;
            updated = true;
            return node;
        }
        
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        
        if (balance > 1 && key < node->left->data.first) {
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->data.first) {
            return leftRotate(node);
        }
        if (balance > 1 && key > node->left->data.first) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->data.first) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    Node* find(Node* node, const K& key) const {
        if (!node) return nullptr;
        if (key == node->data.first) return node;
        if (key < node->data.first) return find(node->left, key);
        return find(node->right, key);
    }
    
    void inorder(Node* node, Vector<Pair<K, V>>& result) const {
        if (!node) return;
        inorder(node->left, result);
        result.push_back(node->data);
        inorder(node->right, result);
    }
    
    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    Map() : root(nullptr), count(0) {}
    
    ~Map() {
        deleteTree(root);
    }
    
    void insert(const K& key, const V& value) {
        bool updated = false;
        root = insert(root, key, value, updated);
    }
    
    V& operator[](const K& key) {
        Node* node = find(root, key);
        if (!node) {
            bool updated = false;
            root = insert(root, key, V(), updated);
            node = find(root, key);
        }
        return node->data.second;
    }
    
    bool contains(const K& key) const {
        return find(root, key) != nullptr;
    }
    
    const V* get(const K& key) const {
        Node* node = find(root, key);
        return node ? &node->data.second : nullptr;
    }
    
    V* get(const K& key) {
        Node* node = find(root, key);
        return node ? &node->data.second : nullptr;
    }
    
    int size() const { return count; }
    bool empty() const { return count == 0; }
    
    Vector<Pair<K, V>> toVector() const {
        Vector<Pair<K, V>> result;
        inorder(root, result);
        return result;
    }
};

// ==================== MANUAL SET IMPLEMENTATION ====================

template<typename T>
class Set {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        
        Node(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    int count;
    
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }
    
    Node* insert(Node* node, T value, bool& inserted) {
        if (!node) {
            inserted = true;
            count++;
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insert(node->left, value, inserted);
        } else if (value > node->data) {
            node->right = insert(node->right, value, inserted);
        } else {
            return node;
        }
        
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    bool find(Node* node, T value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return find(node->left, value);
        return find(node->right, value);
    }
    
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }
    
    Node* erase(Node* node, T value) {
        if (!node) return node;
        
        if (value < node->data) {
            node->left = erase(node->left, value);
        } else if (value > node->data) {
            node->right = erase(node->right, value);
        } else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
                count--;
            } else {
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = erase(node->right, temp->data);
            }
        }
        
        if (!node) return node;
        
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    Set() : root(nullptr), count(0) {}
    
    ~Set() {
        deleteTree(root);
    }
    
    void insert(T value) {
        bool inserted = false;
        root = insert(root, value, inserted);
    }
    
    void erase(T value) {
        root = erase(root, value);
    }
    
    bool contains(T value) const {
        return find(root, value);
    }
    
    int size() const { return count; }
    bool empty() const { return count == 0; }
};

// ==================== MANUAL PRIORITY QUEUE (MAX HEAP) ====================

template<typename T>
class PriorityQueue {
private:
    Vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] < heap[index]) {
            T temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.getSize();
        while (leftChild(index) < size) {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            if (left < size && heap[largest] < heap[left]) {
                largest = left;
            }
            if (right < size && heap[largest] < heap[right]) {
                largest = right;
            }
            
            if (largest == index) break;
            
            T temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            index = largest;
        }
    }
    
public:
    PriorityQueue() {}
    
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.getSize() - 1);
    }
    
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap[heap.getSize() - 1];
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
    
    const T& top() const {
        return heap[0];
    }
    
    bool empty() const {
        return heap.empty();
    }
    
    int size() const {
        return heap.getSize();
    }
};

// ==================== MIN PRIORITY QUEUE ====================

template<typename T>
struct Greater {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

template<typename T>
class MinPriorityQueue {
private:
    Vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[index] < heap[parent(index)]) {
            T temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.getSize();
        while (leftChild(index) < size) {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            
            if (smallest == index) break;
            
            T temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            index = smallest;
        }
    }
    
public:
    MinPriorityQueue() {}
    
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.getSize() - 1);
    }
    
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap[heap.getSize() - 1];
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
    
    const T& top() const {
        return heap[0];
    }
    
    bool empty() const {
        return heap.empty();
    }
    
    int size() const {
        return heap.getSize();
    }
};

// ==================== MANUAL HASH TABLE ====================

template<typename K, typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 100;
    
    struct HashNode {
        K key;
        V value;
        bool isOccupied;
        bool isDeleted;
        
        HashNode() : isOccupied(false), isDeleted(false) {}
    };
    
    Vector<HashNode> table;
    int count;
    
    int hashFunction(const string& key) const {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % TABLE_SIZE;
        }
        return hash >= 0 ? hash : hash + TABLE_SIZE;
    }
    
    int probe(int index, int i) const {
        return (index + i * i) % TABLE_SIZE;
    }
    
public:
    HashTable() : count(0) {
        table.reserve(TABLE_SIZE);
        for (int i = 0; i < TABLE_SIZE; i++) {
            table.push_back(HashNode());
        }
    }
    
    bool insert(const K& key, const V& value) {
        if (count >= TABLE_SIZE * 0.7) {
            return false;
        }
        
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied || table[probedIndex].isDeleted) {
                table[probedIndex].key = key;
                table[probedIndex].value = value;
                table[probedIndex].isOccupied = true;
                table[probedIndex].isDeleted = false;
                count++;
                return true;
            }
            
            if (table[probedIndex].key == key) {
                table[probedIndex].value = value;
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
    bool find(const K& key, V& value) const {
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied) {
                return false;
            }
            
            if (table[probedIndex].key == key && !table[probedIndex].isDeleted) {
                value = table[probedIndex].value;
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
    Vector<Pair<K, V>> getAllEntries() const {
        Vector<Pair<K, V>> entries;
        for (int i = 0; i < table.getSize(); i++) {
            if (table[i].isOccupied && !table[i].isDeleted) {
                entries.push_back(makePair(table[i].key, table[i].value));
            }
        }
        return entries;
    }
    
    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

// ==================== SIMPLE SMART POINTER ====================

template<typename T>
class SharedPtr {
private:
    T* ptr;
    int* refCount;
    
public:
    SharedPtr() : ptr(nullptr), refCount(nullptr) {}
    
    SharedPtr(T* p) : ptr(p), refCount(new int(1)) {}
    
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) (*refCount)++;
    }
    
    ~SharedPtr() {
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
            }
        }
    }
    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            if (refCount) {
                (*refCount)--;
                if (*refCount == 0) {
                    delete ptr;
                    delete refCount;
                }
            }
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) (*refCount)++;
        }
        return *this;
    }
    
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    const T* operator->() const { return ptr; }
    T* get() { return ptr; }
    const T* get() const { return ptr; }
    bool isNull() const { return ptr == nullptr; }
};

template<typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) {
    return SharedPtr<T>(new T(args...));
}

// ==================== UTILITY CLASSES ====================

class Time {
private:
    int hours, minutes;
    
public:
    Time(int h = 0, int m = 0) : hours(h % 24), minutes(m % 60) {}
    
    string toString() const {
        stringstream ss;
        ss << setfill('0') << setw(2) << hours << ":" 
           << setw(2) << minutes;
        return ss.str();
    }
    
    int toMinutes() const { return hours * 60 + minutes; }
    
    bool operator<(const Time& other) const {
        return toMinutes() < other.toMinutes();
    }
    
    bool operator>(const Time& other) const {
        return toMinutes() > other.toMinutes();
    }
    
    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes;
    }
    
    Time addMinutes(int mins) const {
        int totalMins = toMinutes() + mins;
        return Time(totalMins / 60, totalMins % 60);
    }
};

class Date {
private:
    int day, month, year;
    
public:
    Date(int d = 1, int m = 1, int y = 2024) : day(d), month(m), year(y) {}
    
    string toString() const {
        stringstream ss;
        ss << setfill('0') << setw(2) << day << "/" 
           << setw(2) << month << "/" << year;
        return ss.str();
    }
};

// ==================== CORE ENTITIES ====================

class Station {
private:
    string stationId;
    string name;
    string city;
    int platformCount;
    Pair<double, double> coordinates;
    
public:
    Station() : platformCount(0), coordinates(makePair(0.0, 0.0)) {}
    
    Station(string id, string n, string c, int platforms, double lat, double lon)
        : stationId(id), name(n), city(c), platformCount(platforms),
          coordinates(makePair(lat, lon)) {}
    
    string getId() const { return stationId; }
    string getName() const { return name; }
    string getCity() const { return city; }
    int getPlatforms() const { return platformCount; }
    
    void display() const {
        cout << "\n+=========================================+\n";
        cout << "| Station ID    : " << left << setw(20) << stationId << "|\n";
        cout << "| Name          : " << setw(20) << name << "|\n";
        cout << "| City          : " << setw(20) << city << "|\n";
        cout << "| Platforms     : " << setw(20) << platformCount << "|\n";
        cout << "+=========================================+\n";
    }
};

class Passenger {
private:
    string passengerId;
    string name;
    string cnic;
    string phone;
    int age;
    
public:
    Passenger() : age(0) {}
    
    Passenger(string id, string n, string c, string p, int a)
        : passengerId(id), name(n), cnic(c), phone(p), age(a) {}
    
    string getId() const { return passengerId; }
    string getName() const { return name; }
    
    void display() const {
        cout << "+=========================================+\n";
        cout << "| Passenger ID  : " << left << setw(20) << passengerId << "|\n";
        cout << "| Name          : " << setw(20) << name << "|\n";
        cout << "| CNIC          : " << setw(20) << cnic << "|\n";
        cout << "| Phone         : " << setw(20) << phone << "|\n";
        cout << "| Age           : " << setw(20) << age << "|\n";
        cout << "+=========================================+\n";
    }
};

class Ticket {
private:
    string ticketId;
    string passengerId;
    string trainId;
    string fromStation;
    string toStation;
    Date journeyDate;
    Time departureTime;
    double fare;
    string seatNumber;
    bool isBooked;
    
public:
    Ticket() : fare(0.0), isBooked(false) {}
    
    Ticket(string tId, string pId, string trId, string from, string to,
           Date date, Time time, double f, string seat)
        : ticketId(tId), passengerId(pId), trainId(trId), 
          fromStation(from), toStation(to), journeyDate(date),
          departureTime(time), fare(f), seatNumber(seat), isBooked(true) {}
    
    string getId() const { return ticketId; }
    string getTrainId() const { return trainId; }
    double getFare() const { return fare; }
    bool getBookingStatus() const { return isBooked; }
    
    void cancelTicket() { isBooked = false; }
    
    void display() const {
        cout << "\n+===========================================+\n";
        cout << "|           RAILWAY TICKET                  |\n";
        cout << "+===========================================+\n";
        cout << "| Ticket ID     : " << left << setw(22) << ticketId << "|\n";
        cout << "| Passenger ID  : " << setw(22) << passengerId << "|\n";
        cout << "| Train ID      : " << setw(22) << trainId << "|\n";
        cout << "| From          : " << setw(22) << fromStation << "|\n";
        cout << "| To            : " << setw(22) << toStation << "|\n";
        cout << "| Date          : " << setw(22) << journeyDate.toString() << "|\n";
        cout << "| Departure     : " << setw(22) << departureTime.toString() << "|\n";
        cout << "| Seat          : " << setw(22) << seatNumber << "|\n";
        cout << "| Fare          : PKR " << setw(18) << fixed << setprecision(2) << fare << "|\n";
        cout << "| Status        : " << setw(22) << (isBooked ? "CONFIRMED" : "CANCELLED") << "|\n";
        cout << "+===========================================+\n";
    }
};

class Train {
private:
    string trainId;
    string trainName;
    string trainType;
    int totalSeats;
    int availableSeats;
    Vector<string> route;
    Map<string, Time> schedule;
    int priority;
    int delayMinutes;
    
public:
    Train() : totalSeats(0), availableSeats(0), priority(0), delayMinutes(0) {}
    
    Train(string id, string name, string type, int seats, int prio)
        : trainId(id), trainName(name), trainType(type), 
          totalSeats(seats), availableSeats(seats), priority(prio), delayMinutes(0) {}
    
    string getId() const { return trainId; }
    string getName() const { return trainName; }
    int getPriority() const { return priority; }
    int getDelay() const { return delayMinutes; }
    int getAvailableSeats() const { return availableSeats; }
    Vector<string> getRoute() const { return route; }
    
    void addToRoute(string stationId, Time arrivalTime) {
        route.push_back(stationId);
        schedule.insert(stationId, arrivalTime);
    }
    
    void setDelay(int mins) { delayMinutes = mins; }
    
    bool bookSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            return true;
        }
        return false;
    }
    
    void releaseSeat() {
        if (availableSeats < totalSeats) {
            availableSeats++;
        }
    }
    
    Time getArrivalTime(string stationId) const {
        const Time* timePtr = schedule.get(stationId);
        if (timePtr) {
            return timePtr->addMinutes(delayMinutes);
        }
        return Time(0, 0);
    }
    
    void display() const {
        cout << "\n+============================================+\n";
        cout << "| Train ID      : " << left << setw(23) << trainId << "|\n";
        cout << "| Name          : " << setw(23) << trainName << "|\n";
        cout << "| Type          : " << setw(23) << trainType << "|\n";
        cout << "| Total Seats   : " << setw(23) << totalSeats << "|\n";
        cout << "| Available     : " << setw(23) << availableSeats << "|\n";
        cout << "| Priority      : " << setw(23) << priority << "|\n";
        cout << "| Delay         : " << setw(20) << delayMinutes << " min|\n";
        cout << "+============================================+\n";
        cout << "| Route & Schedule:                          |\n";
        
        Vector<Pair<string, Time>> scheduleVec = schedule.toVector();
        for (int i = 0; i < scheduleVec.getSize(); i++) {
            Time actualTime = scheduleVec[i].second.addMinutes(delayMinutes);
            cout << "|  -> " << left << setw(23) << scheduleVec[i].first 
                 << setw(10) << actualTime.toString() << "   |\n";
        }
        cout << "+============================================+\n";
    }
};

// ==================== GRAPH EDGE ====================

struct Edge {
    string destination;
    double distance;
    int travelTime;
    double fare;
    
    Edge() : distance(0), travelTime(0), fare(0) {}
    
    Edge(string dest, double dist, int time, double f)
        : destination(dest), distance(dist), travelTime(time), fare(f) {}
};

// ==================== PATH INFO ====================

struct PathInfo {
    Vector<string> path;
    double totalDistance;
    int totalTime;
    double totalFare;
    
    PathInfo() : totalDistance(0), totalTime(0), totalFare(0) {}
};

// ==================== PASSENGER QUEUE ====================

class PassengerQueue {
private:
    struct QueueNode {
        Passenger passenger;
        int priority;
        Time arrivalTime;
        
        QueueNode() : priority(0) {}
        
        QueueNode(Passenger p, int pr, Time t)
            : passenger(p), priority(pr), arrivalTime(t) {}
        
        bool operator<(const QueueNode& other) const {
            if (priority != other.priority) {
                return priority > other.priority;
            }
            return arrivalTime < other.arrivalTime;
        }
    };
    
    PriorityQueue<QueueNode> pq;
    
public:
    void enqueue(const Passenger& p, int priority, Time arrivalTime) {
        pq.push(QueueNode(p, priority, arrivalTime));
    }
    
    Passenger dequeue() {
        if (pq.empty()) {
            throw runtime_error("Queue is empty");
        }
        Passenger p = pq.top().passenger;
        pq.pop();
        return p;
    }
    
    bool isEmpty() const {
        return pq.empty();
    }
    
    int size() const {
        return pq.size();
    }
};

// ==================== RAILWAY GRAPH SYSTEM ====================

class RailwayGraph {
private:
    Map<string, Station> stations;
    Map<string, Vector<Edge>> adjacencyList;
    HashTable<string, SharedPtr<Train>> trains;
    HashTable<string, Passenger> passengers;
    HashTable<string, Ticket> tickets;
    Map<string, PassengerQueue> stationQueues;
    
    int ticketCounter;
    int passengerCounter;
    
public:
    RailwayGraph() : ticketCounter(1000), passengerCounter(1000) {
        initializeKarachiNetwork();
    }
    
    void initializeKarachiNetwork() {
        addStation(Station("KC", "Karachi Cantt", "Karachi", 6, 24.8607, 67.0011));
        addStation(Station("KCTY", "Karachi City", "Karachi", 8, 24.8614, 67.0099));
        addStation(Station("DRH", "Drigh Road", "Karachi", 4, 24.8967, 67.1354));
        addStation(Station("MLR", "Malir", "Karachi", 3, 24.8918, 67.2094));
        addStation(Station("LNDI", "Landhi", "Karachi", 4, 24.8471, 67.2176));
        addStation(Station("BQS", "Bin Qasim", "Karachi", 3, 24.7935, 67.3245));
        addStation(Station("SAL", "Shah Abdul Latif", "Karachi", 2, 24.9315, 67.0773));
        addStation(Station("JCL", "Jama Cloth", "Karachi", 2, 24.8805, 67.0352));
        addStation(Station("ORG", "Orangi", "Karachi", 3, 24.9450, 66.9875));
        addStation(Station("SITE", "SITE", "Karachi", 2, 24.8850, 66.9900));
        
        addEdge("KCTY", "KC", 1.2, 5, 20);
        addEdge("KC", "DRH", 8.5, 15, 50);
        addEdge("DRH", "MLR", 6.8, 12, 40);
        addEdge("MLR", "LNDI", 5.2, 10, 35);
        addEdge("LNDI", "BQS", 8.3, 18, 60);
        addEdge("KCTY", "JCL", 2.8, 7, 25);
        addEdge("JCL", "KC", 3.8, 8, 30);
        addEdge("SAL", "DRH", 7.5, 20, 55);
        
        initializeTrains();
    }
    
    void initializeTrains() {
        SharedPtr<Train> train1 = makeShared<Train>("TN001", "Karachi Express", "Express", 500, 10);
        train1->addToRoute("KCTY", Time(6, 0));
        train1->addToRoute("KC", Time(6, 10));
        train1->addToRoute("DRH", Time(6, 30));
        train1->addToRoute("MLR", Time(6, 50));
        train1->addToRoute("LNDI", Time(7, 5));
        train1->addToRoute("BQS", Time(7, 30));
        trains.insert("TN001", train1);
        
        SharedPtr<Train> train2 = makeShared<Train>("TN002", "Local Passenger", "Passenger", 600, 5);
        train2->addToRoute("KC", Time(8, 0));
        train2->addToRoute("DRH", Time(8, 20));
        train2->addToRoute("MLR", Time(8, 45));
        trains.insert("TN002", train2);
    }
    
    void addStation(const Station& station) {
        stations.insert(station.getId(), station);
        adjacencyList.insert(station.getId(), Vector<Edge>());
    }
    
    void addEdge(const string& from, const string& to, double distance, int time, double fare) {
        Vector<Edge>* fromEdges = adjacencyList.get(from);
        Vector<Edge>* toEdges = adjacencyList.get(to);
        
        if (fromEdges) fromEdges->push_back(Edge(to, distance, time, fare));
        if (toEdges) toEdges->push_back(Edge(from, distance, time, fare));
    }
    
    void displayAllStations() {
        cout << "\n+===========================================================+\n";
        cout << "|              KARACHI RAILWAY STATIONS                     |\n";
        cout << "+===========================================================+\n";
        cout << "| ID    | Name                    | Platforms | City        |\n";
        cout << "+===========================================================+\n";
        
        Vector<Pair<string, Station>> stationVec = stations.toVector();
        for (int i = 0; i < stationVec.getSize(); i++) {
            const Station& s = stationVec[i].second;
            cout << "| " << left << setw(6) << s.getId() 
                 << "| " << setw(24) << s.getName()
                 << "| " << setw(10) << s.getPlatforms()
                 << "| " << setw(12) << s.getCity() << "|\n";
        }
        
        cout << "+===========================================================+\n";
    }
    
    PathInfo dijkstraShortestPath(const string& source, const string& destination) {
        PathInfo result;
        
        if (!stations.contains(source) || !stations.contains(destination)) {
            cout << "Invalid source or destination!\n";
            return result;
        }
        
        Map<string, double> dist;
        Map<string, int> time;
        Map<string, double> fare;
        Map<string, string> parent;
        Set<string> visited;
        
        Vector<Pair<string, Station>> stationVec = stations.toVector();
        for (int i = 0; i < stationVec.getSize(); i++) {
            dist.insert(stationVec[i].first, numeric_limits<double>::max());
            time.insert(stationVec[i].first, INT_MAX);
            fare.insert(stationVec[i].first, numeric_limits<double>::max());
        }
        
        dist.insert(source, 0);
        time.insert(source, 0);
        fare.insert(source, 0);
        
        MinPriorityQueue<Pair<double, string>> pq;
        pq.push(makePair(0.0, source));
        
        while (!pq.empty()) {
            string u = pq.top().second;
            pq.pop();
            
            if (visited.contains(u)) continue;
            visited.insert(u);
            
            if (u == destination) break;
            
            const Vector<Edge>* edges = adjacencyList.get(u);
            if (edges) {
                for (int i = 0; i < edges->getSize(); i++) {
                    const Edge& edge = (*edges)[i];
                    string v = edge.destination;
                    
                    const double* uDist = dist.get(u);
                    const double* vDist = dist.get(v);
                    
                    if (!visited.contains(v) && uDist && vDist && *uDist + edge.distance < *vDist) {
                        dist.insert(v, *uDist + edge.distance);
                        time.insert(v, *time.get(u) + edge.travelTime);
                        fare.insert(v, *fare.get(u) + edge.fare);
                        parent.insert(v, u);
                        pq.push(makePair(*uDist + edge.distance, v));
                    }
                }
            }
        }
        
        const double* destDist = dist.get(destination);
        if (!destDist || *destDist == numeric_limits<double>::max()) {
            cout << "No path found!\n";
            return result;
        }
        
        string current = destination;
        while (current != source) {
            result.path.push_back(current);
            const string* p = parent.get(current);
            if (!p) break;
            current = *p;
        }
        result.path.push_back(source);
        
        // Reverse path
        for (int i = 0; i < result.path.getSize() / 2; i++) {
            string temp = result.path[i];
            result.path[i] = result.path[result.path.getSize() - 1 - i];
            result.path[result.path.getSize() - 1 - i] = temp;
        }
        
        result.totalDistance = *destDist;
        result.totalTime = *time.get(destination);
        result.totalFare = *fare.get(destination);
        
        return result;
    }
    
    void displayShortestPath(const string& source, const string& destination) {
        cout << "\n+========================================================+\n";
        cout << "|           SHORTEST PATH ANALYSIS                       |\n";
        cout << "+========================================================+\n";
        
        PathInfo path = dijkstraShortestPath(source, destination);
        if (path.path.empty()) return;
        
        cout << "| Route: ";
        for (int i = 0; i < path.path.getSize(); i++) {
            cout << path.path[i];
            if (i < path.path.getSize() - 1) cout << " -> ";
        }
        cout << "\n| Total Distance: " << fixed << setprecision(2) 
             << path.totalDistance << " km\n";
        cout << "| Total Time: " << path.totalTime << " minutes\n";
        cout << "| Total Fare: PKR " << path.totalFare << "\n";
        cout << "+========================================================+\n";
    }
    
    string addPassenger(const string& name, const string& cnic, 
                       const string& phone, int age) {
        string passengerId = "P" + to_string(passengerCounter++);
        Passenger p(passengerId, name, cnic, phone, age);
        passengers.insert(passengerId, p);
        return passengerId;
    }
    
    void displayPassenger(const string& passengerId) {
        Passenger p;
        if (passengers.find(passengerId, p)) {
            p.display();
        } else {
            cout << "Passenger not found!\n";
        }
    }
    
    string bookTicket(const string& passengerId, const string& trainId,
                     const string& from, const string& to) {
        Passenger p;
        if (!passengers.find(passengerId, p)) {
            cout << "Passenger not found!\n";
            return "";
        }
        
        SharedPtr<Train> train;
        if (!trains.find(trainId, train)) {
            cout << "Train not found!\n";
            return "";
        }
        
        if (!train->bookSeat()) {
            cout << "No seats available!\n";
            return "";
        }
        
        PathInfo path = dijkstraShortestPath(from, to);
        
        string ticketId = "T" + to_string(ticketCounter++);
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Date currentDate(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
        
        Time departureTime = train->getArrivalTime(from);
        string seatNumber = "S-" + to_string(train->getAvailableSeats() + 1);
        
        Ticket ticket(ticketId, passengerId, trainId, from, to,
                     currentDate, departureTime, path.totalFare, seatNumber);
        
        tickets.insert(ticketId, ticket);
        
        cout << "\n[SUCCESS] Ticket booked successfully!\n";
        cout << "Ticket ID: " << ticketId << "\n";
        
        return ticketId;
    }
    
    void displayTicket(const string& ticketId) {
        Ticket t;
        if (tickets.find(ticketId, t)) {
            t.display();
        } else {
            cout << "Ticket not found!\n";
        }
    }
    
    void displayAllTrains() {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        
        cout << "\n+============================================================+\n";
        cout << "|                    ALL TRAINS IN SYSTEM                    |\n";
        cout << "+============================================================+\n";
        
        for (int i = 0; i < allTrains.getSize(); i++) {
            allTrains[i].second->display();
        }
    }
    
    void displaySystemStatistics() {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        Vector<Pair<string, Ticket>> allTickets = tickets.getAllEntries();
        Vector<Pair<string, Passenger>> allPassengers = passengers.getAllEntries();
        
        int totalSeats = 0;
        int bookedSeats = 0;
        double totalRevenue = 0;
        int activeTickets = 0;
        
        for (int i = 0; i < allTrains.getSize(); i++) {
            totalSeats += 500;
            bookedSeats += (500 - allTrains[i].second->getAvailableSeats());
        }
        
        for (int i = 0; i < allTickets.getSize(); i++) {
            if (allTickets[i].second.getBookingStatus()) {
                totalRevenue += allTickets[i].second.getFare();
                activeTickets++;
            }
        }
        
        cout << "\n+========================================================+\n";
        cout << "|           RAILWAY SYSTEM STATISTICS                    |\n";
        cout << "+========================================================+\n";
        cout << "| Total Stations        : " << stations.size() << "\n";
        cout << "| Total Trains          : " << allTrains.getSize() << "\n";
        cout << "| Total Passengers      : " << allPassengers.getSize() << "\n";
        cout << "| Active Tickets        : " << activeTickets << "\n";
        cout << "| Total Seats           : " << totalSeats << "\n";
        cout << "| Booked Seats          : " << bookedSeats << "\n";
        cout << "| Total Revenue         : PKR " << fixed << setprecision(2) << totalRevenue << "\n";
        cout << "+========================================================+\n";
    }
};

// ==================== MENU SYSTEM ====================

class MenuSystem {
private:
    RailwayGraph& railway;
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void pause() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
public:
    MenuSystem(RailwayGraph& rg) : railway(rg) {}
    
    void run() {
        while (true) {
            clearScreen();
            cout << "\n+==========================================================+\n";
            cout << "|     SMART RAILWAY SCHEDULING SYSTEM - KARACHI            |\n";
            cout << "+==========================================================+\n";
            cout << "|  1. View All Stations                                    |\n";
            cout << "|  2. View All Trains                                      |\n";
            cout << "|  3. Find Shortest Path (Dijkstra)                        |\n";
            cout << "|  4. Register Passenger                                   |\n";
            cout << "|  5. Book Ticket                                          |\n";
            cout << "|  6. View Ticket                                          |\n";
            cout << "|  7. System Statistics                                    |\n";
            cout << "|  0. Exit                                                 |\n";
            cout << "+==========================================================+\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1:
                    railway.displayAllStations();
                    pause();
                    break;
                case 2:
                    railway.displayAllTrains();
                    pause();
                    break;
                case 3: {
                    string from, to;
                    cout << "Enter Source Station: ";
                    cin >> from;
                    cout << "Enter Destination Station: ";
                    cin >> to;
                    cin.ignore();
                    railway.displayShortestPath(from, to);
                    pause();
                    break;
                }
                case 4: {
                    string name, cnic, phone;
                    int age;
                    cout << "Enter Name: ";
                    getline(cin, name);
                    cout << "Enter CNIC: ";
                    cin >> cnic;
                    cout << "Enter Phone: ";
                    cin >> phone;
                    cout << "Enter Age: ";
                    cin >> age;
                    cin.ignore();
                    string id = railway.addPassenger(name, cnic, phone, age);
                    cout << "\n[SUCCESS] Passenger registered! ID: " << id << "\n";
                    pause();
                    break;
                }
                case 5: {
                    string passengerId, trainId, from, to;
                    cout << "Enter Passenger ID: ";
                    cin >> passengerId;
                    cout << "Enter Train ID: ";
                    cin >> trainId;
                    cout << "Enter From Station: ";
                    cin >> from;
                    cout << "Enter To Station: ";
                    cin >> to;
                    cin.ignore();
                    railway.bookTicket(passengerId, trainId, from, to);
                    pause();
                    break;
                }
                case 6: {
                    string ticketId;
                    cout << "Enter Ticket ID: ";
                    cin >> ticketId;
                    cin.ignore();
                    railway.displayTicket(ticketId);
                    pause();
                    break;
                }
                case 7:
                    railway.displaySystemStatistics();
                    pause();
                    break;
                case 0:
                    cout << "\nThank you for using Railway System!\n";
                    return;
                default:
                    cout << "\nInvalid choice!\n";
                    pause();
            }
        }
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    #ifdef _WIN32
        UINT originalCP = GetConsoleOutputCP();
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
        system("cls");
    #else
        system("clear");
    #endif
    
    cout << "\n    +=============================================================+\n";
    cout << "    |                                                             |\n";
    cout << "    |        SMART RAILWAY SCHEDULING SYSTEM                      |\n";
    cout << "    |        Karachi, Pakistan                                    |\n";
    cout << "    |                                                             |\n";
    cout << "    |        100% MANUAL DATA STRUCTURES - NO STL                 |\n";
    cout << "    |        FAST NUCES - DSA Project                             |\n";
    cout << "    |                                                             |\n";
    cout << "    +=============================================================+\n\n";
    
    cout << "  Initializing system";
    for(int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        #ifdef _WIN32
            Sleep(300);
        #else
            usleep(300000);
        #endif
    }
    cout << " Ready!\n\n";
    cout << "  Press Enter to continue...";
    cin.get();
    
    RailwayGraph railway;
    MenuSystem menu(railway);
    menu.run();
    
    #ifdef _WIN32
        SetConsoleOutputCP(originalCP);
        SetConsoleCP(originalCP);
    #endif
    
    return 0;
}
