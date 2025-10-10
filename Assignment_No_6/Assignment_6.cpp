#include <bits/stdc++.h>
using namespace std;

#define N 8   // Chessboard size for 8-Queens

// Function to print the board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1)         
                cout << " Q ";               
            else
                cout << " . ";
        }
        cout << endl;
    }
}

// Check if a queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    // Check this row on left side
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Solve N Queen problem using Backtracking
bool solveNQUtil(int board[N][N], int col) {
    if (col >= N)  // Base case: All queens placed
        return true;

    // Try placing this queen in all rows one by one
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1; // Place queen

            if (solveNQUtil(board, col + 1)) // Recur for next column
                return true;

            board[i][col] = 0; // BACKTRACK
        }
    }
    return false;
}

// Wrapper function
void solveNQ() {
    int board[N][N] = {0};

    if (!solveNQUtil(board, 0)) {
        cout << "Solution does not exist" << endl;
        return;
    }

    printBoard(board);
}

// Menu driven program
int main() {
    int choice;
    do {
        cout << "\n===== 8-Queens Problem (Backtracking) =====" << endl;
        cout << "1. Solve 8-Queens" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                solveNQ();
                break;
            case 2:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 2);

    return 0;
}
