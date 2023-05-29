#ifndef macro
#define macro
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
#define X 21
#define NVISIT 99
//must be odd
#define  VACANT  0
#define BARRIER  1
#define     RED  2
#define    DEST  3
#define   START  4
extern char* colors[];
extern int blockState[X][X];
void Barrier();
void colorBlock(int color, int x, int y);
#endif // !macro




