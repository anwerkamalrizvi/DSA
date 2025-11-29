/*
================================================================================
    SMART RAILWAY SCHEDULING SYSTEM - KARACHI, PAKISTAN
    Advanced Data Structures & Algorithms Project
    
    Features:
    - Graph-based station network
    - Dijkstra's shortest path algorithm
    - All possible paths finding (DFS/BFS)
    - Priority queue for train scheduling
    - Hash table for O(1) lookups
    - Queue for passenger management
    - Advanced sorting algorithms
    - Real-time delay management
================================================================================
*/
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <memory>
#include <functional>
#include <climits>

using namespace std;

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
        return abs(toMinutes() - other.toMinutes());
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
    pair<double, double> coordinates; // latitude, longitude
    
public:
    Station() : platformCount(0), coordinates({0.0, 0.0}) {}
    
    Station(string id, string n, string c, int platforms, 
            double lat, double lon)
        : stationId(id), name(n), city(c), platformCount(platforms),
          coordinates({lat, lon}) {}
    
    string getId() const { return stationId; }
    string getName() const { return name; }
    string getCity() const { return city; }
    int getPlatforms() const { return platformCount; }
    pair<double, double> getCoordinates() const { return coordinates; }
    
    void display() const {
        cout << "\n┌─────────────────────────────────────────┐\n";
        cout << "│ Station ID    : " << left << setw(22) << stationId << "│\n";
        cout << "│ Name          : " << setw(22) << name << "│\n";
        cout << "│ City          : " << setw(22) << city << "│\n";
        cout << "│ Platforms     : " << setw(22) << platformCount << "│\n";
        cout << "│ Coordinates   : " << setw(22) 
             << ("(" + to_string(coordinates.first) + ", " + 
                 to_string(coordinates.second) + ")") << "│\n";
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

class Train {
private:
    string trainId;
    string trainName;
    string trainType; // Express, Passenger, Freight
    int totalSeats;
    int availableSeats;
    vector<string> route; // List of station IDs
    map<string, Time> schedule; // Station ID -> Arrival Time
    int priority; // Higher priority = more important
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
    vector<string> getRoute() const { return route; }
    map<string, Time> getSchedule() const { return schedule; }
    
    void addToRoute(string stationId, Time arrivalTime) {
        route.push_back(stationId);
        schedule[stationId] = arrivalTime;
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
        if (schedule.find(stationId) != schedule.end()) {
            return schedule.at(stationId).addMinutes(delayMinutes);
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
        for (const auto& station : route) {
            Time actualTime = schedule.at(station).addMinutes(delayMinutes);
            cout << "║  → " << left << setw(25) << station 
                 << setw(10) << actualTime.toString() << "   ║\n";
        }
        cout << "╚════════════════════════════════════════════╝\n";
    }
};

// ==================== GRAPH EDGE ====================

struct Edge {
    string destination;
    double distance; // in kilometers
    int travelTime; // in minutes
    double fare;
    
    Edge(string dest, double dist, int time, double f)
        : destination(dest), distance(dist), travelTime(time), fare(f) {}
};

// ==================== PRIORITY QUEUE NODE ====================

struct TrainPriority {
    shared_ptr<Train> train;
    Time scheduledTime;
    
    TrainPriority(shared_ptr<Train> t, Time time)
        : train(t), scheduledTime(time) {}
    
    bool operator<(const TrainPriority& other) const {
        // Higher priority trains come first
        // If same priority, earlier time comes first
        if (train->getPriority() != other.train->getPriority()) {
            return train->getPriority() < other.train->getPriority();
        }
        return scheduledTime > other.scheduledTime;
    }
};

// ==================== DIJKSTRA RESULT ====================

struct PathInfo {
    vector<string> path;
    double totalDistance;
    int totalTime;
    double totalFare;
    
    PathInfo() : totalDistance(0), totalTime(0), totalFare(0) {}
};

// ==================== HASH TABLE IMPLEMENTATION ====================

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
    
    vector<HashNode> table;
    int count;
    
    int hashFunction(const string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }
    
    int probe(int index, int i) const {
        return (index + i * i) % TABLE_SIZE; // Quadratic probing
    }
    
public:
    HashTable() : table(TABLE_SIZE), count(0) {}
    
    bool insert(const K& key, const V& value) {
        if (count >= TABLE_SIZE * 0.7) { // Load factor check
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
    
    bool remove(const K& key) {
        int index = hashFunction(key);
        int i = 0;
        
        while (i < TABLE_SIZE) {
            int probedIndex = probe(index, i);
            
            if (!table[probedIndex].isOccupied) {
                return false;
            }
            
            if (table[probedIndex].key == key && !table[probedIndex].isDeleted) {
                table[probedIndex].isDeleted = true;
                count--;
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
    vector<pair<K, V>> getAllEntries() const {
        vector<pair<K, V>> entries;
        for (const auto& node : table) {
            if (node.isOccupied && !node.isDeleted) {
                entries.push_back({node.key, node.value});
            }
        }
        return entries;
    }
    
    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

// ==================== PASSENGER QUEUE ====================

class PassengerQueue {
private:
    struct QueueNode {
        Passenger passenger;
        int priority;
        Time arrivalTime;
        
        QueueNode(Passenger p, int pr, Time t)
            : passenger(p), priority(pr), arrivalTime(t) {}
        
        bool operator<(const QueueNode& other) const {
            // Higher priority (elderly, disabled) comes first
            if (priority != other.priority) {
                return priority < other.priority;
            }
            return arrivalTime > other.arrivalTime;
        }
    };
    
    priority_queue<QueueNode> pq;
    
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
    
    void display() const {
        if (pq.empty()) {
            cout << "Queue is empty.\n";
            return;
        }
        
        auto temp = pq;
        cout << "\n╔════════════════════════════════════════════╗\n";
        cout << "║         PASSENGER WAITING QUEUE            ║\n";
        cout << "╠════════════════════════════════════════════╣\n";
        
        int position = 1;
        while (!temp.empty()) {
            auto node = temp.top();
            temp.pop();
            cout << "║ " << position++ << ". " << left << setw(35) 
                 << node.passenger.getName() 
                 << " P:" << node.priority << " ║\n";
        }
        
        cout << "╚════════════════════════════════════════════╝\n";
    }
};

// ==================== RAILWAY GRAPH SYSTEM ====================

class RailwayGraph {
private:
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Edge>> adjacencyList;
    HashTable<string, shared_ptr<Train>> trains;
    HashTable<string, Passenger> passengers;
    HashTable<string, Ticket> tickets;
    map<string, PassengerQueue> stationQueues;
    priority_queue<TrainPriority> trainSchedule;
    
    int ticketCounter;
    int passengerCounter;
    
public:
    RailwayGraph() : ticketCounter(1000), passengerCounter(1000) {
        initializeKarachiNetwork();
    }
    
    // ==================== INITIALIZATION ====================
    
    void initializeKarachiNetwork() {
        // Adding major railway stations in Karachi
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
        
        // Adding edges (routes) with distance (km), time (min), and fare (PKR)
        
        // Main Line Route
        addEdge("KCTY", "KC", 1.2, 5, 20);
        addEdge("KC", "DRH", 8.5, 15, 50);
        addEdge("DRH", "MLR", 6.8, 12, 40);
        addEdge("MLR", "LNDI", 5.2, 10, 35);
        addEdge("LNDI", "BQS", 8.3, 18, 60);
        
        // Circular Railway Route
        addEdge("KCTY", "SDHR", 2.5, 8, 25);
        addEdge("SDHR", "LYRI", 3.1, 10, 30);
        addEdge("LYRI", "SITE", 4.2, 12, 35);
        addEdge("SITE", "ORG", 5.5, 15, 40);
        addEdge("ORG", "SAL", 6.0, 18, 45);
        addEdge("SAL", "JCL", 4.3, 10, 35);
        addEdge("JCL", "KC", 3.8, 8, 30);
        
        // Cross connections
        addEdge("KC", "SDHR", 2.0, 6, 25);
        addEdge("DRH", "SHAH", 3.5, 8, 30);
        addEdge("SHAH", "KMR", 5.0, 12, 40);
        addEdge("KMR", "LNDI", 4.5, 10, 35);
        addEdge("MLR", "KMR", 3.8, 8, 30);
        addEdge("SITE", "GWDR", 2.5, 7, 25);
        addEdge("GWDR", "LYRI", 3.0, 8, 25);
        
        // Additional connections
        addEdge("KCTY", "JCL", 2.8, 7, 25);
        addEdge("SAL", "DRH", 7.5, 20, 55);
        
        // Initialize some trains
        initializeTrains();
    }
    
    void initializeTrains() {
        // Express Trains
        auto train1 = make_shared<Train>("TN001", "Karachi Express", "Express", 500, 10);
        train1->addToRoute("KCTY", Time(6, 0));
        train1->addToRoute("KC", Time(6, 10));
        train1->addToRoute("DRH", Time(6, 30));
        train1->addToRoute("MLR", Time(6, 50));
        train1->addToRoute("LNDI", Time(7, 5));
        train1->addToRoute("BQS", Time(7, 30));
        trains.insert("TN001", train1);
        
        auto train2 = make_shared<Train>("TN002", "Circular Express", "Express", 450, 9);
        train2->addToRoute("KCTY", Time(7, 0));
        train2->addToRoute("SDHR", Time(7, 10));
        train2->addToRoute("LYRI", Time(7, 25));
        train2->addToRoute("SITE", Time(7, 40));
        train2->addToRoute("ORG", Time(8, 0));
        train2->addToRoute("SAL", Time(8, 20));
        trains.insert("TN002", train2);
        
        // Passenger Trains
        auto train3 = make_shared<Train>("TN003", "Local Passenger", "Passenger", 600, 5);
        train3->addToRoute("KC", Time(8, 0));
        train3->addToRoute("DRH", Time(8, 20));
        train3->addToRoute("SHAH", Time(8, 35));
        train3->addToRoute("KMR", Time(8, 50));
        train3->addToRoute("LNDI", Time(9, 5));
        trains.insert("TN003", train3);
        
        auto train4 = make_shared<Train>("TN004", "Metro Line", "Metro", 400, 8);
        train4->addToRoute("KCTY", Time(9, 0));
        train4->addToRoute("JCL", Time(9, 10));
        train4->addToRoute("SAL", Time(9, 25));
        train4->addToRoute("DRH", Time(9, 50));
        train4->addToRoute("MLR", Time(10, 10));
        trains.insert("TN004", train4);
        
        auto train5 = make_shared<Train>("TN005", "Business Express", "Express", 300, 10);
        train5->addToRoute("KCTY", Time(10, 0));
        train5->addToRoute("KC", Time(10, 8));
        train5->addToRoute("SDHR", Time(10, 16));
        train5->addToRoute("DRH", Time(10, 35));
        trains.insert("TN005", train5);
    }
    
    // ==================== STATION MANAGEMENT ====================
    
    void addStation(const Station& station) {
        stations[station.getId()] = station;
        adjacencyList[station.getId()] = vector<Edge>();
    }
    
    bool removeStation(const string& stationId) {
        if (stations.find(stationId) == stations.end()) {
            return false;
        }
        
        stations.erase(stationId);
        adjacencyList.erase(stationId);
        
        // Remove all edges to this station
        for (auto& pair : adjacencyList) {
            auto& edges = pair.second;
            edges.erase(
                remove_if(edges.begin(), edges.end(),
                    [&stationId](const Edge& e) { return e.destination == stationId; }),
                edges.end()
            );
        }
        
        return true;
    }
    
    void displayStation(const string& stationId) {
        if (stations.find(stationId) != stations.end()) {
            stations[stationId].display();
        } else {
            cout << "Station not found!\n";
        }
    }
    
    void displayAllStations() {
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║              KARACHI RAILWAY STATIONS                    ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        cout << "║ ID    │ Name                    │ Platforms │ City      ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        
        for (const auto& pair : stations) {
            const Station& s = pair.second;
            cout << "║ " << left << setw(6) << s.getId() 
                 << "│ " << setw(24) << s.getName()
                 << "│ " << setw(10) << s.getPlatforms()
                 << "│ " << setw(10) << s.getCity() << "║\n";
        }
        
        cout << "╚══════════════════════════════════════════════════════════╝\n";
    }
    
    // ==================== EDGE/ROUTE MANAGEMENT ====================
    
    void addEdge(const string& from, const string& to, double distance, 
                 int time, double fare) {
        adjacencyList[from].push_back(Edge(to, distance, time, fare));
        adjacencyList[to].push_back(Edge(from, distance, time, fare)); // Bidirectional
    }
    
    void displayConnections(const string& stationId) {
        if (adjacencyList.find(stationId) == adjacencyList.end()) {
            cout << "Station not found!\n";
            return;
        }
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║  Connections from " << left << setw(34) << stationId << "║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        cout << "║ To      │ Distance(km) │ Time(min) │ Fare(PKR)      ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        for (const Edge& edge : adjacencyList[stationId]) {
            cout << "║ " << left << setw(8) << edge.destination
                 << "│ " << setw(13) << fixed << setprecision(1) << edge.distance
                 << "│ " << setw(10) << edge.travelTime
                 << "│ " << setw(15) << setprecision(2) << edge.fare << "║\n";
        }
        
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    // ==================== DIJKSTRA'S SHORTEST PATH ====================
    
    PathInfo dijkstraShortestPath(const string& source, const string& destination,
                                  bool byDistance = true) {
        PathInfo result;
        
        if (stations.find(source) == stations.end() || 
            stations.find(destination) == stations.end()) {
            cout << "Invalid source or destination!\n";
            return result;
        }
        
        unordered_map<string, double> dist;
        unordered_map<string, int> time;
        unordered_map<string, double> fare;
        unordered_map<string, string> parent;
        unordered_map<string, bool> visited;
        
        // Initialize
        for (const auto& pair : stations) {
            dist[pair.first] = numeric_limits<double>::max();
            time[pair.first] = INT_MAX;
            fare[pair.first] = numeric_limits<double>::max();
            visited[pair.first] = false;
        }
        
        dist[source] = 0;
        time[source] = 0;
        fare[source] = 0;
        
        // Priority queue: (distance/time, station)
        priority_queue<pair<double, string>, 
                      vector<pair<double, string>>,
                      greater<pair<double, string>>> pq;
        
        pq.push({0, source});
        
        while (!pq.empty()) {
            string u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            if (u == destination) break;
            
            for (const Edge& edge : adjacencyList[u]) {
                string v = edge.destination;
                double weight = byDistance ? edge.distance : edge.travelTime;
                
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    time[v] = time[u] + edge.travelTime;
                    fare[v] = fare[u] + edge.fare;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // Reconstruct path
        if (dist[destination] == numeric_limits<double>::max()) {
            cout << "No path found!\n";
            return result;
        }
        
        string current = destination;
        while (current != source) {
            result.path.push_back(current);
            current = parent[current];
        }
        result.path.push_back(source);
        reverse(result.path.begin(), result.path.end());
        
        result.totalDistance = dist[destination];
        result.totalTime = time[destination];
        result.totalFare = fare[destination];
        
        return result;
    }
    
    void displayShortestPath(const string& source, const string& destination) {
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║           SHORTEST PATH ANALYSIS                       ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        // By Distance
        PathInfo pathByDist = dijkstraShortestPath(source, destination, true);
        cout << "║ By Distance:                                           ║\n";
        cout << "║ Route: ";
        for (size_t i = 0; i < pathByDist.path.size(); i++) {
            cout << pathByDist.path[i];
            if (i < pathByDist.path.size() - 1) cout << " → ";
        }
        cout << "\n║ Total Distance: " << fixed << setprecision(2) 
             << pathByDist.totalDistance << " km\n";
        cout << "║ Total Time: " << pathByDist.totalTime << " minutes\n";
        cout << "║ Total Fare: PKR " << pathByDist.totalFare << "\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        // By Time
        PathInfo pathByTime = dijkstraShortestPath(source, destination, false);
        cout << "║ By Time:                                               ║\n";
        cout << "║ Route: ";
        for (size_t i = 0; i < pathByTime.path.size(); i++) {
            cout << pathByTime.path[i];
            if (i < pathByTime.path.size() - 1) cout << " → ";
        }
        cout << "\n║ Total Distance: " << fixed << setprecision(2) 
             << pathByTime.totalDistance << " km\n";
        cout << "║ Total Time: " << pathByTime.totalTime << " minutes\n";
        cout << "║ Total Fare: PKR " << pathByTime.totalFare << "\n";
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    // ==================== ALL POSSIBLE PATHS (DFS) ====================
    
    void findAllPathsDFS(const string& current, const string& destination,
                        unordered_set<string>& visited,
                        vector<string>& currentPath,
                        vector<PathInfo>& allPaths,
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
            for (const Edge& edge : adjacencyList[current]) {
                if (visited.find(edge.destination) == visited.end()) {
                    findAllPathsDFS(edge.destination, destination, visited, currentPath,
                                   allPaths, currentDist + edge.distance,
                                   currentTime + edge.travelTime,
                                   currentFare + edge.fare);
                }
            }
        }
        
        currentPath.pop_back();
        visited.erase(current);
    }
    
    vector<PathInfo> findAllPaths(const string& source, const string& destination,
                                   int maxPaths = 10) {
        vector<PathInfo> allPaths;
        unordered_set<string> visited;
        vector<string> currentPath;
        
        if (stations.find(source) == stations.end() || 
            stations.find(destination) == stations.end()) {
            cout << "Invalid source or destination!\n";
            return allPaths;
        }
        
        findAllPathsDFS(source, destination, visited, currentPath, allPaths, 0, 0, 0);
        
        // Sort by distance
        sort(allPaths.begin(), allPaths.end(),
            [](const PathInfo& a, const PathInfo& b) {
                return a.totalDistance < b.totalDistance;
            });
        
        // Return only top paths
        if (allPaths.size() > maxPaths) {
            allPaths.resize(maxPaths);
        }
        
        return allPaths;
    }
    
    void displayAllPaths(const string& source, const string& destination) {
        vector<PathInfo> paths = findAllPaths(source, destination);
        
        if (paths.empty()) {
            cout << "No paths found!\n";
            return;
        }
        
        cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        cout << "║         ALL POSSIBLE ROUTES FROM " << source << " TO " << destination << "          ║\n";
        cout << "╠═══════════════════════════════════════════════════════════╣\n";
        
        for (size_t i = 0; i < paths.size(); i++) {
            cout << "║ Route " << (i + 1) << ":                                                ║\n";
            cout << "║ Path: ";
            for (size_t j = 0; j < paths[i].path.size(); j++) {
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
    
    // ==================== TRAIN MANAGEMENT ====================
    
    void addTrain(shared_ptr<Train> train) {
        trains.insert(train->getId(), train);
    }
    
    void displayTrain(const string& trainId) {
        shared_ptr<Train> train;
        if (trains.find(trainId, train)) {
            train->display();
        } else {
            cout << "Train not found!\n";
        }
    }
    
    void displayAllTrains() {
        auto allTrains = trains.getAllEntries();
        
        if (allTrains.empty()) {
            cout << "No trains in the system.\n";
            return;
        }
        
        cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
        cout << "║                    ALL TRAINS IN SYSTEM                       ║\n";
        cout << "╠═══════════════════════════════════════════════════════════════╣\n";
        
        for (const auto& pair : allTrains) {
            pair.second->display();
        }
    }
    
    void setTrainDelay(const string& trainId, int delayMinutes) {
        shared_ptr<Train> train;
        if (trains.find(trainId, train)) {
            train->setDelay(delayMinutes);
            cout << "Delay of " << delayMinutes << " minutes set for train " 
                 << trainId << "\n";
        } else {
            cout << "Train not found!\n";
        }
    }
    
    // ==================== PASSENGER MANAGEMENT ====================
    
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
    
    void addPassengerToQueue(const string& stationId, const string& passengerId,
                            int priority = 5) {
        Passenger p;
        if (!passengers.find(passengerId, p)) {
            cout << "Passenger not found!\n";
            return;
        }
        
        if (stations.find(stationId) == stations.end()) {
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
        if (stationQueues.find(stationId) == stationQueues.end() ||
            stationQueues[stationId].isEmpty()) {
            cout << "No passengers in queue at " << stationId << "\n";
            return;
        }
        
        Passenger p = stationQueues[stationId].dequeue();
        cout << "Processing passenger: " << p.getName() << "\n";
    }
    
    void displayStationQueue(const string& stationId) {
        if (stationQueues.find(stationId) == stationQueues.end()) {
            cout << "No queue at station " << stationId << "\n";
            return;
        }
        
        cout << "\nQueue at Station: " << stationId << "\n";
        stationQueues[stationId].display();
    }
    
    // ==================== TICKET BOOKING ====================
    
    string bookTicket(const string& passengerId, const string& trainId,
                     const string& from, const string& to) {
        // Validate passenger
        Passenger p;
        if (!passengers.find(passengerId, p)) {
            cout << "Passenger not found!\n";
            return "";
        }
        
        // Validate train
        shared_ptr<Train> train;
        if (!trains.find(trainId, train)) {
            cout << "Train not found!\n";
            return "";
        }
        
        // Check if train covers this route
        vector<string> route = train->getRoute();
        auto fromIt = find(route.begin(), route.end(), from);
        auto toIt = find(route.begin(), route.end(), to);
        
        if (fromIt == route.end() || toIt == route.end() || fromIt >= toIt) {
            cout << "Train does not cover this route!\n";
            return "";
        }
        
        // Check seat availability
        if (!train->bookSeat()) {
            cout << "No seats available!\n";
            return "";
        }
        
        // Calculate fare based on shortest path
        PathInfo path = dijkstraShortestPath(from, to, true);
        
        // Create ticket
        string ticketId = "T" + to_string(ticketCounter++);
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Date currentDate(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
        
        Time departureTime = train->getArrivalTime(from);
        string seatNumber = "S-" + to_string(train->getAvailableSeats() + 1);
        
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
            
            // Release seat
            shared_ptr<Train> train;
            if (trains.find(t.getTrainId(), train)) {
                train->releaseSeat();
            }
            
            t.cancelTicket();
            tickets.insert(ticketId, t); // Update
            cout << "Ticket " << ticketId << " cancelled successfully!\n";
        } else {
            cout << "Ticket not found!\n";
        }
    }
    
    // ==================== SORTING & ANALYSIS ====================
    
    void displayTrainsByPriority() {
        auto allTrains = trains.getAllEntries();
        
        // Sort by priority (descending)
        sort(allTrains.begin(), allTrains.end(),
            [](const pair<string, shared_ptr<Train>>& a,
               const pair<string, shared_ptr<Train>>& b) {
                return a.second->getPriority() > b.second->getPriority();
            });
        
        cout << "\n╔═══════════════════════════════════════════════════════╗\n";
        cout << "║         TRAINS SORTED BY PRIORITY                     ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        cout << "║ ID    │ Name              │ Priority │ Delay(min)   ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        
        for (const auto& pair : allTrains) {
            auto train = pair.second;
            cout << "║ " << left << setw(6) << train->getId()
                 << "│ " << setw(18) << train->getName()
                 << "│ " << setw(9) << train->getPriority()
                 << "│ " << setw(13) << train->getDelay() << "║\n";
        }
        
        cout << "╚═══════════════════════════════════════════════════════╝\n";
    }
    
    void displayTrainSchedule(const string& stationId) {
        auto allTrains = trains.getAllEntries();
        vector<pair<Time, shared_ptr<Train>>> schedule;
        
        for (const auto& pair : allTrains) {
            auto train = pair.second;
            auto trainSchedule = train->getSchedule();
            
            if (trainSchedule.find(stationId) != trainSchedule.end()) {
                Time arrivalTime = train->getArrivalTime(stationId);
                schedule.push_back({arrivalTime, train});
            }
        }
        
        // Sort by time
        sort(schedule.begin(), schedule.end(),
            [](const pair<Time, shared_ptr<Train>>& a,
               const pair<Time, shared_ptr<Train>>& b) {
                return a.first < b.first;
            });
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║       TRAIN SCHEDULE AT " << left << setw(28) << stationId << "║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        cout << "║ Time  │ Train ID │ Train Name          │ Delay       ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        for (const auto& entry : schedule) {
            Time t = entry.first;
            auto train = entry.second;
            cout << "║ " << setw(6) << t.toString()
                 << "│ " << setw(9) << train->getId()
                 << "│ " << setw(20) << train->getName()
                 << "│ " << setw(8) << train->getDelay() << " min║\n";
        }
        
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    // ==================== STATISTICS ====================
    
    void displaySystemStatistics() {
        auto allTrains = trains.getAllEntries();
        auto allTickets = tickets.getAllEntries();
        auto allPassengers = passengers.getAllEntries();
        
        int totalSeats = 0;
        int bookedSeats = 0;
        double totalRevenue = 0;
        int activeTickets = 0;
        
        for (const auto& pair : allTrains) {
            auto train = pair.second;
            totalSeats += 500; // Assuming default
            bookedSeats += (500 - train->getAvailableSeats());
        }
        
        for (const auto& pair : allTickets) {
            if (pair.second.getBookingStatus()) {
                totalRevenue += pair.second.getFare();
                activeTickets++;
            }
        }
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║           RAILWAY SYSTEM STATISTICS                    ║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        cout << "║ Total Stations        : " << left << setw(28) 
             << stations.size() << "║\n";
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
    
    // ==================== SEARCH FUNCTIONS ====================
    
    void searchTrainsByRoute(const string& stationId) {
        auto allTrains = trains.getAllEntries();
        vector<shared_ptr<Train>> matchingTrains;
        
        for (const auto& pair : allTrains) {
            auto route = pair.second->getRoute();
            if (find(route.begin(), route.end(), stationId) != route.end()) {
                matchingTrains.push_back(pair.second);
            }
        }
        
        if (matchingTrains.empty()) {
            cout << "No trains pass through " << stationId << "\n";
            return;
        }
        
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║    TRAINS PASSING THROUGH " << left << setw(27) << stationId << "║\n";
        cout << "╠════════════════════════════════════════════════════════╣\n";
        
        for (auto train : matchingTrains) {
            cout << "║ " << setw(8) << train->getId() 
                 << " │ " << setw(43) << train->getName() << "║\n";
        }
        
        cout << "╚════════════════════════════════════════════════════════╝\n";
    }
    
    vector<string> getStationIds() const {
        vector<string> ids;
        for (const auto& pair : stations) {
            ids.push_back(pair.first);
        }
        return ids;
    }
    
    vector<string> getTrainIds() const {
        vector<string> ids;
        auto allTrains = trains.getAllEntries();
        for (const auto& pair : allTrains) {
            ids.push_back(pair.first);
        }
        return ids;
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
                    if (!ticketId.empty()) {
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
// ==================== MAIN FUNCTION ====================
int main() {
    // ==================== AUTO UTF-8 SETUP ====================
    #ifdef _WIN32
        // Save original console code page
        UINT originalCP = GetConsoleOutputCP();
        
        // Set to UTF-8
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);

        
    #endif
    
    // Display startup banner
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
    
    // Create railway graph and menu system
    RailwayGraph railway;
    MenuSystem menu(railway);
    
    menu.run();
    
    // ==================== CLEANUP & RESTORE ====================
    #ifdef _WIN32
        // Restore original code page
        SetConsoleOutputCP(originalCP);
        SetConsoleCP(originalCP);
    #endif
    
    return 0;
}