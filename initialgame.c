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
#define X 5
//must be odd
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4
//TODO: change into structure  ; outer surrounding unchangable: array use structure
void callsolve();
void solve(int visit[X][X], int ci, int cj, int length);
void visualize();

int blockState[X][X];//record the states of blocks

int visit[X][X];
struct visits_node{
	int x;
	int y;
	struct visits_node *next;
};
struct visits_node *Head[99] = {NULL};
int _blockState[X][X];//backup of 'blockState'
int lengths[X*X];
int soFar, count;
int shown_count;
struct{
    int i;
	int j;
	}agent = {1,1};//the position of agent
	
int lock_change = 1;//whether being able to change the map
int play = 0;
char *colors[]={"White","Black","Red","Yellow","Green"};//store the color strings
void lock(int lock_change){
	double ww  = GetWindowWidth();
   	double wh = GetWindowHeight();
   	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = wh;
	double h = fH * 1.5; // controler height
	double w = ww/4; // controler width
    char *str1 = "locked";
    char *str2 = "unlocked";
    double fontAscent  = GetFontAscent();
    double tw = TextStringWidth(str2);
    double len = tw + 1; 
	
    if(lock_change){
    	MovePen(x, y - h * 3);
        SetPenColor("Blue");
        StartFilledRegion(1);
        DrawLine(0, h);
        DrawLine(len , 0);
        DrawLine(0, -h);
        DrawLine(-len, 0);
        EndFilledRegion();
        
        MovePen(len / 2 - tw / 2, y - h * 2.5 - fontAscent / 2);
	    SetPenColor("Black");
        DrawTextString(str1);
        
	}else{
		MovePen(x, y - h * 3);
        SetPenColor("Blue");
        StartFilledRegion(1);
        DrawLine(0, h);
        DrawLine(len , 0);
        DrawLine(0, -h);
        DrawLine(-len, 0);
        EndFilledRegion();
        
        MovePen(len / 2 - tw / 2, y - h * 2.5 - fontAscent / 2);
	    SetPenColor("Black");
        DrawTextString(str2);
	}
    
}
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
	//judge whether a direction is visible 

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
	//use random algorithm to generate a maze
    if (direction_feasible(i,j)==-1) return;
    int rand_way=rand()%4;
    int k;
	for(k=0;k<4;k++) {
        if(direction_judge(i,j,(k+rand_way)%4)==1){
            switch ((k+rand_way)%4) {//traverse all feasible direction
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
	//boundary_filling
		for(i=0;i<X;i++){
		blockState[i][0]=BARRIER;
		blockState[i][X-1]=BARRIER;
		blockState[0][i]=BARRIER;
		blockState[X-1][i]=BARRIER;
		}
			

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
	callsolve();
	printf("\n");
}
void Display() {//(re)display the changes
    DisplayClear();
    lock(lock_change);
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
	"New",
	"Open | Ctrl-VK_F5",
	"Save | Ctrl-VK_F4",
	"Exit | Ctrl-VK_F12"};
	static char * menuListMazeEdit[] = {"Edit the map",
	    "Edit manually | Ctrl-VK_F3",
		"Regenerate | Ctrl-VK_F2",
		"Clear and edit | Ctrl-VK_F1"};
	static char * menuListMazeSolve[] = {"Solve",
		"Manually",
		"Automatically | Ctrl-VK_F7"};
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
		ClearMaze();
		Display();
	}
	//Edit the map
	selection = menuList(GenUIID(0), x+w,  y-h, w, wlist,h, menuListMazeEdit,sizeof(menuListMazeEdit)/sizeof(menuListMazeEdit[0]));
	if( selection > 0 ) selectedLabel = menuListMazeEdit[selection];
	if( selection == 3 ){
		if(lock_change == 1){
			ClearMaze();//To DO :the surrounding barriers
			Display();
			lock_change = 0;
			lock(lock_change);
		}else{
			lock_change = 1;
			lock(lock_change);
			callsolve();
		}
	}
	else if( selection == 1 ){//by hand
		if(lock_change == 1){
			lock_change = 0;
			lock(lock_change);
		}else{
			lock_change = 1;
			lock(lock_change);
		    callsolve();
		}
	}else if( selection == 2 ){
		InitGame();
		Display();
		callsolve();
		lock_change = 1;
	}
	//Solve
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListMazeSolve,sizeof(menuListMazeSolve)/sizeof(menuListMazeSolve[0]));
	if( selection > 0 ) selectedLabel = menuListMazeSolve[selection];
	if( selection == 2 ){
		visualize();
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

    char *str1 = "ABOUT";
    char *str2 = "  This is a maze game where players can both try to solve";
    char *str3 = "it by themselves or get some hints.And there're two ways ";
    char *str4 = "to get a new maze,including generating by the program or ";
    char *str5 = "by player.";
    char *str6 = "";
    char *str7 = "";
    char *str8 = "created by Xu Yang and Zheng Jiyun in 2023.";
    
    //ABOUT\n.\n generating by the program or by player.\ncreated by Xu Yang and Zheng Jiyun in 2023.\n";
	 double fontAscent  = GetFontAscent();
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent);
	SetPenColor("Black");
	DrawTextString(str1);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 2.5);
	DrawTextString(str2);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 4);
	DrawTextString(str3);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 5.5);
	DrawTextString(str4);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 7);
	DrawTextString(str5);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 8.5);
	DrawTextString(str6);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 10);
	DrawTextString(str7);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 11.5);
	DrawTextString(str8);
	
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
    char *str8 = "  (touch F3/Edit manually again to lock the map)";
    char *str5 = "  Start to play: Solve->Manually";
    char *str6 = "  (use up/down/left/right on the keyboard to advance)";
    char *str7 = "  Show the path: Solve->Automatically";
    
    double fontAscent  = GetFontAscent();
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent);
	SetPenColor("Black");
	DrawTextString(str1);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 2.5);
	DrawTextString(str2);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 4);
	DrawTextString(str3);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 5.5);
	DrawTextString(str4);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 7);
	DrawTextString(str8);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 8.5);
	DrawTextString(str5);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 10);
	DrawTextString(str6);
	
	MovePen(cx - len / 2 + 0.5, cy + len / 2  - fontAscent * 11.5);
	DrawTextString(str7);
  
}
void callsolve(){
	int i = 1;
	while(Head[i]){
		while(Head[i]){
		    struct visits_node *node;
		    node = Head[i]->next;
		    free(Head[i]);
		    Head[i] = node;
		}
		i++;
	}
	int j;
	for(i = 0;i < X;i++){
			for(j = 0;j < X;j++){
				visit[i][j] = blockState[i][j];
		}
    }
    soFar = 99999999;
    count = 0;
    solve(visit, 1, 1, 0);
    shown_count = 1;
    
}
void solve(int visit[X][X], int ci, int cj, int length){
	if(length > soFar) return;
	
	struct visits_node *p = NULL, *tail = NULL;
	int di[4] = {1, 0, -1, 0};
    int dj[4] = {0, 1, 0, -1};
    int _i, _j, k;		
    if(ci==X-2 && cj==X-2 && soFar >= length){
        count++;
    	printf("%d\n",count);
    	int k_i,k_j;
		for(k_i = 1;k_i < X-1;k_i++){
			for(k_j = 1;k_j < X-1;k_j++){
				if(visit[k_i][k_j] == RED){
					if(count >= 99) break;
					if((p = (struct visits_node *)malloc(sizeof(struct visits_node))) == NULL ){
    		            printf("Failed.\n");
    		         	
	            	}
					p->x = k_i;
					p->y = k_j;
					p->next = NULL;
					if(Head[count] == NULL){
						Head[count] = p;	
					}else{
						tail->next = p;
					}
					tail = p;
					//printf("%d,%d->",k_i,k_j);
					printf("%d,%d->",tail->x,tail->y);
				}			
			}
		}
		printf("\n");
		lengths[count] = length;
		soFar = (length < soFar ? length : soFar);
		return;
	}else{
        for(k = 0;k < 4;k++){
            _i = ci + di[k];
            _j = cj + dj[k];
            if((visit[_i][_j] == VACANT || visit[_i][_j] == DEST)){
               visit[_i][_j] = RED;
			   solve(visit, _i, _j, length + 1);
			   visit[_i][_j] = VACANT;
            }
        }
	}

}
void visualize(){
	if(count == 0){
		double ww  = GetWindowWidth();
    	double wh = GetWindowHeight();
	
	    double cx = ww / 2;
	    double cy = wh / 2;
	    double len = ww / 1.6;
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
        
        char *str = "No valid path!";
        double fontAscent  = GetFontAscent();
	    double tw = TextStringWidth(str);
    	MovePen(cx - tw / 2, cy - fontAscent / 2);
	    SetPenColor("Black");
    	DrawTextString(str);
    	
    	return;
	}
    Display();
    if(shown_count > count){
	    shown_count = 1; 
	}
	while(shown_count <= count && lengths[shown_count] > soFar)
	    shown_count++;
	printf("%d/%d\n", shown_count, count);
	int j;
	struct visits_node *p = NULL;
	p = Head[shown_count];
	for(j = 0;j < soFar;j++){
	    printf("%d,%d->",p->x, p->y);
		colorBlock(RED, p->x, p->y);
		p = p->next;
	}
	printf("\n");
	shown_count++;
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
						lock_change = 0;
						lock(lock_change);
					}else{
						lock_change = 1;
						lock(lock_change);
						callsolve();
					}
					break;
				case VK_F2:
					InitGame();
					Display();
					callsolve();
					lock_change = 1;
					break;
				case VK_F3:	//edit on the existing map
				    if(lock_change == 1){
						lock_change = 0;
						lock(lock_change);
					}else{
						lock_change = 1;
						lock(lock_change);
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
                    i = 1;
	                while(Head[i]){
	                	while(Head[i]){
		                    struct visits_node *node;
		                    node = Head[i]->next;
		                    free(Head[i]);
		                    Head[i] = node;
		                }
	                	i++;
                	}
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
				case VK_F7:
					visualize();
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
    lock(lock_change);
    
}






