/*
================================================================================
    SMART RAILWAY SCHEDULING SYSTEM - KARACHI, PAKISTAN
    Advanced Data Structures & Algorithms Project
    
    *** MANUAL IMPLEMENTATION - NO STL CONTAINERS ***
    
    Manually Implemented:
    - Vector (Dynamic Array)
    - Queue (Linked List)
    - Priority Queue (Binary Heap)
    - Hash Table (Quadratic Probing)
    - Hash Set (Open Addressing)
    - Map (Binary Search Tree)
    - Set (Binary Search Tree)
    - Pair (Template Struct)
    - Shared Pointer (Reference Counting)
    - Algorithm Functions (Sort, Find, Reverse)
================================================================================
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cstring>
#include <climits>
#include <cmath>
#include <cstdlib>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::stringstream;

// ==================== MANUAL PAIR IMPLEMENTATION ====================

template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    
    Pair() : first(T1()), second(T2()) {}
    Pair(const T1& f, const T2& s) : first(f), second(s) {}
    
    Pair& operator=(const Pair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
};

template<typename T1, typename T2>
Pair<T1, T2> makePair(const T1& first, const T2& second) {
    return Pair<T1, T2>(first, second);
}

// ==================== MANUAL VECTOR IMPLEMENTATION ====================

template<typename T>
class Vector {
private:
    T* data;
    int capacity;
    int size_;
    
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size_; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    Vector() : data(nullptr), capacity(0), size_(0) {}
    
    explicit Vector(int initialCapacity) : capacity(initialCapacity), size_(0) {
        data = new T[capacity];
    }
    
    Vector(const Vector& other) : capacity(other.capacity), size_(other.size_) {
        data = new T[capacity];
        for (int i = 0; i < size_; i++) {
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
            size_ = other.size_;
            data = new T[capacity];
            for (int i = 0; i < size_; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size_++] = value;
    }
    
    void pop_back() {
        if (size_ > 0) size_--;
    }
    
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
    
    int size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    void clear() {
        size_ = 0;
    }
    
    T* begin() { return data; }
    T* end() { return data + size_; }
    const T* begin() const { return data; }
    const T* end() const { return data + size_; }
    
    void erase(int index) {
        if (index >= 0 && index < size_) {
            for (int i = index; i < size_ - 1; i++) {
                data[i] = data[i + 1];
            }
            size_--;
        }
    }
    
    T& back() { return data[size_ - 1]; }
    const T& back() const { return data[size_ - 1]; }
};

// ==================== MANUAL SHARED POINTER IMPLEMENTATION ====================

template<typename T>
class SharedPtr {
private:
    T* ptr;
    int* refCount;
    
    void release() {
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
            }
        }
    }
    
public:
    SharedPtr() : ptr(nullptr), refCount(nullptr) {}
    
    explicit SharedPtr(T* p) : ptr(p), refCount(new int(1)) {}
    
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) (*refCount)++;
    }
    
    ~SharedPtr() {
        release();
    }
    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) (*refCount)++;
        }
        return *this;
    }
    
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }
    T* operator->() { return ptr; }
    const T* operator->() const { return ptr; }
    
    T* get() { return ptr; }
    const T* get() const { return ptr; }
    
    operator bool() const { return ptr != nullptr; }
};

template<typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) {
    return SharedPtr<T>(new T(args...));
}

// ==================== MANUAL ALGORITHM FUNCTIONS ====================

namespace ManualAlgo {
    
    // QuickSort implementation with function pointer
    template<typename T>
    int partition(T* arr, int low, int high, bool (*comp)(const T&, const T&)) {
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (comp(arr[j], pivot)) {
                i++;
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        T temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }
    
    template<typename T>
    void quickSort(T* arr, int low, int high, bool (*comp)(const T&, const T&)) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSort(arr, low, pi - 1, comp);
            quickSort(arr, pi + 1, high, comp);
        }
    }
    
    template<typename T>
    void sort(Vector<T>& vec, bool (*comp)(const T&, const T&)) {
        if (vec.size() > 1) {
            quickSort(vec.begin(), 0, vec.size() - 1, comp);
        }
    }
    
    template<typename T>
    bool defaultLess(const T& a, const T& b) {
        return a < b;
    }
    
    template<typename T>
    void sort(Vector<T>& vec) {
        sort(vec, defaultLess<T>);
    }
    
    // Find function
    template<typename T>
    int find(const Vector<T>& vec, const T& value) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == value) return i;
        }
        return -1;
    }
    
    // Reverse function
    template<typename T>
    void reverse(Vector<T>& vec) {
        int left = 0;
        int right = vec.size() - 1;
        while (left < right) {
            T temp = vec[left];
            vec[left] = vec[right];
            vec[right] = temp;
            left++;
            right--;
        }
    }
    
    // Remove if function
    template<typename T>
    void removeIf(Vector<T>& vec, bool (*pred)(const T&)) {
        int writeIndex = 0;
        for (int readIndex = 0; readIndex < vec.size(); readIndex++) {
            if (!pred(vec[readIndex])) {
                if (writeIndex != readIndex) {
                    vec[writeIndex] = vec[readIndex];
                }
                writeIndex++;
            }
        }
        while (vec.size() > writeIndex) {
            vec.pop_back();
        }
    }
    
    template<typename T>
    T abs(T value) {
        return value < 0 ? -value : value;
    }
}

// ==================== MANUAL QUEUE IMPLEMENTATION ====================

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    
    Node* frontNode;
    Node* rearNode;
    int size_;
    
public:
    Queue() : frontNode(nullptr), rearNode(nullptr), size_(0) {}
    
    ~Queue() {
        while (!empty()) {
            pop();
        }
    }
    
    void push(const T& value) {
        Node* newNode = new Node(value);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        size_++;
    }
    
    void pop() {
        if (frontNode == nullptr) return;
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        size_--;
    }
    
    T& front() { return frontNode->data; }
    const T& front() const { return frontNode->data; }
    
    bool empty() const { return frontNode == nullptr; }
    int size() const { return size_; }
};

// ==================== MANUAL PRIORITY QUEUE IMPLEMENTATION ====================

template<typename T, typename Compare = bool(*)(const T&, const T&)>
class PriorityQueue {
private:
    Vector<T> heap;
    Compare comp;
    
    // Default comparison (max heap)
    static bool defaultComp(const T& a, const T& b) {
        return a < b;
    }
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && comp(heap[parent(index)], heap[index])) {
            T temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        while (leftChild(index) < size) {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            if (left < size && comp(heap[largest], heap[left])) {
                largest = left;
            }
            if (right < size && comp(heap[largest], heap[right])) {
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
    PriorityQueue() : comp(defaultComp) {}
    explicit PriorityQueue(Compare c) : comp(c) {}
    
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
    
    const T& top() const { return heap[0]; }
    T& top() { return heap[0]; }
    
    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); }
};

// ==================== MANUAL HASH SET IMPLEMENTATION ====================

template<typename K>
class HashSet {
private:
    static const int TABLE_SIZE = 100;
    
    struct HashNode {
        K key;
        bool isOccupied;
        bool isDeleted;
        
        HashNode() : isOccupied(false), isDeleted(false) {}
    };
    
    HashNode* table;
    int count;
    
    int hashFunction(const string& key) const {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % TABLE_SIZE;
        }
        return hash < 0 ? -hash : hash;
    }
    
    int probe(int index, int i) const {
        return (index + i * i) % TABLE_SIZE;
    }
    
public:
    HashSet() : count(0) {
        table = new HashNode[TABLE_SIZE];
    }
    
    ~HashSet() {
        delete[] table;
    }
    
    bool insert(const K& key) {
        if (count >= TABLE_SIZE * 0.7) return false;
        
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied || table[probedIndex].isDeleted) {
                table[probedIndex].key = key;
                table[probedIndex].isOccupied = true;
                table[probedIndex].isDeleted = false;
                count++;
                return true;
            }
            
            if (table[probedIndex].key == key) {
                return true; // Already exists
            }
            i++;
        }
        return false;
    }
    
    bool find(const K& key) const {
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied) return false;
            
            if (table[probedIndex].key == key && !table[probedIndex].isDeleted) {
                return true;
            }
            i++;
        }
        return false;
    }
    
    bool erase(const K& key) {
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied) return false;
            
            if (table[probedIndex].key == key && !table[probedIndex].isDeleted) {
                table[probedIndex].isDeleted = true;
                count--;
                return true;
            }
            i++;
        }
        return false;
    }
    
    int size() const { return count; }
    bool empty() const { return count == 0; }
};

// ==================== MANUAL MAP IMPLEMENTATION (BST) ====================

template<typename K, typename V>
class Map {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        
        Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    int size_;
    
    Node* insertHelper(Node* node, const K& key, const V& value) {
        if (node == nullptr) {
            size_++;
            return new Node(key, value);
        }
        
        if (key < node->key) {
            node->left = insertHelper(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value);
        } else {
            node->value = value; // Update existing
        }
        
        return node;
    }
    
    Node* findHelper(Node* node, const K& key) const {
        if (node == nullptr) return nullptr;
        
        if (key == node->key) return node;
        if (key < node->key) return findHelper(node->left, key);
        return findHelper(node->right, key);
    }
    
    void destroyHelper(Node* node) {
        if (node) {
            destroyHelper(node->left);
            destroyHelper(node->right);
            delete node;
        }
    }
    
    void inorderHelper(Node* node, Vector<Pair<K, V>>& result) const {
        if (node) {
            inorderHelper(node->left, result);
            result.push_back(makePair(node->key, node->value));
            inorderHelper(node->right, result);
        }
    }
    
public:
    Map() : root(nullptr), size_(0) {}
    
    ~Map() {
        destroyHelper(root);
    }
    
    void insert(const K& key, const V& value) {
        root = insertHelper(root, key, value);
    }
    
    bool find(const K& key, V& value) const {
        Node* node = findHelper(root, key);
        if (node) {
            value = node->value;
            return true;
        }
        return false;
    }
    
    V& operator[](const K& key) {
        Node* node = findHelper(root, key);
        if (node) return node->value;
        
        // Insert with default value
        V defaultValue = V();
        root = insertHelper(root, key, defaultValue);
        return findHelper(root, key)->value;
    }
    
    bool contains(const K& key) const {
        return findHelper(root, key) != nullptr;
    }
    
    Vector<Pair<K, V>> getAllEntries() const {
        Vector<Pair<K, V>> result;
        inorderHelper(root, result);
        return result;
    }
    
    int size() const { return size_; }
    bool empty() const { return size_ == 0; }
};

// ==================== MANUAL HASH TABLE IMPLEMENTATION ====================

template<typename K, typename V>
class HashMap {
private:
    static const int TABLE_SIZE = 100;
    
    struct HashNode {
        K key;
        V value;
        bool isOccupied;
        bool isDeleted;
        
        HashNode() : isOccupied(false), isDeleted(false) {}
    };
    
    HashNode* table;
    int count;
    
    int hashFunction(const string& key) const {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % TABLE_SIZE;
        }
        return hash < 0 ? -hash : hash;
    }
    
    int probe(int index, int i) const {
        return (index + i * i) % TABLE_SIZE;
    }
    
public:
    HashMap() : count(0) {
        table = new HashNode[TABLE_SIZE];
    }
    
    ~HashMap() {
        delete[] table;
    }
    
    bool insert(const K& key, const V& value) {
        if (count >= TABLE_SIZE * 0.7) return false;
        
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
            
            if (!table[probedIndex].isOccupied) return false;
            
            if (table[probedIndex].key == key && !table[probedIndex].isDeleted) {
                value = table[probedIndex].value;
                return true;
            }
            i++;
        }
        return false;
    }
    
    bool remove(const K& key) {
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied) return false;
            
            if (table[probedIndex].key == key && !table[probedIndex].isDeleted) {
                table[probedIndex].isDeleted = true;
                count--;
                return true;
            }
            i++;
        }
        return false;
    }
    
    Vector<Pair<K, V>> getAllEntries() const {
        Vector<Pair<K, V>> entries;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied && !table[i].isDeleted) {
                entries.push_back(makePair(table[i].key, table[i].value));
            }
        }
        return entries;
    }
    
    int size() const { return count; }
    bool empty() const { return count == 0; }
};

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
    
    int differenceInMinutes(const Time& other) const {
        return ManualAlgo::abs(toMinutes() - other.toMinutes());
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
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
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
    
    Station(string id, string n, string c, int platforms, 
            double lat, double lon)
        : stationId(id), name(n), city(c), platformCount(platforms),
          coordinates(makePair(lat, lon)) {}
    
    string getId() const { return stationId; }
    string getName() const { return name; }
    string getCity() const { return city; }
    int getPlatforms() const { return platformCount; }
    Pair<double, double> getCoordinates() const { return coordinates; }
    
    void display() const {
        cout << "\n┌─────────────────────────────────────────┐\n";
        cout << "│ Station ID    : " << left << setw(22) << stationId << "│\n";
        cout << "│ Name          : " << setw(22) << name << "│\n";
        cout << "│ City          : " << setw(22) << city << "│\n";
        cout << "│ Platforms     : " << setw(22) << platformCount << "│\n";
        cout << "└─────────────────────────────────────────┘\n";
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
    string getCnic() const { return cnic; }
    string getPhone() const { return phone; }
    int getAge() const { return age; }
    
    void display() const {
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│ Passenger ID  : " << left << setw(22) << passengerId << "│\n";
        cout << "│ Name          : " << setw(22) << name << "│\n";
        cout << "│ CNIC          : " << setw(22) << cnic << "│\n";
        cout << "│ Phone         : " << setw(22) << phone << "│\n";
        cout << "│ Age           : " << setw(22) << age << "│\n";
        cout << "└─────────────────────────────────────────┘\n";
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
    string getPassengerId() const { return passengerId; }
    string getTrainId() const { return trainId; }
    string getFrom() const { return fromStation; }
    string getTo() const { return toStation; }
    double getFare() const { return fare; }
    bool getBookingStatus() const { return isBooked; }
    
    void cancelTicket() { isBooked = false; }
    
    void display() const {
        cout << "\n╔═══════════════════════════════════════════╗\n";
        cout << "║           RAILWAY TICKET                  ║\n";
        cout << "╠═══════════════════════════════════════════╣\n";
        cout << "║ Ticket ID     : " << left << setw(24) << ticketId << "║\n";
        cout << "║ Passenger ID  : " << setw(24) << passengerId << "║\n";
        cout << "║ Train ID      : " << setw(24) << trainId << "║\n";
        cout << "║ From          : " << setw(24) << fromStation << "║\n";
        cout << "║ To            : " << setw(24) << toStation << "║\n";
        cout << "║ Date          : " << setw(24) << journeyDate.toString() << "║\n";
        cout << "║ Departure     : " << setw(24) << departureTime.toString() << "║\n";
        cout << "║ Seat          : " << setw(24) << seatNumber << "║\n";
        cout << "║ Fare          : PKR " << setw(20) << fixed << setprecision(2) << fare << "║\n";
        cout << "║ Status        : " << setw(24) << (isBooked ? "CONFIRMED" : "CANCELLED") << "║\n";
        cout << "╚═══════════════════════════════════════════╝\n";
    }
};

// Forward declaration
class Train;

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

// ==================== DIJKSTRA RESULT ====================

struct PathInfo {
    Vector<string> path;
    double totalDistance;
    int totalTime;
    double totalFare;
    
    PathInfo() : totalDistance(0), totalTime(0), totalFare(0) {}
};

// Comparison functions for PathInfo
bool pathInfoDistanceComp(const PathInfo& a, const PathInfo& b) {
    return a.totalDistance < b.totalDistance;
}

// ==================== TRAIN CLASS ====================

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
    string getType() const { return trainType; }
    int getPriority() const { return priority; }
    int getDelay() const { return delayMinutes; }
    int getAvailableSeats() const { return availableSeats; }
    Vector<string> getRoute() const { return route; }
    Map<string, Time> getSchedule() const { return schedule; }
    
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
        Time t;
        if (schedule.find(stationId, t)) {
            return t.addMinutes(delayMinutes);
        }
        return Time(0, 0);
    }
    
    void display() const {
        cout << "\n╔════════════════════════════════════════════╗\n";
        cout << "║            TRAIN INFORMATION               ║\n";
        cout << "╠════════════════════════════════════════════╣\n";
        cout << "║ Train ID      : " << left << setw(25) << trainId << "║\n";
        cout << "║ Name          : " << setw(25) << trainName << "║\n";
        cout << "║ Type          : " << setw(25) << trainType << "║\n";
        cout << "║ Total Seats   : " << setw(25) << totalSeats << "║\n";
        cout << "║ Available     : " << setw(25) << availableSeats << "║\n";
        cout << "║ Priority      : " << setw(25) << priority << "║\n";
        cout << "║ Delay         : " << setw(22) << delayMinutes << " min║\n";
        cout << "╠════════════════════════════════════════════╣\n";
        cout << "║ Route & Schedule:                          ║\n";
        for (int i = 0; i < route.size(); i++) {
            Time t;
            schedule.find(route[i], t);
            Time actualTime = t.addMinutes(delayMinutes);
            cout << "║  → " << left << setw(25) << route[i]
                 << setw(10) << actualTime.toString() << "   ║\n";
        }
        cout << "╚════════════════════════════════════════════╝\n";
    }
};

// Comparison functions for Train pairs
bool trainPriorityComp(const Pair<string, SharedPtr<Train>>& a,
                       const Pair<string, SharedPtr<Train>>& b) {
    return a.second->getPriority() > b.second->getPriority();
}

bool trainTimeComp(const Pair<Time, SharedPtr<Train>>& a,
                   const Pair<Time, SharedPtr<Train>>& b) {
    return a.first < b.first;
}

// ==================== PRIORITY QUEUE NODE ====================

struct TrainPriority {
    SharedPtr<Train> train;
    Time scheduledTime;
    
    TrainPriority() {}
    
    TrainPriority(SharedPtr<Train> t, Time time)
        : train(t), scheduledTime(time) {}
    
    bool operator<(const TrainPriority& other) const {
        if (train->getPriority() != other.train->getPriority()) {
            return train->getPriority() < other.train->getPriority();
        }
        return scheduledTime > other.scheduledTime;
    }
};

bool trainPriorityNodeComp(const TrainPriority& a, const TrainPriority& b) {
    return a < b;
}

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
                return priority < other.priority;
            }
            return arrivalTime > other.arrivalTime;
        }
    };
    
    static bool queueNodeComp(const QueueNode& a, const QueueNode& b) {
        return a < b;
    }
    
    PriorityQueue<QueueNode, bool(*)(const QueueNode&, const QueueNode&)> pq;
    
public:
    PassengerQueue() : pq(queueNodeComp) {}
    
    void enqueue(const Passenger& p, int priority, Time arrivalTime) {
        pq.push(QueueNode(p, priority, arrivalTime));
    }
    
    Passenger dequeue() {
        if (pq.empty()) {
            throw "Queue is empty";
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
    
    void display() const {
        if (pq.empty()) {
            cout << "Queue is empty.\n";
            return;
        }
        
        cout << "\n╔════════════════════════════════════════════╗\n";
        cout << "║         PASSENGER WAITING QUEUE            ║\n";
        cout << "║   (Queue contains " << setw(2) << pq.size() << " passengers)           ║\n";
        cout << "╚════════════════════════════════════════════╝\n";
    }
};

// ==================== RAILWAY GRAPH SYSTEM ====================

class RailwayGraph {
private:
    HashMap<string, Station> stations;
    HashMap<string, Vector<Edge>> adjacencyList;
    HashMap<string, SharedPtr<Train>> trains;
    HashMap<string, Passenger> passengers;
    HashMap<string, Ticket> tickets;
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
        addStation(Station("GWDR", "Gawader", "Karachi", 2, 24.8200, 67.0600));
        addStation(Station("SHAH", "Shahrah-e-Faisal", "Karachi", 3, 24.8850, 67.0800));
        addStation(Station("KMR", "Korangi", "Karachi", 2, 24.8250, 67.1450));
        addStation(Station("LYRI", "Lyari", "Karachi", 2, 24.8717, 66.9972));
        addStation(Station("SDHR", "Saddar", "Karachi", 4, 24.8546, 67.0189));
        
        addEdge("KCTY", "KC", 1.2, 5, 20);
        addEdge("KC", "DRH", 8.5, 15, 50);
        addEdge("DRH", "MLR", 6.8, 12, 40);
        addEdge("MLR", "LNDI", 5.2, 10, 35);
        addEdge("LNDI", "BQS", 8.3, 18, 60);
        
        addEdge("KCTY", "SDHR", 2.5, 8, 25);
        addEdge("SDHR", "LYRI", 3.1, 10, 30);
        addEdge("LYRI", "SITE", 4.2, 12, 35);
        addEdge("SITE", "ORG", 5.5, 15, 40);
        addEdge("ORG", "SAL", 6.0, 18, 45);
        addEdge("SAL", "JCL", 4.3, 10, 35);
        addEdge("JCL", "KC", 3.8, 8, 30);
        
        addEdge("KC", "SDHR", 2.0, 6, 25);
        addEdge("DRH", "SHAH", 3.5, 8, 30);
        addEdge("SHAH", "KMR", 5.0, 12, 40);
        addEdge("KMR", "LNDI", 4.5, 10, 35);
        addEdge("MLR", "KMR", 3.8, 8, 30);
        addEdge("SITE", "GWDR", 2.5, 7, 25);
        addEdge("GWDR", "LYRI", 3.0, 8, 25);
        
        addEdge("KCTY", "JCL", 2.8, 7, 25);
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
        
        SharedPtr<Train> train2 = makeShared<Train>("TN002", "Circular Express", "Express", 450, 9);
        train2->addToRoute("KCTY", Time(7, 0));
        train2->addToRoute("SDHR", Time(7, 10));
        train2->addToRoute("LYRI", Time(7, 25));
        train2->addToRoute("SITE", Time(7, 40));
        train2->addToRoute("ORG", Time(8, 0));
        train2->addToRoute("SAL", Time(8, 20));
        trains.insert("TN002", train2);
        
        SharedPtr<Train> train3 = makeShared<Train>("TN003", "Local Passenger", "Passenger", 600, 5);
        train3->addToRoute("KC", Time(8, 0));
        train3->addToRoute("DRH", Time(8, 20));
        train3->addToRoute("SHAH", Time(8, 35));
        train3->addToRoute("KMR", Time(8, 50));
        train3->addToRoute("LNDI", Time(9, 5));
        trains.insert("TN003", train3);
        
        SharedPtr<Train> train4 = makeShared<Train>("TN004", "Metro Line", "Metro", 400, 8);
        train4->addToRoute("KCTY", Time(9, 0));
        train4->addToRoute("JCL", Time(9, 10));
        train4->addToRoute("SAL", Time(9, 25));
        train4->addToRoute("DRH", Time(9, 50));
        train4->addToRoute("MLR", Time(10, 10));
        trains.insert("TN004", train4);
        
        SharedPtr<Train> train5 = makeShared<Train>("TN005", "Business Express", "Express", 300, 10);
        train5->addToRoute("KCTY", Time(10, 0));
        train5->addToRoute("KC", Time(10, 8));
        train5->addToRoute("SDHR", Time(10, 16));
        train5->addToRoute("DRH", Time(10, 35));
        trains.insert("TN005", train5);
    }
    
    void addStation(const Station& station) {
        stations.insert(station.getId(), station);
        Vector<Edge> emptyEdges;
        adjacencyList.insert(station.getId(), emptyEdges);
    }
    
    void addEdge(const string& from, const string& to, double distance, 
                 int time, double fare) {
        Vector<Edge> edges1, edges2;
        adjacencyList.find(from, edges1);
        adjacencyList.find(to, edges2);
        
        edges1.push_back(Edge(to, distance, time, fare));
        edges2.push_back(Edge(from, distance, time, fare));
        
        adjacencyList.insert(from, edges1);
        adjacencyList.insert(to, edges2);
    }
    
    void displayStation(const string& stationId) {
        Station s;
        if (stations.find(stationId, s)) {
            s.display();
        } else {
            cout << "Station not found!\n";
        }
    }
    
    void displayAllStations() {
        Vector<Pair<string, Station>> allStations = stations.getAllEntries();
        
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║              KARACHI RAILWAY STATIONS                    ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        cout << "║ ID    │ Name                    │ Platforms │ City      ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < allStations.size(); i++) {
            const Station& s = allStations[i].second;
            cout << "║ " << left << setw(6) << s.getId() 
                 << "│ " << setw(24) << s.getName()
                 << "│ " << setw(10) << s.getPlatforms()
                 << "│ " << setw(10) << s.getCity() << "║\n";
        }
        
        cout << "╚══════════════════════════════════════════════════════════╝\n";
    }
    
    void displayConnections(const string& stationId) {
        Vector<Edge> edges;
        if (!adjacencyList.find(stationId, edges)) {
            cout << "Station not found!\n";
            return;
        }
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║  Connections from " << left << setw(34) << stationId << "║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        cout << "║ To      │ Distance(km) │ Time(min) │ Fare(PKR)      ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < edges.size(); i++) {
            cout << "║ " << left << setw(8) << edges[i].destination
                 << "│ " << setw(13) << fixed << setprecision(1) << edges[i].distance
                 << "│ " << setw(10) << edges[i].travelTime
                 << "│ " << setw(15) << setprecision(2) << edges[i].fare << "║\n";
        }
        
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    PathInfo dijkstraShortestPath(const string& source, const string& destination,
                                  bool byDistance = true) {
        PathInfo result;
        
        Station s1, s2;
        if (!stations.find(source, s1) || !stations.find(destination, s2)) {
            cout << "Invalid source or destination!\n";
            return result;
        }
        
        HashMap<string, double> dist;
        HashMap<string, int> time;
        HashMap<string, double> fare;
        HashMap<string, string> parent;
        HashSet<string> visited;
        
        Vector<Pair<string, Station>> allStations = stations.getAllEntries();
        for (int i = 0; i < allStations.size(); i++) {
            dist.insert(allStations[i].first, 1e9);
            time.insert(allStations[i].first, INT_MAX);
            fare.insert(allStations[i].first, 1e9);
        }
        
        dist.insert(source, 0);
        time.insert(source, 0);
        fare.insert(source, 0);
        
        struct DijkstraNode {
            double distance;
            string stationId;
            
            bool operator<(const DijkstraNode& other) const {
                return distance > other.distance;
            }
        };
        
        auto dijkstraComp = [](const DijkstraNode& a, const DijkstraNode& b) {
            return a < b;
        };
        
        PriorityQueue<DijkstraNode, bool(*)(const DijkstraNode&, const DijkstraNode&)> pq(dijkstraComp);
        
        DijkstraNode start;
        start.distance = 0;
        start.stationId = source;
        pq.push(start);
        
        while (!pq.empty()) {
            DijkstraNode current = pq.top();
            pq.pop();
            
            string u = current.stationId;
            
            if (visited.find(u)) continue;
            visited.insert(u);
            
            if (u == destination) break;
            
            Vector<Edge> edges;
            adjacencyList.find(u, edges);
            
            for (int i = 0; i < edges.size(); i++) {
                string v = edges[i].destination;
                double weight = byDistance ? edges[i].distance : edges[i].travelTime;
                
                double uDist;
                dist.find(u, uDist);
                
                if (!visited.find(v)) {
                    double vDist;
                    dist.find(v, vDist);
                    
                    if (uDist + weight < vDist) {
                        dist.insert(v, uDist + weight);
                        
                        int uTime, vTime;
                        time.find(u, uTime);
                        time.insert(v, uTime + edges[i].travelTime);
                        
                        double uFare, vFare;
                        fare.find(u, uFare);
                        fare.insert(v, uFare + edges[i].fare);
                        
                        parent.insert(v, u);
                        
                        DijkstraNode nextNode;
                        nextNode.distance = uDist + weight;
                        nextNode.stationId = v;
                        pq.push(nextNode);
                    }
                }
            }
        }
        
        double finalDist;
        if (!dist.find(destination, finalDist) || finalDist >= 1e9) {
            cout << "No path found!\n";
            return result;
        }
        
        string current = destination;
        while (current != source) {
            result.path.push_back(current);
            string p;
            parent.find(current, p);
            current = p;
        }
        result.path.push_back(source);
        ManualAlgo::reverse(result.path);
        
        dist.find(destination, result.totalDistance);
        time.find(destination, result.totalTime);
        fare.find(destination, result.totalFare);
        
        return result;
    }
    
    void displayShortestPath(const string& source, const string& destination) {
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║           SHORTEST PATH ANALYSIS                       ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        PathInfo pathByDist = dijkstraShortestPath(source, destination, true);
        cout << "║ By Distance:                                           ║\n";
        cout << "║ Route: ";
        for (int i = 0; i < pathByDist.path.size(); i++) {
            cout << pathByDist.path[i];
            if (i < pathByDist.path.size() - 1) cout << " → ";
        }
        cout << "\n║ Total Distance: " << fixed << setprecision(2) 
             << pathByDist.totalDistance << " km\n";
        cout << "║ Total Time: " << pathByDist.totalTime << " minutes\n";
        cout << "║ Total Fare: PKR " << pathByDist.totalFare << "\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        PathInfo pathByTime = dijkstraShortestPath(source, destination, false);
        cout << "║ By Time:                                               ║\n";
        cout << "║ Route: ";
        for (int i = 0; i < pathByTime.path.size(); i++) {
            cout << pathByTime.path[i];
            if (i < pathByTime.path.size() - 1) cout << " → ";
        }
        cout << "\n║ Total Distance: " << fixed << setprecision(2) 
             << pathByTime.totalDistance << " km\n";
        cout << "║ Total Time: " << pathByTime.totalTime << " minutes\n";
        cout << "║ Total Fare: PKR " << pathByTime.totalFare << "\n";
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    void findAllPathsDFS(const string& current, const string& destination,
                        HashSet<string>& visited,
                        Vector<string>& currentPath,
                        Vector<PathInfo>& allPaths,
                        double currentDist, int currentTime, double currentFare) {
        
        visited.insert(current);
        currentPath.push_back(current);
        
        if (current == destination) {
            PathInfo path;
            path.path = currentPath;
            path.totalDistance = currentDist;
            path.totalTime = currentTime;
            path.totalFare = currentFare;
            allPaths.push_back(path);
        } else {
            Vector<Edge> edges;
            adjacencyList.find(current, edges);
            
            for (int i = 0; i < edges.size(); i++) {
                if (!visited.find(edges[i].destination)) {
                    findAllPathsDFS(edges[i].destination, destination, visited, currentPath,
                                   allPaths, currentDist + edges[i].distance,
                                   currentTime + edges[i].travelTime,
                                   currentFare + edges[i].fare);
                }
            }
        }
        
        currentPath.pop_back();
        visited.erase(current);
    }
    
    Vector<PathInfo> findAllPaths(const string& source, const string& destination,
                                   int maxPaths = 10) {
        Vector<PathInfo> allPaths;
        HashSet<string> visited;
        Vector<string> currentPath;
        
        Station s1, s2;
        if (!stations.find(source, s1) || !stations.find(destination, s2)) {
            cout << "Invalid source or destination!\n";
            return allPaths;
        }
        
        findAllPathsDFS(source, destination, visited, currentPath, allPaths, 0, 0, 0);
        
        // Sort by distance using function pointer
        ManualAlgo::sort(allPaths, pathInfoDistanceComp);
        
        // Keep only top paths
        while (allPaths.size() > maxPaths) {
            allPaths.pop_back();
        }
        
        return allPaths;
    }
    
    void displayAllPaths(const string& source, const string& destination) {
        Vector<PathInfo> paths = findAllPaths(source, destination);
        
        if (paths.empty()) {
            cout << "No paths found!\n";
            return;
        }
        
        cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        cout << "║         ALL POSSIBLE ROUTES FROM " << source << " TO " << destination << "          ║\n";
        cout << "╠═══════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < paths.size(); i++) {
            cout << "║ Route " << (i + 1) << ":                                                ║\n";
            cout << "║ Path: ";
            for (int j = 0; j < paths[i].path.size(); j++) {
                cout << paths[i].path[j];
                if (j < paths[i].path.size() - 1) cout << " → ";
            }
            cout << "\n║ Distance: " << fixed << setprecision(2) 
                 << paths[i].totalDistance << " km │ ";
            cout << "Time: " << paths[i].totalTime << " min │ ";
            cout << "Fare: PKR " << paths[i].totalFare << "\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
        }
        
        cout << "╚═══════════════════════════════════════════════════════════╝\n";
    }
    
    void displayTrain(const string& trainId) {
        SharedPtr<Train> train;
        if (trains.find(trainId, train)) {
            train->display();
        } else {
            cout << "Train not found!\n";
        }
    }
    
    void displayAllTrains() {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        
        if (allTrains.empty()) {
            cout << "No trains in the system.\n";
            return;
        }
        
        cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
        cout << "║                    ALL TRAINS IN SYSTEM                       ║\n";
        cout << "╠═══════════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < allTrains.size(); i++) {
            allTrains[i].second->display();
        }
    }
    
    void setTrainDelay(const string& trainId, int delayMinutes) {
        SharedPtr<Train> train;
        if (trains.find(trainId, train)) {
            train->setDelay(delayMinutes);
            cout << "Delay of " << delayMinutes << " minutes set for train " 
                 << trainId << "\n";
        } else {
            cout << "Train not found!\n";
        }
    }
    
    string addPassenger(const string& name, const string& cnic, 
                       const string& phone, int age) {
        stringstream ss;
        ss << "P" << passengerCounter++;
        string passengerId = ss.str();
        
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
    
    void addPassengerToQueue(const string& stationId, const string& passengerId,
                            int priority = 5) {
        Passenger p;
        if (!passengers.find(passengerId, p)) {
            cout << "Passenger not found!\n";
            return;
        }
        
        Station s;
        if (!stations.find(stationId, s)) {
            cout << "Station not found!\n";
            return;
        }
        
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Time currentTime(ltm->tm_hour, ltm->tm_min);
        
        stationQueues[stationId].enqueue(p, priority, currentTime);
        cout << "Passenger " << p.getName() << " added to queue at " 
             << stationId << "\n";
    }
    
    void processPassengerQueue(const string& stationId) {
        if (stationQueues[stationId].isEmpty()) {
            cout << "No passengers in queue at " << stationId << "\n";
            return;
        }
        
        Passenger p = stationQueues[stationId].dequeue();
        cout << "Processing passenger: " << p.getName() << "\n";
    }
    
    void displayStationQueue(const string& stationId) {
        cout << "\nQueue at Station: " << stationId << "\n";
        stationQueues[stationId].display();
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
        
        Vector<string> route = train->getRoute();
        int fromIdx = ManualAlgo::find(route, from);
        int toIdx = ManualAlgo::find(route, to);
        
        if (fromIdx == -1 || toIdx == -1 || fromIdx >= toIdx) {
            cout << "Train does not cover this route!\n";
            return "";
        }
        
        if (!train->bookSeat()) {
            cout << "No seats available!\n";
            return "";
        }
        
        PathInfo path = dijkstraShortestPath(from, to, true);
        
        stringstream ss;
        ss << "T" << ticketCounter++;
        string ticketId = ss.str();
        
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Date currentDate(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
        
        Time departureTime = train->getArrivalTime(from);
        
        stringstream ss2;
        ss2 << "S-" << (train->getAvailableSeats() + 1);
        string seatNumber = ss2.str();
        
        Ticket ticket(ticketId, passengerId, trainId, from, to,
                     currentDate, departureTime, path.totalFare, seatNumber);
        
        tickets.insert(ticketId, ticket);
        
        cout << "\n✓ Ticket booked successfully!\n";
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
    
    void cancelTicket(const string& ticketId) {
        Ticket t;
        if (tickets.find(ticketId, t)) {
            if (!t.getBookingStatus()) {
                cout << "Ticket already cancelled!\n";
                return;
            }
            
            SharedPtr<Train> train;
            if (trains.find(t.getTrainId(), train)) {
                train->releaseSeat();
            }
            
            t.cancelTicket();
            tickets.insert(ticketId, t);
            cout << "Ticket " << ticketId << " cancelled successfully!\n";
        } else {
            cout << "Ticket not found!\n";
        }
    }
    
    void displayTrainsByPriority() {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        
        // Sort by priority using function pointer
        ManualAlgo::sort(allTrains, trainPriorityComp);
        
        cout << "\n╔═══════════════════════════════════════════════════════╗\n";
        cout << "║         TRAINS SORTED BY PRIORITY                     ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        cout << "║ ID    │ Name              │ Priority │ Delay(min)   ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < allTrains.size(); i++) {
            SharedPtr<Train> train = allTrains[i].second;
            cout << "║ " << left << setw(6) << train->getId()
                 << "│ " << setw(18) << train->getName()
                 << "│ " << setw(9) << train->getPriority()
                 << "│ " << setw(13) << train->getDelay() << "║\n";
        }
        
        cout << "╚═══════════════════════════════════════════════════════╝\n";
    }
    
    void displayTrainSchedule(const string& stationId) {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        Vector<Pair<Time, SharedPtr<Train>>> schedule;
        
        for (int i = 0; i < allTrains.size(); i++) {
            SharedPtr<Train> train = allTrains[i].second;
            Map<string, Time> trainSchedule = train->getSchedule();
            
            Time t;
            if (trainSchedule.find(stationId, t)) {
                Time arrivalTime = train->getArrivalTime(stationId);
                schedule.push_back(makePair(arrivalTime, train));
            }
        }
        
        // Sort by time using function pointer
        ManualAlgo::sort(schedule, trainTimeComp);
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║       TRAIN SCHEDULE AT " << left << setw(28) << stationId << "║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        cout << "║ Time  │ Train ID │ Train Name          │ Delay       ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < schedule.size(); i++) {
            Time t = schedule[i].first;
            SharedPtr<Train> train = schedule[i].second;
            cout << "║ " << setw(6) << t.toString()
                 << "│ " << setw(9) << train->getId()
                 << "│ " << setw(20) << train->getName()
                 << "│ " << setw(8) << train->getDelay() << " min║\n";
        }
        
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    void displaySystemStatistics() {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        Vector<Pair<string, Ticket>> allTickets = tickets.getAllEntries();
        Vector<Pair<string, Passenger>> allPassengers = passengers.getAllEntries();
        
        int totalSeats = 0;
        int bookedSeats = 0;
        double totalRevenue = 0;
        int activeTickets = 0;
        
        for (int i = 0; i < allTrains.size(); i++) {
            SharedPtr<Train> train = allTrains[i].second;
            totalSeats += 500;
            bookedSeats += (500 - train->getAvailableSeats());
        }
        
        for (int i = 0; i < allTickets.size(); i++) {
            if (allTickets[i].second.getBookingStatus()) {
                totalRevenue += allTickets[i].second.getFare();
                activeTickets++;
            }
        }
        
        Vector<Pair<string, Station>> allStations = stations.getAllEntries();
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║           RAILWAY SYSTEM STATISTICS                    ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        cout << "║ Total Stations        : " << left << setw(28) 
             << allStations.size() << "║\n";
        cout << "║ Total Trains          : " << setw(28) 
             << allTrains.size() << "║\n";
        cout << "║ Total Passengers      : " << setw(28) 
             << allPassengers.size() << "║\n";
        cout << "║ Active Tickets        : " << setw(28) 
             << activeTickets << "║\n";
        cout << "║ Total Seats           : " << setw(28) 
             << totalSeats << "║\n";
        cout << "║ Booked Seats          : " << setw(28) 
             << bookedSeats << "║\n";
        cout << "║ Occupancy Rate        : " << setw(24) 
             << fixed << setprecision(2) 
             << (totalSeats > 0 ? (bookedSeats * 100.0 / totalSeats) : 0) 
             << " %  ║\n";
        cout << "║ Total Revenue         : PKR " << setw(24) 
             << setprecision(2) << totalRevenue << "║\n";
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    void searchTrainsByRoute(const string& stationId) {
        Vector<Pair<string, SharedPtr<Train>>> allTrains = trains.getAllEntries();
        Vector<SharedPtr<Train>> matchingTrains;
        
        for (int i = 0; i < allTrains.size(); i++) {
            Vector<string> route = allTrains[i].second->getRoute();
            if (ManualAlgo::find(route, stationId) != -1) {
                matchingTrains.push_back(allTrains[i].second);
            }
        }
        
        if (matchingTrains.empty()) {
            cout << "No trains pass through " << stationId << "\n";
            return;
        }
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║    TRAINS PASSING THROUGH " << left << setw(27) << stationId << "║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < matchingTrains.size(); i++) {
            cout << "║ " << setw(8) << matchingTrains[i]->getId() 
                 << " │ " << setw(43) << matchingTrains[i]->getName() << "║\n";
        }
        
        cout << "╚════════════════════════════════════════════════════════╝\n";
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
    
    void displayHeader() {
        cout << "\n";
        cout << "╔═══════════════════════════════════════════════════════════╗\n";
        cout << "║     SMART RAILWAY SCHEDULING SYSTEM - KARACHI             ║\n";
        cout << "║              Pakistan Railways Network                    ║\n";
        cout << "╚═══════════════════════════════════════════════════════════╝\n";
    }
    
public:
    MenuSystem(RailwayGraph& rg) : railway(rg) {}
    
    void run() {
        while (true) {
            clearScreen();
            displayHeader();
            displayMainMenu();
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1: stationManagementMenu(); break;
                case 2: trainManagementMenu(); break;
                case 3: passengerManagementMenu(); break;
                case 4: ticketManagementMenu(); break;
                case 5: routeAnalysisMenu(); break;
                case 6: scheduleManagementMenu(); break;
                case 7: queueManagementMenu(); break;
                case 8: statisticsMenu(); break;
                case 0:
                    cout << "\nThank you for using Railway System!\n";
                    return;
                default:
                    cout << "\nInvalid choice!\n";
                    pause();
            }
        }
    }
    
    void displayMainMenu() {
        cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        cout << "║                      MAIN MENU                            ║\n";
        cout << "╠═══════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Station Management                                    ║\n";
        cout << "║  2. Train Management                                      ║\n";
        cout << "║  3. Passenger Management                                  ║\n";
        cout << "║  4. Ticket Management                                     ║\n";
        cout << "║  5. Route Analysis (Dijkstra & All Paths)                 ║\n";
        cout << "║  6. Schedule Management                                   ║\n";
        cout << "║  7. Queue Management                                      ║\n";
        cout << "║  8. Statistics & Reports                                  ║\n";
        cout << "║  0. Exit                                                  ║\n";
        cout << "╚═══════════════════════════════════════════════════════════╝\n";
    }
    
    void stationManagementMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║               STATION MANAGEMENT                          ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. View All Stations                                     ║\n";
            cout << "║  2. View Station Details                                  ║\n";
            cout << "║  3. View Station Connections                              ║\n";
            cout << "║  4. Search Trains by Station                              ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1:
                    railway.displayAllStations();
                    pause();
                    break;
                case 2: {
                    string stationId;
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    railway.displayStation(stationId);
                    pause();
                    break;
                }
                case 3: {
                    string stationId;
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    railway.displayConnections(stationId);
                    pause();
                    break;
                }
                case 4: {
                    string stationId;
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    railway.searchTrainsByRoute(stationId);
                    pause();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void trainManagementMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║                TRAIN MANAGEMENT                           ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. View All Trains                                       ║\n";
            cout << "║  2. View Train Details                                    ║\n";
            cout << "║  3. View Trains by Priority                               ║\n";
            cout << "║  4. Set Train Delay                                       ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1:
                    railway.displayAllTrains();
                    pause();
                    break;
                case 2: {
                    string trainId;
                    cout << "Enter Train ID: ";
                    cin >> trainId;
                    railway.displayTrain(trainId);
                    pause();
                    break;
                }
                case 3:
                    railway.displayTrainsByPriority();
                    pause();
                    break;
                case 4: {
                    string trainId;
                    int delay;
                    cout << "Enter Train ID: ";
                    cin >> trainId;
                    cout << "Enter Delay (minutes): ";
                    cin >> delay;
                    railway.setTrainDelay(trainId, delay);
                    pause();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void passengerManagementMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║              PASSENGER MANAGEMENT                         ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. Register New Passenger                                ║\n";
            cout << "║  2. View Passenger Details                                ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: {
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
                    
                    string passengerId = railway.addPassenger(name, cnic, phone, age);
                    cout << "\n✓ Passenger registered successfully!\n";
                    cout << "Passenger ID: " << passengerId << "\n";
                    pause();
                    break;
                }
                case 2: {
                    string passengerId;
                    cout << "Enter Passenger ID: ";
                    cin >> passengerId;
                    railway.displayPassenger(passengerId);
                    pause();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void ticketManagementMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║               TICKET MANAGEMENT                           ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. Book Ticket                                           ║\n";
            cout << "║  2. View Ticket                                           ║\n";
            cout << "║  3. Cancel Ticket                                         ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: {
                    string passengerId, trainId, from, to;
                    
                    cout << "Enter Passenger ID: ";
                    cin >> passengerId;
                    cout << "Enter Train ID: ";
                    cin >> trainId;
                    cout << "Enter From Station: ";
                    cin >> from;
                    cout << "Enter To Station: ";
                    cin >> to;
                    
                    string ticketId = railway.bookTicket(passengerId, trainId, from, to);
                    if (ticketId != "") {
                        railway.displayTicket(ticketId);
                    }
                    pause();
                    break;
                }
                case 2: {
                    string ticketId;
                    cout << "Enter Ticket ID: ";
                    cin >> ticketId;
                    railway.displayTicket(ticketId);
                    pause();
                    break;
                }
                case 3: {
                    string ticketId;
                    cout << "Enter Ticket ID: ";
                    cin >> ticketId;
                    railway.cancelTicket(ticketId);
                    pause();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void routeAnalysisMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║          ROUTE ANALYSIS (ADVANCED ALGORITHMS)             ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. Find Shortest Path (Dijkstra)                         ║\n";
            cout << "║  2. Find All Possible Paths (DFS)                         ║\n";
            cout << "║  3. Compare All Algorithms                                ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            string from, to;
            
            if (choice >= 1 && choice <= 3) {
                cout << "Enter Source Station: ";
                cin >> from;
                cout << "Enter Destination Station: ";
                cin >> to;
            }
            
            switch (choice) {
                case 1:
                    railway.displayShortestPath(from, to);
                    pause();
                    break;
                case 2:
                    railway.displayAllPaths(from, to);
                    pause();
                    break;
                case 3:
                    railway.displayShortestPath(from, to);
                    cout << "\n";
                    railway.displayAllPaths(from, to);
                    pause();
                    break;
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void scheduleManagementMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║             SCHEDULE MANAGEMENT                           ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. View Station Schedule                                 ║\n";
            cout << "║  2. View Train Schedule                                   ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: {
                    string stationId;
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    railway.displayTrainSchedule(stationId);
                    pause();
                    break;
                }
                case 2: {
                    string trainId;
                    cout << "Enter Train ID: ";
                    cin >> trainId;
                    railway.displayTrain(trainId);
                    pause();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void queueManagementMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║              QUEUE MANAGEMENT                             ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. Add Passenger to Queue                                ║\n";
            cout << "║  2. Process Next Passenger                                ║\n";
            cout << "║  3. View Station Queue                                    ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: {
                    string stationId, passengerId;
                    int priority;
                    
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    cout << "Enter Passenger ID: ";
                    cin >> passengerId;
                    cout << "Enter Priority (1-10, higher = more important): ";
                    cin >> priority;
                    
                    railway.addPassengerToQueue(stationId, passengerId, priority);
                    pause();
                    break;
                }
                case 2: {
                    string stationId;
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    railway.processPassengerQueue(stationId);
                    pause();
                    break;
                }
                case 3: {
                    string stationId;
                    cout << "Enter Station ID: ";
                    cin >> stationId;
                    railway.displayStationQueue(stationId);
                    pause();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    pause();
            }
        }
    }
    
    void statisticsMenu() {
        while (true) {
            clearScreen();
            displayHeader();
            cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
            cout << "║            STATISTICS & REPORTS                           ║\n";
            cout << "╠═══════════════════════════════════════════════════════════╣\n";
            cout << "║  1. System Statistics                                     ║\n";
            cout << "║  2. Network Overview                                      ║\n";
            cout << "║  0. Back to Main Menu                                     ║\n";
            cout << "╚═══════════════════════════════════════════════════════════╝\n";
            
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1:
                    railway.displaySystemStatistics();
                    pause();
                    break;
                case 2:
                    railway.displayAllStations();
                    cout << "\n";
                    railway.displayAllTrains();
                    pause();
                    break;
                default:
                    cout << "Invalid choice!\n";
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
    #endif
    
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    
    cout << "\n";
    cout << "    +=================================================================+\n";
    cout << "    |                                                                 |\n";
    cout << "    |        SMART RAILWAY SCHEDULING SYSTEM                          |\n";
    cout << "    |        Karachi, Pakistan                                        |\n";
    cout << "    |                                                                 |\n";
    cout << "    |        Advanced Data Structures & Algorithms                    |\n";
    cout << "    |        FAST NUCES - Semester 3                                  |\n";
    cout << "    |        *** MANUAL IMPLEMENTATION - NO STL ***                   |\n";
    cout << "    |                                                                 |\n";
    cout << "    +=================================================================+\n";
    cout << endl;
    
    cout << "\n  Initializing system";
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
