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

#include"Block.h"

int blockState[N]={1,0,0,1};;
//char *colors[]={"Red","Black","Light Gray"};

void colorBlock(int color,int coordinate);





void InitGame(){
	Randomize();//Randomize Initialization
	randMaze();
}

void Display(){
	DisplayClear();
	int i=0;
	Barrier();
	for(i=0;i<N;i++){
		colorBlock(blockState[i],i);		
	}

}

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
	}
//    SetPenColor(colors[coordinate]);
    StartFilledRegion(1);
    DrawLine(0, blockL);
    DrawLine(blockL, 0);
    DrawLine(0, -blockL);
    DrawLine(-blockL, 0);
    EndFilledRegion();

	
}
