#include <iostream>

const int INF = 999999;
const int V = 6; 

int minDistance(int dist[], bool sptSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) return;
    printPath(parent, parent[j]);
    char nodeName = 'A' + j;
    std::cout << " -> " << nodeName;
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V]; 
    bool sptSet[V]; 
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    std::cout << "Shortest Path from " << (char)('A' + src) << " to " << (char)('A' + dest) << ": ";
    std::cout << (char)('A' + src);
    printPath(parent, dest);
    std::cout << "\nTotal Cost: " << dist[dest] << std::endl;
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 8, 0, 0}, // A
        {4, 0, 9, 0, 0, 0}, // B
        {0, 9, 0, 6, 14, 0},// C
        {8, 0, 6, 0, 0, 4}, // D
        {0, 0, 14, 0, 0, 3},// E
        {0, 0, 0, 4, 3, 0}  // F
    };

    dijkstra(graph, 1, 4);
    dijkstra(graph, 0, 5);
    dijkstra(graph, 2, 3);

    return 0;
}