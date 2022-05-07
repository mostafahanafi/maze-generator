// Maze Generation Program. By Mostafa Hanafi, UCL
#include <stdio.h>
#include <stdlib.h>
#include "menu.h" // complexity
#include "algorithm.h"

#define SIZE complexity
#define GRID_SIZE SIZE*SIZE
#define MAX 8100 // 90*90 i.e. maximum GRID_SIZE

enum Direction {North, East, South, West};
void initializeGrid(struct Cell grid[])
{
    for (int row=0; row<SIZE; row++)
    {
        for (int col=0; col<SIZE; col++)
        {
            grid[row*SIZE + col].x = row;
            grid[row*SIZE + col].y = col;
            for (int i=0; i<4; i++)
            {
                grid[row*SIZE + col].links[i] = 0;
            }
            grid[row*SIZE + col].visited = 0;
            grid[row*SIZE + col].distanceFromStart = GRID_SIZE;
        }
    }
}
int isLinked(struct Cell grid[], int cellNum, int direction)
{
    return grid[cellNum].links[direction];
}
void gridToWallArray(struct Cell grid[], int **walls)
{
    for (int row=0;row<SIZE;row++)
    {
        for (int col=0;col<SIZE-1;col++)
        {
            if (isLinked(grid, row*SIZE+col, East))
            {
                walls[row][2*col+1] = 0;
            }
        }
    }
    for (int row=0;row<SIZE-1;row++)
    {
        for (int col=0;col<SIZE;col++)
        {
            if (isLinked(grid, row*SIZE+col, South))
            {
                walls[row+1][2*col] = 0;
            }
        }
    }
}

int hasNeighbor(struct Cell grid[], int cellNum, int direction)
{
    if ( (direction == North && grid[cellNum].x > 0)     ||
         (direction == East && grid[cellNum].y < SIZE-1)  ||
         (direction == South && grid[cellNum].x < SIZE-1)   ||
         (direction == West && grid[cellNum].y > 0) )
    {
        return 1;
    }
    else return 0;
}
struct Cell neighbor(struct Cell grid[], int cellNum, int direction)
{
    switch (direction)
    {
    case North:
        if (hasNeighbor(grid, cellNum, North))
        {
            return grid[cellNum-SIZE];
        }
        break;
    case East:
        if (hasNeighbor(grid, cellNum, East))
        {
            return grid[cellNum+1];
        }
        break;
    case South:
        if (hasNeighbor(grid, cellNum, South))
        {
            return grid[cellNum+SIZE];
        }
        break;
    case West:
        if (hasNeighbor(grid, cellNum, West))
        {
            return grid[cellNum-1];
        }
        break;
    default:
        break;
    }
    struct Cell null;
    return null;
}
void link(struct Cell grid[], int cellNum, int direction)
{
    if (hasNeighbor(grid, cellNum, direction))
    {
        switch (direction) {
            case North :
                grid[cellNum].links[North] = 1;
                grid[cellNum-SIZE].links[South] = 1;
                break;

            case East :
                grid[cellNum].links[East] = 1;
                grid[cellNum+1].links[West] = 1;
                break;

            case South :
                grid[cellNum].links[South] = 1;
                grid[cellNum+SIZE].links[North] = 1;
                break;

            case West :
                grid[cellNum].links[West] = 1;
                grid[cellNum-1].links[East] = 1;
                break;

            default :
                printf("ERROR: Invalid direction\n");
        }
    }
    else {
        printf("ERROR: Could not link cells\n");
    }
}
int allVisited(struct Cell grid[])
{
    for (int i=0; i<GRID_SIZE; i++)
    {
        if (!grid[i].visited)
        {
            return 0;
        }
    }
    return 1;
}

