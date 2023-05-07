#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
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

#include "linkedlist.h"

#include "random.h"
#define X 75
#define N (X*X)
#define VACANT 0
#define BARRIER    1
#define    RED 2
#define DEST 3
#define FILLRATIO 0.25 //filling ratio of blocks is 0.25 

int lock = 1;
int blockState[N];
//record the state of blocks{VACANT,BARRIER,RED(visualizing route),DEST(start/end)}
char *colors[]={0,"Black","Red","Yellow"};//store the color strings
void InitGame() {
    Randomize();//Randomize Initialization
    randMaze();//Randomize the Maze
}
void Display() {//(re)display the changes
    DisplayClear();
    int i = 0;
    Barrier();
    for (i = 0; i < N; i++) {
        colorBlock(blockState[i], i);
    }
}



void Barrier() {//Draw the grids
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;
    int j = 0;
    for (j = 0; j < X; j++) {
        MovePen(j * blockL, 0);
        DrawLine(0, windowHeight);
    }
    for (j = 0; j < X; j++) {
        MovePen(0, j * blockL);
        DrawLine(windowWidth, 0);
    }
}

void colorBlock(int color, int coordinate) { //Draw the color blocks
    if (blockState[coordinate] == VACANT)return;
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;

    double px = (coordinate % X) * blockL;
    double py = (coordinate / X) * blockL;
    MovePen(px, py);
    SetPenColor(colors[blockState[coordinate]]);
    StartFilledRegion(1);
    DrawLine(0, blockL);
    DrawLine(blockL, 0);
    DrawLine(0, -blockL);
    DrawLine(-blockL, 0);
    EndFilledRegion();



}

void MouseEventProcess(int x, int y, int button, int event){
	if(lock == 1) return;
	double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;
	
    uiGetMouse(x,y,button,event); 
	if (button == LEFT_BUTTON && event == BUTTON_DOWN ) {
	
		int i;
		int curCoordinate = -1;
		double xx = ScaleXInches(x);
		double yy = ScaleYInches(y);
		for(i=0;i<N;i++){
			double px = (i % X) * blockL;
            double py = (i / X) * blockL;
			if(xx > px && xx < px + blockL && yy > py && yy < py + blockL){
				curCoordinate = i;
				break;
			}
		}
		if (curCoordinate < N  && curCoordinate >= 0 && blockState[curCoordinate] == VACANT) {
		 	blockState[curCoordinate] = BARRIER;
		}else if(curCoordinate < N && curCoordinate >= 0 && blockState[curCoordinate] == BARRIER){
		 	blockState[curCoordinate] = VACANT;
		}
	}
	Display();
}	


void KeyboardEventProcess(int key,int event){//Keyboard
	switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_F1:
					if(lock == 1){
						lock = 0;
						registerMouseEvent(MouseEventProcess);
					}else{
						lock = 1;
					}
					break;
				case VK_F2:
					randMaze();
					Display();
			}
			break;
		case KEY_UP:
			break;
	
	}
}


void Main() {
    SetWindowTitle("Maze");
    SetWindowSize(X, X);
    InitGraphics();
    InitGame();
    Display();
    registerKeyboardEvent(KeyboardEventProcess);
}
void randMaze() {
    int i, k;
    for (i=0;i<N;i++){
    	blockState[i]=0;
	}
	        i = rand() % N;
        if (blockState[i] == VACANT) {
            blockState[i] = DEST;
        }
        	        i = rand() % N;
        if (blockState[i] == VACANT) {
            blockState[i] = DEST;
        }
    for (k = 0; k < FILLRATIO*N; k++) {

        while (1) {
            i = rand() % N;
            if (blockState[i] == VACANT) {
                blockState[i] = BARRIER;
                break;
            }
        }
    }
}
