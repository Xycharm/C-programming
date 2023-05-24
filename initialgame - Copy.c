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
#define X 30
#define N (X*X)
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4
#define FILLRATIO 0.35

void explore(int path[N], int ci, int length);

int lock = 1;
int start,dest;
int blockState[N];
//record the state of blocks{VACANT,BARRIER,RED(visualizing route),DEST,START}

int paths[500][N];//record the steps
int lengths[N];//the length of each path
int soFar, count;
int shown_count;

char *colors[]={0,"Black","Red","Yellow","Green"};//store the color strings

void InitGame() {
    Randomize();//Randomize Initialization
    do{
    	randMaze();//Randomize the Maze
        int path[N];
        int i;
        for(i = 0;i < N;i++){
        	path[i] = blockState[i];
	    } 
	    soFar = 99999999;
	    count = 0;
        explore(path, start, 0);
	}while(count == 0);//make sure that there's at least one path
	shown_count == 0;
    InitConsole();
    printf("yes\n");
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
    SetPenColor("Black");
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
    if (color == VACANT)return;
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;

    double px = (coordinate % X) * blockL;
    double py = (coordinate / X) * blockL;
    MovePen(px, py);
    SetPenColor(colors[color]);
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
    int i;
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
					InitGame();
					Display();
					break;
				case VK_F3:
					for(i = 0;i < N;i++){
						blockState[i] = VACANT;
					}
					Display();
					break;
				case VK_F4:
					Display();
					if(shown_count >= count){
						shown_count = 0; 
					}
					while(shown_count < count && lengths[shown_count] > soFar)
						    shown_count++;
					
					printf("%d/%d\n", shown_count, count);
					int j;
					for(j = 0;j < soFar;j++){
						printf("%d->",paths[shown_count][j]);
						colorBlock(RED, paths[shown_count][j]);
					}
					printf("\n");
					shown_count++;
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

void outerWall(){
	int i,j;
	for(i = 0;i < X;i++){
		blockState[i] = BARRIER;
	}
	for(j = 0;j <= X;j++){
		blockState[i+j*X] = BARRIER;
	}
	for(j = X-1;i >= 0;i--){
		blockState[i+j*X] = BARRIER;
	}
	for(i;j >= 0;j--){
		blockState[i+j*X] = BARRIER;
	}
}

 
void randMaze() {
    int i, k;
    for (i=0;i<N;i++){
    	blockState[i]=BARRIER;
	}
	

}
void explore(int path[N], int ci, int length){
	if(length > soFar)return;
	if(ci == dest && soFar >= length){
		int i, j = 0;
		for(i = 0;i < N;i++){
			if(path[i] == RED){
				paths[count][j] = i;
				j++;
			}
		}
		lengths[count] = length;
		soFar = (length < soFar ? length : soFar);
		count++;
	}else{
		int j;
	    int delta[4] = {1, X, -1, -X};
	    for(j = 0;j < 4;j++){
	    	int ni = ci + delta[j];
	    	if(path[ni] == VACANT || path[ni] == DEST){
	    		path[ni] = RED;
	    		explore(path, ni, length + 1);
				path[ni] = VACANT;
			}
		}
	}
}



