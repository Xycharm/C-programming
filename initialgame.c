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

<<<<<<< Updated upstream
#include"Block.h"

int blockState[N]={1,0,0,1};;
//char *colors[]={"Red","Black","Light Gray"};

void colorBlock(int color,int coordinate);
=======
#include "random.h"0
#define X 9
//must be odd
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4
//typedef struct{
//int i;
//int j;
//node* next;
//}node;

int visit[X][X];
int blockState[X][X];//TO DO:change into a structure array
int _blockState[X][X];

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
>>>>>>> Stashed changes





void InitGame(){
	Randomize();//Randomize Initialization
	randMaze();
}

<<<<<<< Updated upstream
void Display(){
	DisplayClear();
	int i=0;
	Barrier();
	for(i=0;i<N;i++){
		colorBlock(blockState[i],i);		
=======
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
void solve(int i, int j){
    visit[i][j]=1;
    printf("(%d,%d)",i,j);
    if(i==X-2&&j==X-2){
    	int mi,mj;
		for(mi=0;mi<X;mi++){
			for(mj=0;mj<X;mj++){
				_blockState[mi][mj]=blockState[mi][mj];
				if(visit[mi][mj]==1)blockState[mi][mj]=RED;
			}
		}
    	Display();
    	for(mi=0;mi<X;mi++){
			for(mj=0;mj<X;mj++){
				blockState[mi][mj]=_blockState[mi][mj];
			}
		}
	}
    int di[]={0,0,1,-1};
    int dj[]={1,-1,0,0};
    int k;
	for(k=0;k<4;k++){
        int _i=i+di[k];
        int _j=j+dj[k] ;
        if((blockState[_i][_j]==VACANT||blockState[_i][_j]==DEST) &&visit[_i][_j]==0){
            solve(_i,_j);
        }
    }
    visit[i][j]=0;

}

void ClearMaze(){
	int i,j;
	for(i=0;i<X;i++){
		for(j=0;j<X;j++){
			blockState[i][j]=VACANT;
		}
>>>>>>> Stashed changes
	}

}
<<<<<<< Updated upstream

void Main() 
{
	SetWindowTitle("Maze");
	SetWindowSize(10, 10);
    InitGraphics();
    InitGame();
    Display();
}

void Barrier(){
		
	double windowWidth = GetWindowWidth();
	double windowHeight = GetWindowHeight();
	double blockL = windowWidth/X;
	int j=0;
	for(j=0;j<X;j++){
		MovePen(j*blockL,0);
		DrawLine(0,windowHeight);
	}
	for(j=0;j<X;j++){
		MovePen(0,j*blockL);
		DrawLine(windowWidth,0);
	}
	
}                                         

void colorBlock(int color,int coordinate){
	if(blockState[coordinate]==VACANT)return;
	double windowWidth = GetWindowWidth();
	double windowHeight = GetWindowHeight();
	double blockL = windowWidth/X;

	double px=(coordinate%X)*blockL;
	double py=(coordinate/X)*blockL;
	MovePen(px, py);
	if(blockState[coordinate]==BARRIER){
		SetPenColor("Black");
	}else if(blockState[coordinate]==RED){
		SetPenColor("Red");
=======
void InitGame() {
	srand( (unsigned)time( NULL ) );
	int i,j;
	for(i=0;i<X;i++){
		for(j=0;j<X;j++){
			blockState[i][j]=BARRIER;
		}
>>>>>>> Stashed changes
	}
//    SetPenColor(colors[coordinate]);
    StartFilledRegion(1);
    DrawLine(0, blockL);
    DrawLine(blockL, 0);
    DrawLine(0, -blockL);
    DrawLine(-blockL, 0);
    EndFilledRegion();

	
}
<<<<<<< Updated upstream
=======
void SaveMap(){
	char filename[2048] = { 0 };
 	if (!SaveFileDialog("graphic file(*.data)\0*.data\0", filename)) 
 		return;
	
	FILE *fp;
	if (!(fp = fopen(filename, "wb"))) {
		MessageBox(NULL, filename, "fail to open",  MB_OK | MB_ICONWARNING);
		return;
	}
	fwrite(blockState,sizeof(int),X*X,fp);
	
	fclose(fp);
}
void LoadMap(){
	char filename[2048] = { 0 };
 	if (!OpenFileDialog("????(*.data)\0*.data\0", filename)) 
 		return;

	FILE *fp;
	if (!(fp = fopen(filename, "rb"))) {
		MessageBox(NULL, filename, "??????",  MB_OK | MB_ICONWARNING);
		return;
	}
	fread(blockState,sizeof(int),X*X,fp);
	fclose(fp);	
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
				case VK_F4://save map
					SaveMap();
					break;
				case VK_F5://read map
					LoadMap();
					Display();
					break;
				case VK_F12://exit
					exit(0);
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
				case 'S':
					solve(1,1);
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
	}
	Display();
}	

void Main() {
	
    SetWindowTitle("Maze");
    SetWindowSize(X, X);
    InitGraphics();
    InitConsole();
    InitGame();
    registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
    Display();
    
}






>>>>>>> Stashed changes
