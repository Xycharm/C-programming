#include"macro_and_system.h"
#include"solution.h"

#define N_list 999
//TODO: change into structure  ; outer surrounding unchangable: array use structure

int blockState[X][X];//record the states of blocks

int visit[X][X];

struct visits_node* Head[99] = { NULL };
int lengths[X * X];
int soFar, count;
int shown_count;
struct {
    int i;
    int j;
} agent = { 1, 1 };//the position of agent

int lock_change = 1;//whether being able to change the map
int play = 0;
char* colors[] = { "White", "Black", "Red", "Yellow", "Green" };//store the color strings


void InitGame() {
    play = 0;
    srand((unsigned)time(NULL));
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < X; j++) {
            blockState[i][j] = BARRIER;
        }
    }
    blockState[1][1] = START;
    blockState[X - 2][X - 2] = DEST;
    randomDFS(1, 1);
    agent.i = 1;
    agent.j = 1;
}

void Display() {//(re)display the changes
    DisplayClear();
    lock(lock_change);
    int i = 0, j = 0;
    Barrier();
    for (i = 0; i < X; i++) {
        for (j = 0; j < X; j++) {
            colorBlock(blockState[i][j], i, j);
        }
    }

    colorBlock(RED, agent.i, agent.j);

    double ww = GetWindowWidth();
    double wh = GetWindowHeight();

    static char* menuListFile[] = { "File",
                                   "New",
                                   "Open | Ctrl-VK_F5",
                                   "Save | Ctrl-VK_F4",
                                   "Exit | Ctrl-VK_F12" };
    static char* menuListMazeEdit[] = { "Edit the map",
                                       "Edit manually | Ctrl-VK_F3",
                                       "Regenerate | Ctrl-VK_F2",
                                       "Clear and edit | Ctrl-VK_F1" };
    static char* menuListMazeSolve[] = { "Solve",
                                        "Manually",
                                        "Automatically | Ctrl-VK_F7" };
    static char* menuListHelp[] = { "Help",
                                   "How to play",
                                   "About" };
    static char* selectedLabel = NULL;

    double fH = GetFontHeight();
    double x = 0; //fH/8;
    double y = wh;
    double h = fH * 1.5; // controler height
    double w = ww / 4; // controler width
    double wlist = TextStringWidth(menuListMazeEdit[1]) * 1.2;
    double xindent = wh / 20;
    int selection;
    bool enable_rotation = 1;
    bool show_more_buttons = 1;

    drawMenuBar(0, y - h, ww, h);
    //File
    selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile,
        sizeof(menuListFile) / sizeof(menuListFile[0]));
    if (selection > 0) selectedLabel = menuListFile[selection];
    if (selection == 4) {
        i = 1;
        while (Head[i]) {
            while (Head[i]) {
                struct visits_node* node;
                node = Head[i]->next;
                free(Head[i]);
                Head[i] = node;
            }
            i++;
        }
        exit(0); // choose to exit

    }
    else if (selection == 3) {
        SaveMap();
    }
    else if (selection == 2) {
        LoadMap();
        Display();
    }
    else if (selection == 1) {
        ClearMaze();
        Display();
    }
    //Edit the map
    selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListMazeEdit,
        sizeof(menuListMazeEdit) / sizeof(menuListMazeEdit[0]));
    if (selection > 0) selectedLabel = menuListMazeEdit[selection];
    if (selection == 3) {
        if (lock_change == 1) {
            ClearMaze();//To DO :the surrounding barriers
            Display();
            lock_change = 0;
            lock(lock_change);
        }
        else {
            lock_change = 1;
            lock(lock_change);
            callsolve(agent.i, agent.j);
        }
    }
    else if (selection == 1) {//by hand
        if (lock_change == 1) {
            lock_change = 0;
            lock(lock_change);
        }
        else {
            lock_change = 1;
            lock(lock_change);
            callsolve(agent.i, agent.j);
        }
    }
    else if (selection == 2) {
        InitGame();
        Display();
        callsolve(agent.i, agent.j);
        lock_change = 1;
    }
    //Solve
    selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListMazeSolve,
        sizeof(menuListMazeSolve) / sizeof(menuListMazeSolve[0]));
    if (selection > 0) selectedLabel = menuListMazeSolve[selection];
    if (selection == 2) {
        callsolve(agent.i, agent.j);
        visualize();
        play = 0;
    }
    else if (selection == 1) {
        play = 1;
    }
    //Help
    selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp,
        sizeof(menuListHelp) / sizeof(menuListHelp[0]));
    if (selection > 0) selectedLabel = menuListHelp[selection];
    if (selection == 2) {
        About();
    }
    else if (selection == 1) {
        Guide();
    }

}

void KeyboardEventProcess(int key, int event) {//Keyboard
    uiGetKeyboard(key, event);
    int i;
    switch (event) {
    case KEY_DOWN:
        switch (key) {
        case VK_F1:
            if (lock_change == 1) {
                ClearMaze();//To DO :the surrounding barriers
                Display();
                lock_change = 0;
                lock(lock_change);
            }
            else {
                lock_change = 1;
                lock(lock_change);
                callsolve(agent.i, agent.j);
            }
            break;
        case VK_F2:
            InitGame();
            Display();
            callsolve(agent.i, agent.j);
            lock_change = 1;
            break;
        case VK_F3:    //edit on the existing map
            if (lock_change == 1) {
                lock_change = 0;
                lock(lock_change);
            }
            else {
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
            while (Head[i]) {
                while (Head[i]) {
                    struct visits_node* node;
                    node = Head[i]->next;
                    free(Head[i]);
                    Head[i] = node;
                }
                i++;
            }
            exit(0);
            break;
        case VK_UP:
            if (play == 0)break;
            if (check(agent.i + 1, agent.j) != 1)
                agent.i++;
            Display();
            break;
        case VK_DOWN:
            if (play == 0)break;
            if (check(agent.i - 1, agent.j) != 1)
                agent.i--;
            Display();
            break;
        case VK_LEFT:
            if (play == 0)break;
            if (check(agent.i, agent.j - 1) != 1)
                agent.j--;
            Display();
            break;
        case VK_RIGHT:
            if (play == 0)break;
            if (check(agent.i, agent.j + 1) != 1)
                agent.j++;
            Display();
            break;
        case VK_F7:
            callsolve(agent.i, agent.j);
            visualize();
            break;

        }
        break;
    case KEY_UP:
        break;

    }
    Display();
}

void MouseEventProcess(int x, int y, int button, int event) {
    uiGetMouse(x, y, button, event);
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;

    if (button == LEFT_BUTTON && event == BUTTON_DOWN) {

        int i, j;
        int curCoordinateI = -1, curCoordinateJ = -1;
        double xx = ScaleXInches(x);
        double yy = ScaleYInches(y);
        for (i = 0; i < X; i++) {
            for (j = 0; j < X; j++) {
                double pi = i * blockL;
                double pj = j * blockL;
                if (xx > pj && xx < pj + blockL && yy > pi && yy < pi + blockL) {
                    curCoordinateI = i;
                    curCoordinateJ = j;
                    break;
                }
            }
        }

        if (lock_change == 0 && curCoordinateI >= 0 && curCoordinateJ >= 0 &&
            (blockState[curCoordinateI][curCoordinateJ] == VACANT ||
                blockState[curCoordinateI][curCoordinateJ] == BARRIER)) {
            blockState[curCoordinateI][curCoordinateJ] = 1 - blockState[curCoordinateI][curCoordinateJ];
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
    SetWindowSize(X, X + 2);
    InitGraphics();
    InitConsole();
    InitGame();
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    Display();
    lock(lock_change);

}





