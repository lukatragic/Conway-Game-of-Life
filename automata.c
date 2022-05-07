#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Luka Taglic | lt2205
// automata.c file for Assignment-2

// set row and column length
int row = 5;
int col = 5;

// calculate the amount of live cells next to horizontally, vertically, and diagonally from the current cell
// the neighbors of border cells are assumed to be dead and will never be alive
int numOfLiveNeighbors(int board[row][col], int r, int c){
    int i, j, count = 0;
    for (i = r-1; i <= r+1; i++){
        for (j = c-1; j <= c+1; j++){
            if ((i == r && j ==c) || (i<0 || j<0) || (i>= row || j>= col)){
                continue;
            }
            if(board[i][j]==1){
                count++;
            }
        }
    }
    return count;
}

// print the inputted array (mainly used for testing)
void print(int arr[row][col])
{
    
    int i, j;
    printf("\n");
    for (i = 0; i < row; i++){
        printf("\n");
        for (j = 0; j < col; j++)
            printf("%d ", arr[i][j]);
    }
}

//advance the board one generation according to these rules:
/*
    1. A LIVE CELL WITH FEWER THAN TWO LIVE NEIGHBORS DIES
    2. A LIVE CELL WITH MORE THAN THREE LIVE NEIGHBORS ALSO DIES
    3. A LIVE CELL WITH EXACTLY TWO OR THREE NEIGHBORS LIVES
    4. A DEAD CELL WITH EXACTLY THREE LIVE NEIGHBORS BECOMES ALIVE
*/

void play (int board[row][col]){
    int i, j, num, newBoard[row][col];
    for (i = 0; i <= row; i++){
        for (j = 0; j < col; j++){
            num = numOfLiveNeighbors(board, i, j);
            if ((board[i][j]) && (num == 2 || num == 3)){
                newBoard[i][j] = 1;
            }
            else if (board[i][j] == 0 && num == 3){
                newBoard[i][j] = 1;
            }
            else {
                newBoard[i][j] = 0;
            }
        }
    }
// copy new board into old board
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            board[i][j] = newBoard[i][j];
        }
    }
}

// construct a 2d array out of the inputted file
void readFile ( int board[row][col], char *name){
    FILE *f;
    int i, j;

    f = fopen(name, "r");
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            fscanf(f, "%d", &board[i][j]);
        }
    }
    fclose (f);    
}

// output a file with the board of the current generation
void fileOut (int board[row][col], char *name){
    
    strcat (name, ".out");

    FILE *f;
    int i, j;
    f = fopen(name, "w");
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            fprintf(f, "%d ", board[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose (f);    
}

// main function
int main(int argc, char *argv[])
{
    // argc is number of arguments
    // argv is list of string containing command line arguments
    if (argc != 3){
        printf("Not valid input. Please input generation # and input file.\n");
    }

    // read how many times to play the game
    int targetGeneration;
    targetGeneration = atoi(argv[1]);
    
    // read the file and play the game for the amount of generations listed above
    int i;
    int board[row][col];
    readFile (board, argv[2]);
    for (i = 0; i < targetGeneration; i++){
        play(board);
    }
    
    // output a file at the final stage
    fileOut(board, argv[2]);
}




