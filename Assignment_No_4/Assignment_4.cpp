#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;         // Coordinates
    int g, h, f;      // g = cost so far, h = heuristic, f = total
    Node* parent;     // To trace path
};

// Compare function for priority queue              
struct Compare {   
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// Check valid cell
bool isValid(int x, int y, int n, int m, vector<vector<int>>& grid) {
    return (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0);
}

// Manhattan distance heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* Algorithm
void AStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int n = grid.size(), m = grid[0].size();
    priority_queue<Node*, vector<Node*>, Compare> openList;
    vector<vector<bool>> closed(n, vector<bool>(m, false));

    Node* startNode = new Node{start.first, start.second, 0,
                               heuristic(start.first, start.second, goal.first, goal.second), 0, nullptr};
    startNode->f = startNode->g + startNode->h;
    openList.push(startNode);

    vector<pair<int,int>> directions = {{1,0},{-1,0},{0,1},{0,-1}}; // 4 directions

    while(!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        int x = current->x, y = current->y;
        if (x == goal.first && y == goal.second) {
            cout << "Path Found!\n";
            vector<pair<int,int>> path;
            while(current != nullptr) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            cout << "Shortest Path: ";                               
            for(auto p : path) cout << "(" << p.first << "," << p.second << ") ";
            cout << "\n";
            return;
        }
   
        closed[x][y] = true;

        for(auto d : directions) {
            int nx = x + d.first, ny = y + d.second;
            if(isValid(nx, ny, n, m, grid) && !closed[nx][ny]) {
                Node* neighbor = new Node{nx, ny, current->g + 1,
                                          heuristic(nx, ny, goal.first, goal.second), 0, current};
                neighbor->f = neighbor->g + neighbor->h;
                openList.push(neighbor);
            }
        }
    }
    cout << "No Path Found!\n";
}

// Menu
int main() {
    int n, m, choice;
    cout << "Enter grid size (rows cols): ";
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));

    cout << "Enter grid (0 = free, 1 = blocked):\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> grid[i][j];

    pair<int,int> start, goal;
    cout << "Enter Start (row col): ";
    cin >> start.first >> start.second;
    cout << "Enter Goal (row col): ";
    cin >> goal.first >> goal.second;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Run A* Algorithm\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                AStar(grid, start, goal);
                break;
            case 2:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 2);

    return 0;
}