// easy algorithms to implement, although these functions worked they
// just looked bad and had more problems than the algorithm chosen
void binaryTree(struct Cell grid[], int seed)
{
    srand(seed);
    for (int i=0; i<GRID_SIZE; i++)
    {
        if (hasNeighbor(grid, i, South) && hasNeighbor(grid, i, East))
        {
            if (rand() % 2 == 0) 
            {
                link(grid, i, South);
            }
            else 
            {
                link(grid, i, East);
            }
        }
        else if (hasNeighbor(grid, i, East)) 
        {
            link(grid, i, East);
        }
        else if (hasNeighbor(grid, i, South)) 
        {
            link(grid, i, South);
        }
    }
}
void sidewinder(struct Cell grid[], int seed)
{
    srand(seed);
    int cellsInLink = 1;
    for (int i=0; i<GRID_SIZE; i++)
    {
        if (hasNeighbor(grid, i, South) && hasNeighbor(grid, i, East))
        {
            if (rand() % 2 == 0) 
            {
                int randomCellNum = rand() % cellsInLink;
                link(grid, i-randomCellNum, South);
                cellsInLink = 1;
            }
            else 
            {
                link(grid, i, East);
                cellsInLink++;
            }
        }
        else if (hasNeighbor(grid, i, East)) 
        {
            link(grid, i, East);
        }
        else if (hasNeighbor(grid, i, South)) 
        {
            int randomCellNum = rand() % cellsInLink;
            link(grid, i-randomCellNum, South);
            cellsInLink = 1;
        }
    }
}
// chosen algorithm
void recursiveBacktracking(struct Cell grid[], int seed)
{
    srand(seed);
    int stack[MAX] = {0};
    do {
        int stackIndex, currentValue;
        int numUnvisitedDirs = 0;

        for (int i=0; i<MAX; i++)
        {
            if (stack[i+1] == 0)
            {
                stackIndex = i;
                currentValue = stack[i];
                grid[currentValue].visited = 1;
                break;
            }
        }
        
        for (int dir=0; dir<4; dir++)
        {
            if (hasNeighbor(grid, currentValue, dir))
            {
                if (!neighbor(grid, currentValue, dir).visited)
                {
                    numUnvisitedDirs++;
                }
            }
        }
        
        if (numUnvisitedDirs)
        {
            int unvisitedDirs[numUnvisitedDirs];
            int dirIndex = 0;
            for (int dir=North; dir<=West; dir++)
            {
                if (hasNeighbor(grid, currentValue, dir))
                {
                    if (!neighbor(grid, currentValue, dir).visited)
                    {
                        unvisitedDirs[dirIndex] = dir;
                        dirIndex++;
                    }
                }
            }

            int randomDir = rand() % numUnvisitedDirs;
            link(grid, currentValue, unvisitedDirs[randomDir]);
            int nextValue = (neighbor(grid, currentValue, unvisitedDirs[randomDir]).x * SIZE) + 
                             neighbor(grid, currentValue, unvisitedDirs[randomDir]).y;
            stack[stackIndex+1] = nextValue;
        }
        
        else
        {
            stack[stackIndex] = 0;
        }
    } while (!allVisited(grid));
}

void solve(struct Cell grid[], int solution[], int seed)
{
    int currentCells[MAX] = {0};
    int nextCells[MAX] = {0};
    for (int i=0; i<GRID_SIZE; i++)
    {
        grid[i].visited = 0;
        solution[i] = 0;
    }

    grid[0].distanceFromStart = 0;
    currentCells[0] = 0;
    int distance = 1;
    int currentIndex;
    int nextIndex;
    do {
        currentIndex=0;
        nextIndex=0;
        do {
            for (int dir=0; dir<4; dir++)
            {
                if (hasNeighbor(grid, currentCells[currentIndex], dir))
                {
                    if (isLinked(grid, currentCells[currentIndex], dir) && !neighbor(grid, currentCells[currentIndex], dir).visited)
                    {
                        int neighborIndex = neighbor(grid, currentCells[currentIndex], dir).x*SIZE +
                                            neighbor(grid, currentCells[currentIndex], dir).y;
                        nextCells[nextIndex] = neighborIndex;
                        nextIndex++;
                        if (distance < grid[neighborIndex].distanceFromStart)
                            grid[neighborIndex].distanceFromStart = distance;
                    }
                }
            }
            grid[currentCells[currentIndex]].visited = 1;
            currentIndex++;
        } while (currentCells[currentIndex] != 0);
        distance++;

        currentIndex = 0;
        do {
            currentCells[currentIndex] = 0;
            currentIndex++;
        } while (currentCells[currentIndex] != 0);

        currentIndex = 0;
        while (currentIndex < nextIndex)
        {
            currentCells[currentIndex] = nextCells[currentIndex];
            nextCells[currentIndex] = 0;
            currentIndex++;
        }
    } while (!allVisited(grid));

    int endDistance = grid[GRID_SIZE-1].distanceFromStart;
    int currentDistance = endDistance;
    solution[currentDistance] = grid[GRID_SIZE-1].x*SIZE + grid[GRID_SIZE-1].y;
    int index = solution[currentDistance];
    
    while (currentDistance > 0)
    {
        currentDistance--;
        for (int dir=0; dir<4; dir++)
        {
            if (hasNeighbor(grid, index, dir))
            {
                if (neighbor(grid, index, dir).distanceFromStart == currentDistance)
                {
                    int prevIndex = neighbor(grid, index, dir).x*SIZE +
                                    neighbor(grid, index, dir).y;
                    solution[currentDistance] = prevIndex;
                    index = prevIndex;
                    break;
                }
            }
        }
    }
}
