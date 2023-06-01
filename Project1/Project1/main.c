#include"macro_and_system.h"
#include"solution.h"

int blockState[X][X];//record the states of blocks
int visit[X][X];//record whether a block has been visited
Node *nodes[N_list] = {NULL};//store the linked list of nodes as paths that arrive at the destination
Node *path;//store the linked list of nodes as the path of exploration
int lengths[N_list];//store the lengths of paths
int count;//the number of paths
struct Agent agent = {1, 1};//the position of agent
int lock_change = 1;//whether being able to change the map
int play = 0;//whether the agent is able to move
char *colors[] = {"White", "Black", "Red", "Yellow", "Green"};//store the color strings


void InitGame() {
    //initialize the game, including the map and the agent
    //use randomDFS to generate a random map

    play = 0;
    srand((unsigned) time(NULL));
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < X; j++) {
            blockState[i][j] = BARRIER;
        }
    }
    blockState[1][1] = START;
    blockState[X - 2][X - 2] = DEST;
    //set the start and the destination
    randomDFS(1, 1);
    agent.i = 1;
    agent.j = 1;
}

void block_display() {
    //display the blocks


    DisplayClear();
    lock(lock_change);//show the lock icon
    int i = 0, j = 0;
    Barrier();
    for (i = 0; i < X; i++) {
        for (j = 0; j < X; j++) {
            colorBlock(blockState[i][j], i, j);
        }
    }

    colorBlock(RED, agent.i, agent.j);
}

void Display() {
    //redraw the menu bar and realize the function of the menu bar


    //menu list
    static char *menuListFile[] = {"File",
                                   "New",
                                   "Open | Ctrl-VK_F5",
                                   "Save | Ctrl-VK_F4",
                                   "Exit | Ctrl-VK_F12"};
    static char *menuListMazeEdit[] = {"Edit the map",
                                       "Edit manually | Ctrl-VK_F3",
                                       "Regenerate | Ctrl-VK_F2",
                                       "Clear and edit | Ctrl-VK_F1"};
    static char *menuListMazeSolve[] = {"Solve",
                                        "Manually",
                                        "Automatically | Ctrl-VK_F7",
                                        "Optimal | Ctrl-VK_F8",
                                        "Single Step | Ctrl-VK_F9",
                                        "Explore paths | Ctrl-VK_F10"};
    static char *menuListHelp[] = {"Help",
                                   "How to play",
                                   "About"};
    static char *selectedLabel = NULL;
    //menu size and position and other attributes
    double ww = GetWindowWidth();
    double wh = GetWindowHeight();
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
    //draw the menu bar
    drawMenuBar(0, y - h, ww, h);


    //File
    selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile,
                         sizeof(menuListFile) / sizeof(menuListFile[0]));
    if (selection > 0) selectedLabel = menuListFile[selection];//get the selected label
    if (selection == 4) {//exit
        free_node();
        free_path();
        exit(0); // choose to exit

    } else if (selection == 3) {//save
        SaveMap();
        Display();
    } else if (selection == 2) {//open
        LoadMap();
        block_display();
        Display();
    } else if (selection == 1) {//new
        ClearMaze();
        block_display();
        Display();
    }



    //Edit the map
    selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListMazeEdit,
                         sizeof(menuListMazeEdit) / sizeof(menuListMazeEdit[0]));
    if (selection > 0) selectedLabel = menuListMazeEdit[selection];//get the selected label
    if (selection == 3) {//clear and edit
        if (lock_change == 1) {//clear and edit
            agent.i = 1;
            agent.j = 1;
            play = 0;
            ClearMaze();
            block_display();
            lock_change = 0;
            lock(lock_change);
        } else {
            lock_change = 1;
            lock(lock_change);
        }
    } else if (selection == 1) {//by hand
        agent.i = 1;
        agent.j = 1;
        play = 0;
        if (lock_change == 1) {
            lock_change = 0;
            lock(lock_change);
        } else {
            lock_change = 1;
            lock(lock_change);
        }
    } else if (selection == 2) {//regenerate
        agent.i = 1;
        agent.j = 1;
        play = 0;
        InitGame();
        block_display();
        lock_change = 1;
    }



    //Solve
    selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListMazeSolve,
                         sizeof(menuListMazeSolve) / sizeof(menuListMazeSolve[0]));
    if (selection > 0) selectedLabel = menuListMazeSolve[selection];
    if (lock_change == 1) {
        if (selection == 2) {//auto
            callsolve(agent.i, agent.j);
            startTimer(0, 500);
            block_display();
            Display();
            play = 0;
        } else if (selection == 1) {//by hand
            play = 1;
        } else if (selection == 3) {//optimal
            callsolve(agent.i, agent.j);
            traverse_linkedlist(shortest_index());
        } else if (selection == 4) {//single step
            callsolve(agent.i, agent.j);
            if (nodes[shortest_index()]->next != NULL) {
                agent.i = nodes[shortest_index()]->next->i;
                agent.j = nodes[shortest_index()]->next->j;
            }//move to the next node on the shortest path
            block_display();
            Display();

        } else if (selection == 5) {//explore
            callsolve(agent.i, agent.j);
            path_();
        }


    }


    //Help
    selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp,
                         sizeof(menuListHelp) / sizeof(menuListHelp[0]));
    if (selection > 0) selectedLabel = menuListHelp[selection];
    if (selection == 2) {//about
        About();
    } else if (selection == 1) {// how to play
        Guide();
    }

}

