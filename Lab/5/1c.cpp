#include <iostream>
using namespace std;

const int N = 4;
int maze[N][N] = {
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 1}
};
bool visit[N][N] = {false};
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visit[x][y]);
}

bool solveMaze(int x, int y, int targetX, int targetY) {
    if (x == targetX && y == targetY) {
        cout << "(" << x << ", " << y << ") ";
        return true;
    }
    visit[x][y] = true;
    cout << "(" << x << ", " << y << ") -> ";

    // Try all 4 directions
    for (int dir = 0; dir < 4; dir++) {
        int newX = x + dx[dir];
        int newY = y + dy[dir];

        if (isValid(newX, newY)) {
            if (solveMaze(newX, newY, targetX, targetY))
                return true;
        }
    }

    // Backtrack
    visit[x][y] = false;
    return false;
}

int main() {
    int startX = 0, startY = 0;
    int targetX = 2, targetY = 0;

    cout << "Path from (" << startX << "," << startY << ") to (" << targetX << "," << targetY << "):\n";

    if (!solveMaze(startX, startY, targetX, targetY))
        cout << "No path found!\n";

    return 0;
}
