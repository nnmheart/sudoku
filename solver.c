#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sudoku.h>

void print_sud(sudoku_t* sudoku) {
    for (int y = 0; y < 9; y++) {
        if (y == 0) {
            printf("|-------|-------|-------|\n");
        }
        for (int x = 0; x < 9; x++) {
            if (x == 0) {
                printf("| ");
            }
            cell_t cell = sudoku->grid[y][x];
            if (cell.number == 0) {
                printf("  ");
            } else {
                printf("%i ", cell.number);
            }
            if ((x+1) % 3 == 0) {
                printf("| ");
            }
        }
        printf("\n");
        if ((y+1) % 3 == 0) {
            printf("|-------|-------|-------|\n");
        }
    }
}

int main(int argc, char** argv) {
    sudoku_t* sud = sudoku_create();

    if (argc != 2) {
        printf("This program only accepts a text file that lists out digits.\n");
        exit(EXIT_FAILURE);
    }

    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int digit_count = 0;
    int x = 0;
    int y = 0;

    while (digit_count < 81) {
        int c = fgetc(fptr);
        if (c == -1) {
            printf("Not enough data.\n");
            exit(EXIT_FAILURE);
        }
        char cha = (char)c;
        if (('0' <= cha) && (cha <= '9')) {
            int digit = (int)(cha - '0');
            sud->grid[y][x].number = digit;
            x += 1;
            if (x == 9) {
                x = 0;
                y += 1;
            }
            digit_count++;
        }
    }

    printf("Input board:\n");
    print_sud(sud);
    printf("--------------------------\n");
    if (!sud_solve(sud)) {
        printf("Unable to find solution for board.\n");
        exit(EXIT_FAILURE);
    }
    printf("Solved board:\n");
    print_sud(sud);
}