# Maze Generator

This program is a maze generator, with a console-based menu and graphics drawn using `graphics.h`. The algorithm used for generating the mazes is a *randomized depth-first search* (or, a recursive backtracker), and the one used for the solution is a *breadth-first search shortest path algorithm.* 

## Examples

![Screenshot showing maze generation menu and drawn maze](/documentation/demo.png)
![Screenshot showing settings changed and drawn solution](/documentation/demo2.png)

## Compilation

To make things easier, there is a Makefile in the src directory, so running `make` will compile the file and produce a `./main` executable. If this doesn’t work, run `gcc -o main main.c menu.c -w`.

Once compiled, run the program using `./main`.

## Usage

To interact with the menu, enter the integer number \[0-8\] corresponding to the option or `Q` to quit the program.

**(0)** resets the program to default settings.

**(1)** generates an entirely new maze every time, using the specified settings and complexity, and **(2)** shows the solution for the last generated maze.

**(3)** allows the user to change the complexity of the maze:
1. *Very Easy*
2. *Easy*
3. *Medium*
4. *Hard*
5. *Very Hard*
6. *Impossible*

**(4)** and **(5)** allow the user to change the background and foreground color of the maze respectively by entering the name of the color. The recognized color inputs are:
+ black
+ blue
+ cyan
+ darkgray
+ gray
+ green
+ lightgray
+ magenta
+ orange
+ pink
+ red
+ white
+ yellow

**(6)** lets the user select the dimensions of the maze window:
1. Small (180x180)
2. Medium (360x360)
3. Large (540x540)

**(7)** and **(8)** are similar to **(1)** and **(2)** as they also draw a maze and show its solution respectively; however, the maze for **(7)** and **(8)** (named MOTD, or Maze of the Day) is generated using a set seed corresponding to the day. This not only means that the seed remains the same for the entire day, but that the seed is a brand new number each day.

## Structure

The `/src` directory contains 5 C files:
+ **main.c**: This is the main application, which starts by running the function `displayMenu()` from `menu.c`
+ **menu.c**: This file holds the code for displaying the menu, reading user input for settings (stored in `../data/settings.txt`), and parsing the `settings.txt` file
+ **algorithm.c**: Uses *Cells*, a custom struct housed in `algorithm.h`, to initialize the 'grid' (i.e. a 2D array of *Cells*) the maze is generated on. This file also contains the maze generation algorithm, as well as the solver algorithm.
+ **graphics.c**: This file contains the auxiliary functions used for generating graphics.
+ **draw.c**: Takes the output from the algorithm along with the user-specified settings and draws the maze on screen (with the option of overlaying the solution).
