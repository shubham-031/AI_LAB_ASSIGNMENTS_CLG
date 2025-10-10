#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX = 100;
vector<int> color(MAX);
vector<vector<int>> graph(MAX);
int numRegions, numEdges, numColors;
vector<string> colorNames = {"Red", "Green", "Blue", "Yellow", "Orange"}; 
     
bool isSafe(int node, int c) {
    for (int neighbor : graph[node]) {
        if (color[neighbor] == c)               
            return false;                
    }
    return true;
}

bool solveCSP(int node) {
    if (node == numRegions) return true;

    for (int c = 1; c <= numColors; c++) {
        if (isSafe(node, c)) {
            color[node] = c;
            if (solveCSP(node + 1)) return true;
            color[node] = 0; // Backtrack
        }
    }
    return false;
}

void inputGraph() {
    cout << "Enter number of regions: ";
    cin >> numRegions;
    cout << "Enter number of edges (adjacent regions): ";
    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cout << "Enter edge " << i + 1 << " (format: u v): ";
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Enter number of colors (max 5 supported): ";
    cin >> numColors;
}

void printColorAssignment() {
    cout << "\nRegion to Color Assignment:\n";
    for (int i = 0; i < numRegions; i++) {
        if (color[i] > 0)
            cout << "Region " << i << " => " << colorNames[color[i] - 1] << "\n";
        else
            cout << "Region " << i << " => Not Assigned\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Constraint Satisfaction Problem ---\n";
        cout << "1. Input Graph (Regions & Adjacency)\n";
        cout << "2. Solve using Backtracking\n";
        cout << "3. Show Color Assignment\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                if (solveCSP(0))
                    cout << "CSP Solved Successfully!\n";
                else
                    cout << "No solution exists.\n";
                break;
            case 3:
                printColorAssignment();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);

    return 0;
}
