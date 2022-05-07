#ifndef MENU_H_
#define MENU_H_

void displayMenu(void);
void readSettings(void);

extern int dimensions;
extern int complexity;
extern char fgStr[];
extern char bgStr[];
extern int solved;
extern int seed;

#endif