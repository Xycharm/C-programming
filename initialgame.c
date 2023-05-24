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

#include "random.h"0
#define X 51
//must be odd
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4


int blockState[X][X];//TO DO:change into a structure array
struct{
	int i;
	int j;
}agent={1,1};
int lock_change=1;
char *colors[]={0,"Black","Red","Yellow","Green"};//store the color strings
int check(int i,int j){//return 0 if cant else 1
    if(i<0||i>=X||j<0||j>=X)return 0;
    if(blockState[i][j]==VACANT)return 0;
    if(blockState[i][j]==BARRIER)return 1;
    return -1;
}
int direction_feasible(int i, int j){



    int k=0;
    for(k=0;k<4;k++){
        
        switch (k) {
            case 0:
                if(check(i,j+2)!=0)return 0;
                break;
            case 1:
                if(check(i+2,j)!=0)return 1;
                break;
            case 2:
                if(check(i,j-2)!=0)return 2;
                break;
            case 3:
                if(check(i-2,j)!=0)return 3;
                break;
        }

    }



    return -1;
    //return -1 /*reversed 0up 1right 2down 3left
}
int direction_judge(int i, int j,int dir){

        switch (dir) {
            case 0:
                if(check(i,j+2)!=0)return 1;
                break;
            case 1:
                if(check(i+2,j)!=0)return 1;
                break;
            case 2:
                if(check(i,j-2)!=0)return 1;
                break;
            case 3:
                if(check(i-2,j)!=0)return 1;
                break;
        }




    return -1;
    //return -1 /*reversed 0up 1right 2down 3left
}

void randomDFS(int i,int j){
    if (direction_feasible(i,j)==-1) return;
    int rand_way=rand()%4;
    int k;
	for(k=0;k<4;k++) {
        if(direction_judge(i,j,(k+rand_way)%4)==1){
            switch ((k+rand_way)%4) {
                case 0:
                    if (blockState[i][j + 1] == BARRIER) {
                        blockState[i][j + 1] = VACANT;
                    }
                    if (blockState[i][j + 2] == BARRIER) {
                        blockState[i][j + 2] = VACANT;
                    }
                    randomDFS(i, j + 2);
                    break;
                case 1:
                    if (blockState[i + 1][j] == BARRIER) {
                        blockState[i + 1][j] = VACANT;
                    }
                    if (blockState[i + 2][j] == BARRIER) {
                        blockState[i + 2][j] = VACANT;
                    }
                    randomDFS(i + 2, j);
                    break;
                case 2:
                    if (blockState[i][j - 1] == BARRIER) {
                        blockState[i][j - 1] = VACANT;
                    }
                    if (blockState[i][j - 2] == BARRIER) {
                        blockState[i][j - 2] = VACANT;
                    }
                    randomDFS(i, j - 2);
                    break;
                case 3:
                    if (blockState[i - 1][j] == BARRIER) {
                        blockState[i - 1][j] = VACANT;
                    }
                    if (blockState[i - 2][j] == BARRIER) {
                        blockState[i - 2][j] = VACANT;
                    }
                    randomDFS(i - 2, j);
                    break;


            }
        }

    }
}

void ClearMaze(){
	int i,j;
	for(i=0;i<X;i++){
		for(j=0;j<X;j++){
			blockState[i][j]=VACANT;
		}
	}
	blockState[1][1]=START;
	blockState[X-2][X-2]=DEST;
		for(i=0;i<X;i++){
		blockState[i][0]=BARRIER;
		blockState[i][X-1]=BARRIER;
		blockState[0][i]=BARRIER;
		blockState[X-1][i]=BARRIER;
		}
			
	//outer surrounding unchangable: array use structure
}
void InitGame() {
	srand( (unsigned)time( NULL ) );
	int i,j;
	for(i=0;i<X;i++){
		for(j=0;j<X;j++){
			blockState[i][j]=BARRIER;
		}
	}
	blockState[1][1]=START;
	blockState[X-2][X-2]=DEST;
	randomDFS(1,1);
}
void Display() {//(re)display the changes
    DisplayClear();
    int i = 0,j = 0;
    Barrier();
    for (i = 0; i < X; i++) {
		for(j=0;j<X;j++ ){
			colorBlock(blockState[i][j],i,j);
		}
    }
    
    colorBlock(RED,agent.i,agent.j);
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

void colorBlock(int color, int x,int y) { //Draw the color blocks
    if (color == VACANT)return;
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;

    double px = x * blockL;
    double py = y * blockL;
    MovePen(py, px);
    SetPenColor(colors[color]);
    StartFilledRegion(1);
    DrawLine(0, blockL);
    DrawLine(blockL, 0);
    DrawLine(0, -blockL);
    DrawLine(-blockL, 0);
    EndFilledRegion();



}

void KeyboardEventProcess(int key,int event){//Keyboard
    int i;
	switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_F1:
					if(lock_change==1){
						ClearMaze();//To DO :the surrounding barriers
						Display();
						lock_change=1-lock_change;
					}else{
						lock_change=1-lock_change;
					}
					break;
				case VK_F2:
					InitGame();
					Display();
					lock_change=1;
					break;
				case VK_F4:
					break;
				case VK_UP:
					if(check(agent.i+1,agent.j)!=1)
					agent.i++;
					Display();
					break;
				case VK_DOWN:
					if(check(agent.i-1,agent.j)!=1)
					agent.i--;
					Display();
					break;
				case VK_LEFT:
					if(check(agent.i,agent.j-1)!=1)
					agent.j--;
					Display();
					break;
				case VK_RIGHT:
					if(check(agent.i,agent.j+1)!=1)
					agent.j++;
					Display();
					break;
			}
			break;
		case KEY_UP:
			break;
	
	}
}

void MouseEventProcess(int x, int y, int button, int event){
	if(lock_change == 1) return;
	double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;
	
    uiGetMouse(x,y,button,event); 
	if (button == LEFT_BUTTON && event == BUTTON_DOWN ) {
	
		int i,j;
		int curCoordinateI = -1,curCoordinateJ = -1;
		double xx = ScaleXInches(x);
		double yy = ScaleYInches(y);
		for(i=0;i<X;i++){
			for(j=0;j<X;j++){
				double pi = i * blockL;
            	double pj = j * blockL;
				if(xx > pj && xx < pj + blockL && yy > pi && yy < pi + blockL){
					curCoordinateI = i;
					curCoordinateJ = j; 
					break;
				}			
			}
		}
		
		if(curCoordinateI>=0&&curCoordinateJ>=0&&(blockState[curCoordinateI][curCoordinateJ]== VACANT||blockState[curCoordinateI][curCoordinateJ]== BARRIER)){
			blockState[curCoordinateI][curCoordinateJ]=1-blockState[curCoordinateI][curCoordinateJ];
		}
		
		
//		if (curCoordinate < N  && curCoordinate >= 0 && blockState[curCoordinate] == VACANT) {
//		 	blockState[curCoordinate] = BARRIER;
//		}else if(curCoordinate < N && curCoordinate >= 0 && blockState[curCoordinate] == BARRIER){
//		 	blockState[curCoordinate] = VACANT;
//		}
	}
	Display();
}	

void Main() {
	
    SetWindowTitle("Maze");
    SetWindowSize(X, X);
    InitGraphics();
    InitGame();
    registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
    Display();
    
}






