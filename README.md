# Maze Generator

This program is a maze generator, with a console-based menu and graphics drawn using `graphics.h`. The algorithm used for generating the mazes is a *randomized depth-first search* (or, a recursive backtracker), and the one used for the solution is a *breadth-first search shortest path algorithm.* 

## Examples
![Screenshot showing maze generation menu and drawn maze](/documentation/demo.png)
![Screenshot showing settings changed and drawn solution](/documentation/demo2.png)

## Structure

The `/src` directory contains 5 .c files:
+ **main.c**: This is the main application, which starts by running the function `displayMenu()` from `menu.c`
+ **menu.c**: This file holds the code for displaying the menu, reading user input for settings (stored in `../data/settings.txt`), and parsing the `settings.txt` file
+ **algorithm.c**: Uses *Cells*, a custom struct housed in `algorithm.h`, to initialize the 'grid' (i.e. a 2D array of *Cells*) the maze is generated on. This file also contains the maze generation algorithm, as well as the solver algorithm.
+ **graphics.c**: This file contains the auxiliary functions used for generating graphics.
+ **draw.c**: Takes the output from the algorithm along with the user-specified settings and draws the maze on screen (with the option of overlaying the solution).
