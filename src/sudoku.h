#include <iostream>
#include <cstring>

class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator==(const int (*otherGrid)[9]) {
        for (int i = 0; i < 9 * 9; i++) {
            if (grid[i % 9][i / 9] != otherGrid[i % 9][i / 9]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const Sudoku &other) {
        for (int i = 0; i < 9 * 9; i++) {
#ifdef PRINT
            printf("comparing grid(%d, %d)\n", i%9, i/9);
#endif
            if (grid[i % 9][i / 9] != other.grid[i % 9][i / 9]) {
                return false;
            }
        }
        return true;
    }

    int get(int i, int j) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j];
        }

        return -1;
    }

    int set(int i, int j, int val) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j] = val;
        }
        return -1;
    }

    void print() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf(" [%d] ", get(i, j));
                if (j == 8) {
                    printf("\n");
                }
            }
        }
    }

    bool containedIn3x3Box(int row, int col, int value) {
        // Find the top left of its 3x3 box to start validating from
        int startRow = row / 3 * 3;
        int startCol = col / 3 * 3;

        // Check within its 3x3 box except its cell
        for (int i = startRow; i < startRow + 3; i++)
            for (int j = startCol; j < startCol + 3; j++) {
                if (!(i == row && j == col)) {
                    if (grid[i][j] == value) {
                        return true;
                    }
                }
            }

        return false;
    }

    bool containedInRowCol(int row, int col, int value) {
        for (int i = 0; i < 9; i++) {
            if (i != col)
                if (grid[row][i] == value)
                    return true;
            if (i != row)
                if (grid[i][col] == value)
                    return true;
        }

        return false;
    }

    bool _solve(int row, int col) {
        if (row == 9)
            return true;

        if (grid[row][col] != 0) {
            if (_solve(col == 8 ? (row + 1) : row, (col + 1) % 9))
                return true;
        } else {
            for (int i = 1; i <= 9; i++) {
                if (!containedInRowCol(row, col, i) && !containedIn3x3Box(row, col, i)) {
                    grid[row][col] = i;
                    if (_solve(col == 8 ? (row + 1) : row, (col + 1) % 9))
                        return true;
                    else {
                        grid[row][col] = 0;
                    }
                }
            }
        }

        return false;
    }

    bool solve() {
        return _solve(0, 0);
        return false;   // placeholder
    }
};
