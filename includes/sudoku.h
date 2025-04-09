#ifndef _SUDOKU_H
#define _SUDOKU_H

#include<stdbool.h>

typedef struct cell_t {
    int number;
} cell_t;

typedef struct sudoku_t {
    cell_t grid[9][9];
} sudoku_t;

sudoku_t* sudoku_create();
bool sud_solve(sudoku_t* sud);

#endif // _SUDOKU_H