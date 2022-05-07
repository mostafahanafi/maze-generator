// Maze Generation Program. By Mostafa Hanafi, UCL
#include <stdio.h> 
#include <stdlib.h> // rand(); srand();
#include <string.h> // strcmp();
#include <time.h> // seed
#include "graphics.h" // drawing the grid
#include "menu.h" // access to all variables, readSettings();
#include "algorithm.h" // struct Cell, maze algorithms

#define GRID_DIMENSIONS dimensions
#define CANVAS_DIMENSIONS (GRID_DIMENSIONS+100) // margin=100;
// (origin_x, origin_y) = top left of grid, used for drawing
#define ORIGIN_X (CANVAS_DIMENSIONS/2 - GRID_DIMENSIONS/2)
#define ORIGIN_Y (CANVAS_DIMENSIONS/2 - GRID_DIMENSIONS/2)

#define SIZE complexity
#define GRID_SIZE SIZE*SIZE
#define NUM_WALLS (2*SIZE-1)
#define SPACING GRID_DIMENSIONS/SIZE

#define BG_COLOR stringToColour(bgStr)
#define FG_COLOR stringToColour(fgStr)

colour stringToColour(char colour[]) {
    if (!strcmp(colour, "black")) return black;
    if (!strcmp(colour, "blue")) return blue;
    if (!strcmp(colour, "cyan")) return cyan;
    if (!strcmp(colour, "darkgray")) return darkgray;
    if (!strcmp(colour, "gray")) return gray;
    if (!strcmp(colour, "green")) return green;
    if (!strcmp(colour, "lightgray")) return lightgray;
    if (!strcmp(colour, "magenta")) return magenta;
    if (!strcmp(colour, "orange")) return orange;
    if (!strcmp(colour, "pink")) return pink;
    if (!strcmp(colour, "red")) return red;
    if (!strcmp(colour, "white")) return white;
    if (!strcmp(colour, "yellow")) return yellow;
    return white; // never runs
}

int** initializeWalls() {
    int **walls = malloc( sizeof(int*) * SIZE );
    for (int row = 0; row < SIZE; row++) {
        walls[row] = malloc( sizeof(int) * NUM_WALLS );
        for (int col = 0; col < NUM_WALLS; col++) {
            // all walls currently drawn
            walls[row][col] = 1;
        }
    }
    return walls;
}

void deleteWalls(int **walls) {
    for (int row=0; row<SIZE; row++) {
        free(walls[row]);
    }
    free(walls);
}

void drawGrid(int **walls) {
    setColour(BG_COLOR);
    fillRect(0,0,CANVAS_DIMENSIONS,CANVAS_DIMENSIONS);
    setColour(FG_COLOR);
    drawRect(ORIGIN_X, ORIGIN_Y, GRID_DIMENSIONS, GRID_DIMENSIONS);
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < NUM_WALLS; col++) {
            if (col % 2 == 1) { // vertical line
                if (walls[row][col] == 1) {
                    drawLine( ORIGIN_X+(col/2+1)*GRID_DIMENSIONS/SIZE, ORIGIN_Y+row*GRID_DIMENSIONS/SIZE, 
                              ORIGIN_X+(col/2+1)*GRID_DIMENSIONS/SIZE, ORIGIN_Y+(row+1)*GRID_DIMENSIONS/SIZE );
                }
            }
            else { // horizontal line
                if (walls[row][col] == 1) {
                    drawLine( ORIGIN_X+(col/2)*GRID_DIMENSIONS/SIZE, ORIGIN_Y+row*GRID_DIMENSIONS/SIZE, 
                              ORIGIN_X+(col/2+1)*GRID_DIMENSIONS/SIZE, ORIGIN_Y+row*GRID_DIMENSIONS/SIZE );
                }
            }
        }
    }

    setColour(BG_COLOR);
    drawLine(ORIGIN_X, ORIGIN_Y, ORIGIN_X, ORIGIN_Y+SPACING);
    drawLine(ORIGIN_X + SPACING*SIZE, ORIGIN_Y + SPACING*(SIZE-1), 
             ORIGIN_X + SPACING*SIZE, ORIGIN_Y + SPACING*SIZE);
}

void drawSolution(struct Cell grid[], int solution[])
{
    int endDistance = grid[GRID_SIZE-1].distanceFromStart;
    if ((BG_COLOR == red || BG_COLOR == green) && (FG_COLOR == red || FG_COLOR == green)) {
        setColour(blue);
    }
    else if (BG_COLOR == red || FG_COLOR == red) {
        setColour(green);
    } else {
        setColour(red);
    }

    for (int i=0; i<endDistance; i++)
    {
        int currentValue = solution[i];
        int currentRow = grid[solution[i]].y;
        int centerRow = ORIGIN_Y + SPACING*currentRow + SPACING/2;
        int currentCol = grid[solution[i]].x;
        int centerCol = ORIGIN_X + SPACING*currentCol + SPACING/2;

        int nextValue = solution[i+1];
        int nextRow = grid[solution[i+1]].y;
        int nextCenterRow = ORIGIN_Y + SPACING*nextRow + SPACING/2;
        int nextCol = grid[solution[i+1]].x;
        int nextCenterCol = ORIGIN_X + SPACING*nextCol + SPACING/2;

        drawLine(centerRow, centerCol, nextCenterRow, nextCenterCol);
    }
}

int main(void) {
    readSettings();
    setWindowSize(CANVAS_DIMENSIONS,CANVAS_DIMENSIONS);

    struct Cell grid[GRID_SIZE];
    initializeGrid(grid);

    recursiveBacktracking(grid, seed);
    int** walls;
    walls = initializeWalls();
    gridToWallArray(grid, walls);
    drawGrid(walls);
    if (solved)
    {
        int solution[GRID_SIZE];
        solve(grid, solution, seed);
        drawSolution(grid, solution);
    }
    deleteWalls(walls);
}