void KeyboardEventProcess(int key, int event) {//Keyboard
    win_judge();
    uiGetKeyboard(key, event);
    int i;
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case VK_F1: //clear and edit
                    agent.i = 1;
                    agent.j = 1;
                    play = 0;
                    if (lock_change == 1) {
                        ClearMaze();
                        Display();
                        lock_change = 0;
                        lock(lock_change);
                    } else {
                        lock_change = 1;
                        lock(lock_change);
                    }
                    break;
                case VK_F2://regenerate
                    agent.i = 1;
                    agent.j = 1;
                    play = 0;
                    InitGame();
                    Display();
                    lock_change = 1;
                    break;
                case VK_F3:    //edit on the existing map
                    agent.i = 1;
                    agent.j = 1;
                    play = 0;
                    if (lock_change == 1) {
                        lock_change = 0;
                        lock(lock_change);
                    } else {
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
                case VK_F6://Guide
                    Guide();
                    break;
                case VK_F12://exit
                    free_node();
                    free_path();
                    exit(0);
                    break;
                case VK_UP://move up
                    if (play == 0)break;
                    if (check(agent.i + 1, agent.j) != 1)
                        agent.i++;
                    block_display();
                    Display();
                    break;
                case VK_DOWN://move down
                    if (play == 0)break;
                    if (check(agent.i - 1, agent.j) != 1)
                        agent.i--;
                    block_display();
                    Display();
                    break;
                case VK_LEFT://move left
                    if (play == 0)break;
                    if (check(agent.i, agent.j - 1) != 1)
                        agent.j--;
                    block_display();
                    Display();
                    break;
                case VK_RIGHT://move right
                    if (play == 0)break;
                    if (check(agent.i, agent.j + 1) != 1)
                        agent.j++;
                    block_display();
                    Display();
                    break;
                case VK_F7://auto
                    if (lock_change == 1) {
                        callsolve(agent.i, agent.j);
                        startTimer(0, 500);
                        block_display();
                        Display();
                    }

                    break;
                case VK_F8://optimal
                    if (lock_change == 1) {
                        callsolve(agent.i, agent.j);
                        traverse_linkedlist(shortest_index());
                    }

                    break;
                case VK_F9://single step
                    if (lock_change == 1) {
                        callsolve(agent.i, agent.j);
                        if (nodes[shortest_index()]->next != NULL) {
                            agent.i = nodes[shortest_index()]->next->i;
                            agent.j = nodes[shortest_index()]->next->j;
                        }
                    }

                    block_display();
                    Display();
                    break;
                case 'S'://explore
                    if (lock_change == 1) {
                        callsolve(agent.i, agent.j);
                        path_();
                        break;
                    }

            }
            break;
        case KEY_UP:
            break;

    }
    Display();
}

void TimerEventProcess(int timerID) {//Timer
    static int time = 0;
    if (timerID == 0) {//visualize all the paths
        block_display();
        traverse_linkedlist(time);
        Display();
        time++;
        if (time >= count) {
            cancelTimer(0);
            time = 0;
        }
    }
    if (timerID == -1) {//visualize  explore path
        block_display();
        if (path != NULL) {
            colorBlock(RED, path->i, path->j);
            path = path->next;
        } else {
            cancelTimer(-1);
        }

        printf("end\n");
        Display();

    }
}

void MouseEventProcess(int x, int y, int button, int event) {//Mouse
    win_judge();
    uiGetMouse(x, y, button, event);
    double windowWidth = GetWindowWidth();
    double windowHeight = GetWindowHeight();
    double blockL = windowWidth / X;
    //click the block
    if (button == LEFT_BUTTON && event == BUTTON_DOWN) {

        int i, j;
        int curCoordinateI = -1, curCoordinateJ = -1;
        double xx = ScaleXInches(x);
        double yy = ScaleYInches(y);
        for (i = 1; i < X - 1; i++) {
            for (j = 1; j < X - 1; j++) {
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
    }
    DisplayClear();
    block_display();
    Display();
}

void Main() {
    SetWindowTitle("Maze");
    SetWindowSize(X, X + 2);
    InitGraphics();
//    InitConsole();
    InitGame();
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    registerTimerEvent(TimerEventProcess);
    block_display();
    Display();
    lock(lock_change);

}





