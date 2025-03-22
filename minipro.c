#include <stdio.h>

#define N 9  // Size of the Sudoku grid (9x9)

// Function to display the Sudoku grid
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if it's safe to place a number at board[row][col]
int isSafe(int board[N][N], int row, int col, int num) {
    // Check if the number is already in the current row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) {
            return 0;  // Return 0 (false) if the number is already in the row
        }
    }

    // Check if the number is already in the current column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num) {
            return 0;  // Return 0 (false) if the number is already in the column
        }
    }

    // Check if the number is already in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return 0;  // Return 0 (false) if the number is already in the subgrid
            }
        }
    }

    return 1;  // Return 1 (true) if it's safe to place the number
}

// Backtracking function to solve the Sudoku puzzle
int solveSudoku(int board[N][N]) {
    int row, col;
    int emptyCellFound = 0;

    // Find an empty cell in the grid (marked with 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                emptyCellFound = 1;
                break;
            }
        }
        if (emptyCellFound) {
            break;
        }
    }

    // If there is no empty cell, the puzzle is solved
    if (!emptyCellFound) {
        return 1;
    }

    // Try digits 1 to 9 for the empty cell
    for (int num = 1; num <= N; num++) {
        if (isSafe(board, row, col, num)) {
            // Place the number and recursively attempt to solve
            board[row][col] = num;

            if (solveSudoku(board)) {
                return 1;  // Puzzle solved
            }

            // Backtrack if placing num doesn't lead to a solution
            board[row][col] = 0;
        }
    }

    return 0;  // Trigger backtracking if no solution is found
}

int main() {
    int board[N][N];

    printf("Enter the Sudoku puzzle (9x9 grid, use 0 for empty cells):\n");
    
    // Input the Sudoku puzzle from the user
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    printf("\nInput Sudoku Puzzle:\n");
    printBoard(board);

    // Solve the Sudoku puzzle
    if (solveSudoku(board)) {
        printf("\nSolved Sudoku Puzzle:\n");
        printBoard(board);
    } else {
        printf("\nNo solution exists for this Sudoku puzzle.\n");
    }

    return 0;
}
