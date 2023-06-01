#include"macro_and_system.h"

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

void colorBlock(int color, int x, int y) { //Draw the color blocks
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

void ClearMaze() {
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < X; j++) {
            blockState[i][j] = VACANT;
        }
    }
    blockState[1][1] = START;
    blockState[X - 2][X - 2] = DEST;
    //boundary_filling
    for (i = 0; i < X; i++) {
        blockState[i][0] = BARRIER;
        blockState[i][X - 1] = BARRIER;
        blockState[0][i] = BARRIER;
        blockState[X - 1][i] = BARRIER;
    }


}

void lock(int lock_change) {
    double ww = GetWindowWidth();
    double wh = GetWindowHeight();
    double fH = GetFontHeight();
    double x = 0; //fH/8;
    double y = wh;
    double h = fH * 1.5; // controler height
    double w = ww / 4; // controler width
    char* str1 = "locked";
    char* str2 = "unlocked";
    double fontAscent = GetFontAscent();
    double tw = TextStringWidth(str2);
    double len = tw + 1;

    if (lock_change) {
        MovePen(x, y - h * 2);
        SetPenColor("Blue");
        StartFilledRegion(1);
        DrawLine(0, h);
        DrawLine(len, 0);
        DrawLine(0, -h);
        DrawLine(-len, 0);
        EndFilledRegion();

        MovePen(len / 2 - tw / 2, y - h * 2.5 - fontAscent / 2);
        SetPenColor("Black");
        DrawTextString(str1);

    }
    else {
        MovePen(x, y - h * 2);
        SetPenColor("Blue");
        StartFilledRegion(1);
        DrawLine(0, h);
        DrawLine(len, 0);
        DrawLine(0, -h);
        DrawLine(-len, 0);
        EndFilledRegion();

        MovePen(len / 2 - tw / 2, y - h * 2.5 - fontAscent / 2);
        SetPenColor("Black");
        DrawTextString(str2);
    }

}