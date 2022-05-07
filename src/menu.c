// Maze Generation Program. By Mostafa Hanafi, UCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"

int complexity, complexitySetting;
char bgStr[10];
char fgStr[10];
int dimensions, dimensionsSetting;
int solved;
int seed;

char colours[][10] = {"black", "blue", "cyan", "darkgray", "gray", "green", 
                      "lightgray", "magenta", "orange", "pink", "red", "white", "yellow"};

int isColour(char colour[]) {
    for (int i = 0; i < 13; i++)
    {
        if (!strcmp(colours[i], colour)) {
            return 1;
        }
    }
    return 0;
}

FILE *settings;

void updateSettings(void) {
    settings = fopen("../data/settings.txt", "w+");
    fprintf(settings, "%d ", complexity);
    fprintf(settings, "%s ", bgStr);
    fprintf(settings, "%s ", fgStr);
    fprintf(settings, "%d ", solved);
    fprintf(settings, "%d ", seed);
    fprintf(settings, "%d ", dimensions);
    fclose(settings);
}

void initializeSettings(void) {
    complexitySetting = 3;
    complexity = 20;
    dimensionsSetting = 2;
    dimensions = 360;
    strcpy(bgStr, "white");
    strcpy(fgStr, "black");
    solved = 0;
    seed = 1;
    updateSettings();
}

void readSettings(void) {
    settings = fopen("../data/settings.txt", "r");
    fscanf(settings, "%d", &complexity);
    fscanf(settings, "%s", &bgStr);
    fscanf(settings, "%s", &fgStr);
    fscanf(settings, "%d", &solved);
    fscanf(settings, "%d", &seed);
    fscanf(settings, "%d", &dimensions);
    fclose(settings);
}

void displayMenu(void)
{   
    char input;
    initializeSettings();
    do {
        system("clear");
        readSettings();
        printf("\033[1;34m          Maze Generator \033[0m \n");
        printf("0) Set default settings\n");
        printf("1) Draw new maze\n");
        printf("2) Show solution for maze\n");
        printf("3) Set complexity (current=%d)\n", complexitySetting);
        printf("4) Set background color (current=%s)\n", bgStr);
        printf("5) Set foreground color (current=%s)\n", fgStr);
        printf("6) Set maze dimensions (current=%d)\n", dimensionsSetting);
        printf("7) Play today's maze of the day!\n");
        printf("8) Show today's MOTD solution\n");
        printf("Q) Quit\n");
        printf("> ");
        scanf(" %c", &input);

        int tempInt;
        char tempStr[30];

        switch (input) {
            case '0' :
                initializeSettings();
                break;

            case '1' :
                if (!(strcmp(fgStr, bgStr)))
                {
                    printf("ERROR: Foreground color and background color cannot be equal [ENTER]\n");
                    getchar(); getchar();
                }
                else {
                    seed = time(0);
                    solved = 0;
                    updateSettings();
                    system("gcc -o run -w draw.c menu.c graphics.c algorithm.c");
                    system("./run | java -jar drawapp.jar");
                }
                break;
            
            case '2' :
                solved = 1;
                updateSettings();
                system("gcc -o run -w draw.c menu.c graphics.c algorithm.c");
                system("./run | java -jar drawapp.jar");
                break;

            case '3' :
                printf("Enter complexity (1-6)\n");
                printf("(1) Very Easy\n");
                printf("(2) Easy\n");
                printf("(3) Medium\n");
                printf("(4) Hard\n");
                printf("(5) Very Hard\n");
                printf("(6) Impossible* \n*(okay, not actually)\n");
                printf("> ");
                scanf(" %d", &tempInt);
                switch (tempInt)
                {
                case 1:
                    complexity = 10;
                    complexitySetting = tempInt;
                    break;
                case 2:
                    complexity = 15;
                    complexitySetting = tempInt;
                    break;
                case 3:
                    complexity = 20;
                    complexitySetting = tempInt;
                    break;
                case 4:
                    complexity = 30;
                    complexitySetting = tempInt;
                    break;
                case 5:
                    complexity = 45;
                    complexitySetting = tempInt;
                    break;
                case 6:
                    complexity = 90;
                    complexitySetting = tempInt;
                    break;
                default:
                    printf("ERROR: Number should be between 1-6 [ENTER]\n");
                    getchar(); getchar();
                }
                break;
            
            case '4' :
                printf("Enter background colour: ");
                scanf(" %s", &tempStr);
                if (!isColour(tempStr)) {
                    printf("ERROR: Not a recognized colour [ENTER]\n");
                    getchar(); getchar();
                }
                else {
                    strcpy(bgStr, tempStr);
                }
                printf("\n");
                break;
            
            case '5' :
                printf("Enter foreground colour: ");
                scanf(" %s", &tempStr);
                if (!isColour(tempStr)) {
                    printf("ERROR: Not a recognized colour [ENTER]\n");
                    getchar(); getchar();
                }
                else {
                    strcpy(fgStr, tempStr);
                }
                printf("\n");
                break;

            case '6' :
                printf("Enter dimensions (1-3)\n");
                printf("(1) Small (180x180)\n");
                printf("(2) Medium (360x360)\n");
                printf("(3) Large (540x540)\n");
                printf("> ");
                scanf(" %d", &tempInt);
                switch (tempInt)
                {
                case 1:
                    dimensions = 180;
                    dimensionsSetting = tempInt;
                    break;
                case 2:
                    dimensions = 360;
                    dimensionsSetting = tempInt;
                    break;
                case 3:
                    dimensions = 540;
                    dimensionsSetting = tempInt;
                    break;
                default:
                    printf("ERROR: Number should be between 1-3 [ENTER]\n");
                    getchar(); getchar();
                }
                break;
            
            case '7' :
                initializeSettings();
                seed = time(0)/86400; // sec / (60sec * 60min * 24hr)
                complexity = 30; 
                solved = 0;
                updateSettings();
                system("gcc -o run -w draw.c menu.c graphics.c algorithm.c");
                system("./run | java -jar drawapp.jar");

                break;
            
            case '8' :
                initializeSettings();
                seed = time(0)/86400; // sec % (60sec * 60min * 24hr)
                complexity = 30;
                solved = 1;
                updateSettings();
                system("gcc -o run -w draw.c menu.c graphics.c algorithm.c");
                system("./run | java -jar drawapp.jar");
                break;

            case 'Q' : break;

            default : printf("Error: Input must be valid integer or Q. [ENTER]\n");
            getchar(); getchar();
        }
        updateSettings();
    } while (input != 'Q');
}