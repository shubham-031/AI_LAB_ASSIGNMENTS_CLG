#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// Goal state
const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// State structure
struct State {
    vector<vector<int>> board;
    int x, y; // blank tile position
    string path;

    State(vector<vector<int>> b, int i, int j, string p = "") : board(b), x(i), y(j), path(p) {}
};

// Check if current state is goal
bool isGoal(const vector<vector<int>>& b) {
    return b == goal;
}

// Convert board to string for hashing
string toStr(const vector<vector<int>>& b) {
    string s;
    for (auto& row : b)
        for (int val : row)
            s += to_string(val);
    return s;
}

// Generate all next states from current
vector<State> getNextStates(State s) {
    vector<State> res;
    vector<pair<int, int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};
    string move = "UDLR";

    for (int i = 0; i < 4; i++) {
        int nx = s.x + dirs[i].first;
        int ny = s.y + dirs[i].second;
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> nb = s.board;
            swap(nb[s.x][s.y], nb[nx][ny]);
            res.push_back(State(nb, nx, ny, s.path + move[i]));
        }
    }
    return res;
}

// BFS Solver
void solveBFS(State start) {
    queue<State> q;
    set<string> visited;

    q.push(start);
    visited.insert(toStr(start.board));

    while (!q.empty()) {
        State curr = q.front(); q.pop();

        if (isGoal(curr.board)) {
            cout << "\n✅ BFS: Goal Reached!" << endl;
            cout << "Moves to reach goal: " << curr.path << endl;
            return;
        }

        for (auto next : getNextStates(curr)) {
            string key = toStr(next.board);
            if (!visited.count(key)) {
                visited.insert(key);
                q.push(next);
            }
        }
    }
    cout << "\n❌ BFS: Goal not reachable." << endl;
}

// DFS Solver with depth limit
bool solveDFSUtil(State curr, set<string>& visited, int depth, int maxDepth, string& resultPath) {
    if (isGoal(curr.board)) {
        resultPath = curr.path;
        return true;
    }
    if (depth >= maxDepth) return false;
    visited.insert(toStr(curr.board));
    for (auto next : getNextStates(curr)) {
        string key = toStr(next.board);
        if (!visited.count(key)) {
            if (solveDFSUtil(next, visited, depth + 1, maxDepth, resultPath))
                return true;
        }
    }
    visited.erase(toStr(curr.board));
    return false;
}

void solveDFS(State start, int maxDepth = 30) {
    set<string> visited;
    string resultPath;
    if (solveDFSUtil(start, visited, 0, maxDepth, resultPath)) {
        cout << "\n✅ DFS: Goal Reached!" << endl;
        cout << "Moves to reach goal: " << resultPath << endl;
    } else {
        cout << "\n❌ DFS: Goal not reachable within depth limit (" << maxDepth << ")." << endl;
    }
}

// Find blank position (0)
pair<int, int> findBlank(vector<vector<int>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

// Menu-driven main function
int main() {
    vector<vector<int>> board = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    int choice;
    do {
        cout << "\n==== 8-Puzzle Solver Menu ====" << endl;
        cout << "1. Enter Initial Board" << endl;
        cout << "2. Solve using BFS" << endl;
        cout << "3. Solve using DFS" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                cout << "Enter the board (3x3) row-wise (use 0 for blank):" << endl;
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        cin >> board[i][j];
                break;
            }
            case 2: {
                pair<int, int> blankPos = findBlank(board);
                State start(board, blankPos.first, blankPos.second);
                solveBFS(start);
                break;
            }
            case 3: {
                pair<int, int> blankPos = findBlank(board);
                State start(board, blankPos.first, blankPos.second);
                int maxDepth;
                cout << "Enter DFS max depth (suggest 20-40): ";
                cin >> maxDepth;
                solveDFS(start, maxDepth);
                break;
            }
            case 4:
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
