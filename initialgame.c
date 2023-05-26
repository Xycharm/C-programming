#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "imgui.h"
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
#define X 11
//must be odd
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4


int blockState[X][X];//record the states of blocks
int visit[X][X];//record traces
int count;//record the number of traces
int _visit[99][X][X];//backup of 'visit'
int _blockState[X][X];//backup of 'blockState'
struct{int i;int j;}agent = {1,1};//the position of agent
int lock_change = 1;//whether being able to change the map
int play = 0;
char *colors[]={0,"Black","Red","Yellow","Green"};//store the color strings
int check(int i,int j){
	//used while generating the maze,if 
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
    //return -1 if infeasible,otherwise  0up 1right 2down 3left(in array-coordinate)
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
	play = 0;
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
	agent.i=1;agent.j=1;
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
    
    double ww  = GetWindowWidth();
	double wh = GetWindowHeight();
	
	static char * menuListFile[] = {"File",
	"New | ",
	"Open | Ctrl-VK_F5",
	"Save | Ctrl-VK_F4",
	"Exit | Ctrl-VK_F12"};
	static char * menuListMazeEdit[] = {"Edit the map",
		"Regenerate | Ctrl-VK_F2",
		"Edit manually | Ctrl-VK_F3",
		"Clear and edit | Ctrl-VK_F1"};
	static char * menuListMazeSolve[] = {"Solve",
		"Manually",
		"Automatically"};
	static char * menuListHelp[] = {"Help",
		"How to play",
		"About"};
	static char * selectedLabel = NULL;
	
	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = wh;
	double h = fH * 1.5; // controler height
	double w = ww/4; // controler width
	double wlist = TextStringWidth(menuListMazeEdit[1])*1.2;
	double xindent = wh/20; 
	int    selection;
	bool   enable_rotation = 1;
	bool   show_more_buttons = 1;
	
	drawMenuBar(0,y-h,ww,h);
	//File
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection > 0 ) selectedLabel = menuListFile[selection];
	if( selection == 4 )
		exit(-1); // choose to exit
	else if( selection == 3 ) {
		SaveMap();
	}else if(selection == 2 ){
		LoadMap();
		Display();
	}else if(selection == 1 ){
		//new
	}
	//Edit the map
	selection = menuList(GenUIID(0), x+w,  y-h, w, wlist,h, menuListMazeEdit,sizeof(menuListMazeEdit)/sizeof(menuListMazeEdit[0]));
	if( selection > 0 ) selectedLabel = menuListMazeEdit[selection];
	if( selection == 3 ){
		if(lock_change == 1){
			ClearMaze();//To DO :the surrounding barriers
			Display();
			lock_change = 1-lock_change;
		}else{
			lock_change = 1-lock_change;
		}
	}
	else if( selection == 2 ){
		if(lock_change == 1){
			lock_change = 0;
		}else{
			lock_change = 1;
		}
	}else if( selection == 1 ){
		InitGame();
		Display();
		lock_change = 1;
	}
	//Solve
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListMazeSolve,sizeof(menuListMazeSolve)/sizeof(menuListMazeSolve[0]));
	if( selection > 0 ) selectedLabel = menuListMazeSolve[selection];
	if( selection == 2 ){
		//Automatically
		play = 0;
	}else if( selection == 1 ){
		play = 1;
	}
	//Help
	selection = menuList(GenUIID(0),x+3*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection > 0 ) selectedLabel = menuListHelp[selection];
	if( selection == 2 ){
		About();
	}else if( selection == 1 ){
		Guide();
	}

}
void Barrier() {//Draw the grids
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight() - 2;
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
    double windowHeight = GetWindowHeight() - 2;
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
void About(){
	double ww  = GetWindowWidth();
	double wh = GetWindowHeight();
	
	double cx = ww / 2;
	double cy = wh / 2;
	double len = ww / 1.5;
	
    MovePen(cx - len / 2, cy - len / 2 );
	SetPenColor("White");
    StartFilledRegion(1);
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);
    EndFilledRegion();
    
    MovePen(cx - len / 2, cy - len / 2 );
    SetPenColor("Black");
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);

    char *str = "ABOUT";
    //ABOUT\nThis is a maze game where players can both try to solve it by themselves or get some hints.\nAnd there're two ways to get a new maze,including generating by the program or by player.\ncreated by Xu Yang and Zheng Jiyun in 2023.\n";
	double fontAscent  = GetFontAscent();
	double tw = TextStringWidth(str);
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent);
	SetPenColor("Black");
	DrawTextString(str);
	
}
void Guide(){
	double ww  = GetWindowWidth();
	double wh = GetWindowHeight();
	
	double cx = ww / 2;
	double cy = wh / 2;
	double len = ww / 1.2;
	
    MovePen(cx - len / 2, cy - len / 2 );
	SetPenColor("White");
    StartFilledRegion(1);
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);
    EndFilledRegion();
    
    MovePen(cx - len / 2, cy - len / 2 );
    SetPenColor("Black");
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);

    char *str1 = "HOW TO PLAY";
    char *str2 = "  clear the map and biuld your own: F1 / Edit the map->Regenerate";
    char *str3 = "  Regenerate a map: F2 / Edit the map->Clear and edit";
    char *str4 = "  Edit the map: F3 / Edit the map->Edit manually";
    char *str5 = "HOW TO PLAY";
    char *str6 = "HOW TO PLAY";
    char *str7 = "HOW TO PLAY";
    char *str8 = "HOW TO PLAY";
    double fontAscent  = GetFontAscent();
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent);
	SetPenColor("Black");
	DrawTextString(str1);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 2);
	DrawTextString(str2);
	
  
}
void solve(int i, int j){
    visit[i][j]=1;
//    printf("(%d,%d)",i,j);
    if(i==X-2&&j==X-2&&count<69){
    	int k_i,k_j;
		for(k_i=0;k_i<X;k_i++){
			for(k_j=0;k_j<X;k_j++){
				_visit[count][k_i][k_j]=visit[k_i][k_j];		
			}

		}
		count++;
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
void visualize(int count){
//    int i,j;
//    for (i = 0; i < X; i++) {
//		for(j=0;j<X;j++ ){
//			if(_visit[count][i][j])
//			colorBlock(RED,i,j);
//		}
//    }
}
void KeyboardEventProcess(int key,int event){//Keyboard
    uiGetKeyboard(key, event);
    int i;
	switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_F1:
					if(lock_change == 1){
						ClearMaze();//To DO :the surrounding barriers
						Display();
						lock_change = 1-lock_change;
					}else{
						lock_change = 1-lock_change;
					}
					break;
				case VK_F2:
					InitGame();
					Display();
					lock_change = 1;
					break;
				case VK_F3:	//edit on the existing map
				    if(lock_change == 1){
						lock_change = 0;
					}else{
						lock_change = 1;
					}
					break;
				case VK_F4://save map
					SaveMap();
					break;
				case VK_F5://read map
					LoadMap();
					Display();
					break;
				case VK_F6:
					Guide();
					break;
				case VK_F12://exit
					exit(0);
					break;
				case VK_UP:
					if(play == 0)break;
					if(check(agent.i+1,agent.j)!=1)
					agent.i++;
					Display();
					break;
				case VK_DOWN:
					if(play == 0)break;
					if(check(agent.i-1,agent.j)!=1)
					agent.i--;
					Display();
					break;
				case VK_LEFT:
					if(play == 0)break;
					if(check(agent.i,agent.j-1)!=1)
					agent.j--;
					Display();
					break;
				case VK_RIGHT:
					if(play == 0)break;
					if(check(agent.i,agent.j+1)!=1)
					agent.j++;
					Display();
					break;
				case 'S':
					solve(1,1);
					visualize(0);
					break;
			}
			break;
		case KEY_UP:
			break;
	
	}
	Display();
}
void MouseEventProcess(int x, int y, int button, int event){
	uiGetMouse(x,y,button,event); 
//	if(lock_change == 1) return;
	double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;
	
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
		
		if(lock_change == 0 && curCoordinateI>=0 && curCoordinateJ>=0 && (blockState[curCoordinateI][curCoordinateJ] == VACANT||blockState[curCoordinateI][curCoordinateJ] == BARRIER)){
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
    SetWindowSize(X, X+2);
    InitGraphics();
    InitConsole();
    InitGame();
    registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
    Display();
    About();
}






