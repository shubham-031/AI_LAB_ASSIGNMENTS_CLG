#include <bits/stdc++.h>
using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = '_';

// Function to print board
void printBoard(vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }                              
    cout << "\n";
}

// Check if any moves left
bool isMovesLeft(vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

// Evaluate board
int evaluate(vector<vector<char>>& b) {
    // Rows
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == AI) return +10;
            else if (b[row][0] == HUMAN) return -10;
        }
    }
    // Columns
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == AI) return +10;
            else if (b[0][col] == HUMAN) return -10;
        }
    }
    // Diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == AI) return +10;
        else if (b[0][0] == HUMAN) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == AI) return +10;
        else if (b[0][2] == HUMAN) return -10;
    }
    return 0;
}

// Minimax Algorithm
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score - depth;   // prefer quick win
    if (score == -10) return score + depth;  // prefer delayed loss
    if (!isMovesLeft(board)) return 0;

    if (isMax) { // Maximizer (AI)
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else { // Minimizer (Human)
        int best = 1000;   
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find best move for AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    int choice;

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Play Tic Tac Toe (Human vs AI)\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            board.assign(3, vector<char>(3, EMPTY));
            cout << "\nGame Start!\nYou are X, Computer is O\n";
            printBoard(board);

            while (true) {
                int x, y;
                cout << "Enter your move (row and column: 0 1 2): ";
                cin >> x >> y;
                if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != EMPTY) {
                    cout << "Invalid Move! Try again.\n";
                    continue;
                }
                board[x][y] = HUMAN;
                printBoard(board);

                if (evaluate(board) == -10) {
                    cout << "You Win!\n";
                    break;
                }
                if (!isMovesLeft(board)) {
                    cout << "Game Draw!\n";
                    break;
                }

                pair<int, int> aiMove = findBestMove(board);
                board[aiMove.first][aiMove.second] = AI;
                cout << "Computer placed O at (" << aiMove.first << "," << aiMove.second << ")\n";
                printBoard(board);

                if (evaluate(board) == 10) {
                    cout << "Computer Wins!\n";
                    break;
                }
                if (!isMovesLeft(board)) {
                    cout << "Game Draw!\n";
                    break;
                }
            }
        } else if (choice == 2) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
    