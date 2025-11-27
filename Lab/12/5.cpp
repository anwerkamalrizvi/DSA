#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;
    int front, rear, capacity, size;
    
public:
    Queue(int cap) {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }
    
    ~Queue() {
        delete[] arr;
    }
    
    void enqueue(int val) {
        if(size == capacity) return;
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        size++;
    }
    
    int dequeue() {
        if(size == 0) return -1;
        int val = arr[front];
        front = (front + 1) % capacity;
        size--;
        return val;
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

class Stack {
private:
    int* arr;
    int top, capacity;
    
public:
    Stack(int cap) {
        capacity = cap;
        arr = new int[capacity];
        top = -1;
    }
    
    ~Stack() {
        delete[] arr;
    }
    
    void push(int val) {
        if(top == capacity - 1) return;
        arr[++top] = val;
    }
    
    int pop() {
        if(top == -1) return -1;
        return arr[top--];
    }
    
    bool isEmpty() {
        return top == -1;
    }
};

class Graph {
private:
    int vertices;
    int** adjMatrix;
    
    struct Node {
        int vertex;
        Node* next;
    };
    
    Node** adjList;
    
public:
    Graph(int v) {
        vertices = v;
        
        adjMatrix = new int*[vertices];
        for(int i = 0; i < vertices; i++) {
            adjMatrix[i] = new int[vertices];
            for(int j = 0; j < vertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
        
        adjList = new Node*[vertices];
        for(int i = 0; i < vertices; i++) {
            adjList[i] = nullptr;
        }
    }
    
    ~Graph() {
        for(int i = 0; i < vertices; i++) {
            delete[] adjMatrix[i];
            Node* current = adjList[i];
            while(current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjMatrix;
        delete[] adjList;
    }
    
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
        
        Node* newNode = new Node;
        newNode->vertex = v;
        newNode->next = adjList[u];
        adjList[u] = newNode;
        
        newNode = new Node;
        newNode->vertex = u;
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }
    
    void displayAdjacencyMatrix() {
        cout << "\nAdjacency Matrix:" << endl;
        cout << "   ";
        for(int i = 0; i < vertices; i++) {
            cout << i << " ";
        }
        cout << endl;
        
        for(int i = 0; i < vertices; i++) {
            cout << i << "  ";
            for(int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    void displayAdjacencyList() {
        cout << "\nAdjacency List:" << endl;
        for(int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            Node* temp = adjList[i];
            while(temp != nullptr) {
                cout << temp->vertex;
                if(temp->next != nullptr) cout << " -> ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    
    void BFS(int start) {
        bool* visited = new bool[vertices];
        for(int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        Queue q(vertices);
        visited[start] = true;
        q.enqueue(start);
        
        cout << "\nBFS Traversal starting from vertex " << start << ": ";
        
        while(!q.isEmpty()) {
            int current = q.dequeue();
            cout << current << " ";
            
            Node* temp = adjList[current];
            while(temp != nullptr) {
                if(!visited[temp->vertex]) {
                    visited[temp->vertex] = true;
                    q.enqueue(temp->vertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
        
        delete[] visited;
    }
    
    void DFSUtil(int vertex, bool* visited) {
        visited[vertex] = true;
        cout << vertex << " ";
        
        Node* temp = adjList[vertex];
        while(temp != nullptr) {
            if(!visited[temp->vertex]) {
                DFSUtil(temp->vertex, visited);
            }
            temp = temp->next;
        }
    }
    
    void DFS(int start) {
        bool* visited = new bool[vertices];
        for(int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        cout << "\nDFS Traversal starting from vertex " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
        
        delete[] visited;
    }
};

int main() {
    Graph g(5);
    
    g.addEdge(0, 3); 
    g.addEdge(3, 1); 
    g.addEdge(1, 4); 
    g.addEdge(3, 4); 
    g.addEdge(2, 4); 
    g.displayAdjacencyList();
    g.displayAdjacencyMatrix();

    // Traversal starting from Node 1 (index 0)
    g.BFS(0);
    g.DFS(0);
    return 0;
}