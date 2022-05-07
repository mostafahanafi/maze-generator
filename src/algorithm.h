#ifndef ALGORITHM_H_
#define ALGORITHM_H_

struct Cell 
{
    int x;
    int y;
    int links[4];
    int visited;
    int distanceFromStart;
};

void initializeGrid(struct Cell grid[]);
void gridToWallArray(struct Cell[], int**);
void recursiveBacktracking(struct Cell[], int);
void solve(struct Cell[], int[], int);

#endif