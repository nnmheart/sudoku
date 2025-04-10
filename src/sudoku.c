#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<malloc.h>

#include<sudoku.h>

sudoku_t* sudoku_create() {
    sudoku_t* sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
    
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            cell_t cell = sudoku->grid[y][x];
            cell.number = 0;
            sudoku->grid[y][x] = cell;
        }
    }
    
    return sudoku;
}

void sudoku_destroy(sudoku_t* sud) {
    free(sud);
}

bool sud_solve_round(sudoku_t* sud) {
    bool found_anything = false;


    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            bool possibilities[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
            
            cell_t cell = sud->grid[y][x];
            if (cell.number != 0) continue;

            // Row check
            for (int rx = 0; rx < 9; rx++) {
                cell_t cell2 = sud->grid[y][rx];
                if (cell2.number == 0) continue;
                possibilities[cell2.number - 1] = false;
            }

            // Column check
            for (int ry = 0; ry < 9; ry++) {
                cell_t cell2 = sud->grid[ry][x];
                if (cell2.number == 0) continue;
                possibilities[cell2.number - 1] = false;
            }

            // Block check
            int bx = x - x % 3;
            int by = y - y % 3;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cell_t cell2 = sud->grid[by + j][bx + i];
                    if (cell2.number == 0) continue;
                    possibilities[cell2.number - 1] = false;
                }
            }

            // Looking through possibilities
            int marked = 0;
            int number = 0;
            for (int i = 0; i < 9; i++) {
                if (possibilities[i] == false) {
                    marked += 1;
                } else {
                    number = i + 1;
                }
            }

            if (marked == 8) {
                //printf("%i @ (%i, %i)\n", number, x, y);
                found_anything = true;
                sud->grid[y][x].number = number;
            }
        }
    }
    return found_anything;
}

bool sud_is_full(sudoku_t* sud) {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (sud->grid[y][x].number == 0) {
                return false;
            }
        }
    }
    return true;
}

bool sud_solve(sudoku_t* sud) {
    while (!sud_is_full(sud)) {
        bool found_anything = sud_solve_round(sud);
        if (!found_anything && !sud_is_full(sud)) {
            return false;
        }
    }
    return true;
}
