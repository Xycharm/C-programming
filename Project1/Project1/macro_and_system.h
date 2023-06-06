#ifndef macro
#define macro
//system & graphics libraries
#include "libgraphics\graphics.h"
#include "libgraphics\extgraph.h"
#include "libgraphics\genlib.h"
#include "libgraphics\imgui.h"
#include "libgraphics\simpio.h"
#include "libgraphics\random.h"
#include "libgraphics\strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "libgraphics\linkedlist.h"
#include "libgraphics\random.h"
#include <time.h>

#define X 23 //number of blocks in a row/column
//must be odd
//define the state(color) of a block
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4
#define ANOTHER  5
//#define Epoch 99
extern int biplayer;
extern char *colors[];
extern int blockState[X][X];
struct Agent {
    int i;
    int j;
};
extern struct Agent agent,another_agent;

void Barrier();

void colorBlock(int color, int x, int y);

void About();

void Guide();

void LoadMap();

void SaveMap();

int check(int i, int j);

int direction_feasible(int i, int j);

int direction_judge(int i, int j, int dir);

void randomDFS(int i, int j);

void lock(int lock_change);

void Display();

void block_display();

void subtitle(char *title);

void InitGame();


#endif // !macro




