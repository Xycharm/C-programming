#include"macro_and_system.h"

int check(int i, int j) {
    //used while generating the maze,if
    if (i < 0 || i >= X || j < 0 || j >= X)return 0;
    if (blockState[i][j] == VACANT)return 0;
    if (blockState[i][j] == BARRIER)return 1;
    return -1;
}

int direction_feasible(int i, int j) {
    int k = 0;
    for (k = 0; k < 4; k++) {
        switch (k) {
            case 0:
                if (check(i, j + 2) != 0)return 0;
                break;
            case 1:
                if (check(i + 2, j) != 0)return 1;
                break;
            case 2:
                if (check(i, j - 2) != 0)return 2;
                break;
            case 3:
                if (check(i - 2, j) != 0)return 3;
                break;
        }
    }
    return -1;
    //return -1 if infeasible,otherwise  0up 1right 2down 3left(in array-coordinate)
}

int direction_judge(int i, int j, int dir) {
    //judge whether a direction is visible

    switch (dir) {
        case 0:
            if (check(i, j + 2) != 0)return 1;
            break;
        case 1:
            if (check(i + 2, j) != 0)return 1;
            break;
        case 2:
            if (check(i, j - 2) != 0)return 1;
            break;
        case 3:
            if (check(i - 2, j) != 0)return 1;
            break;
    }


    return -1;
    //return -1 /*reversed 0up 1right 2down 3left
}

void randomDFS(int i, int j) {
    //use random algorithm to generate a maze
    if (direction_feasible(i, j) == -1) return;
    int rand_way = rand() % 4;
    int k;
    for (k = 0; k < 4; k++) {
        if (direction_judge(i, j, (k + rand_way) % 4) == 1) {
            switch ((k + rand_way) % 4) {//traverse all feasible direction
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