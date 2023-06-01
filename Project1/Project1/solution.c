#include"macro_and_system.h"
#include"solution.h"

void callsolve(int I, int J) {
    int i = 1;
    while (Head[i]) {
        while (Head[i]) {
            struct visits_node* node;
            node = Head[i]->next;
            free(Head[i]);
            Head[i] = node;
        }
        i++;
    }
    int j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < X; j++) {
            visit[i][j] = blockState[i][j];
        }
    }
    soFar = 99999999;
    count = 0;
    solve(visit, I, J, 0);
    shown_count = 1;

}

void solve(int visit[X][X], int ci, int cj, int length) {
    if (length > soFar) return;

    struct visits_node* p = NULL, * tail = NULL;
    int di[4] = { 1, 0, -1, 0 };
    int dj[4] = { 0, 1, 0, -1 };
    int _i, _j, k;
    if (ci == X - 2 && cj == X - 2 && soFar >= length) {
        count++;
        printf("%d\n", count);
        int k_i, k_j;
        for (k_i = 1; k_i < X - 1; k_i++) {
            for (k_j = 1; k_j < X - 1; k_j++) {
                if (visit[k_i][k_j] == RED) {
                    if (count >= 99) break;
                    if ((p = (struct visits_node*)malloc(sizeof(struct visits_node))) == NULL) {
                        printf("Failed.\n");

                    }
                    p->x = k_i;
                    p->y = k_j;
                    p->next = NULL;
                    if (Head[count] == NULL) {
                        Head[count] = p;
                    }
                    else {
                        tail->next = p;
                    }
                    tail = p;
                    //printf("%d,%d->",k_i,k_j);
                    printf("%d,%d->", tail->x, tail->y);
                }
            }
        }
        printf("\n");
        lengths[count] = length;
        soFar = (length < soFar ? length : soFar);
        return;
    }
    else {
        for (k = 0; k < 4; k++) {
            _i = ci + di[k];
            _j = cj + dj[k];
            if ((visit[_i][_j] == VACANT || visit[_i][_j] == DEST)) {
                visit[_i][_j] = RED;
                solve(visit, _i, _j, length + 1);
                visit[_i][_j] = VACANT;
            }
        }
    }

}

void visualize() {
    if (count == 0) {
        double ww = GetWindowWidth();
        double wh = GetWindowHeight();

        double cx = ww / 2;
        double cy = wh / 2;
        double len = ww / 1.6;
        MovePen(cx - len / 2, cy - len / 2);
        SetPenColor("White");
        StartFilledRegion(1);
        DrawLine(0, len);
        DrawLine(len, 0);
        DrawLine(0, -len);
        DrawLine(-len, 0);
        EndFilledRegion();

        MovePen(cx - len / 2, cy - len / 2);
        SetPenColor("Black");
        DrawLine(0, len);
        DrawLine(len, 0);
        DrawLine(0, -len);
        DrawLine(-len, 0);

        char* str = "No valid path!";
        double fontAscent = GetFontAscent();
        double tw = TextStringWidth(str);
        MovePen(cx - tw / 2, cy - fontAscent / 2);
        SetPenColor("Black");
        DrawTextString(str);

        return;
    }
    Display();
    if (shown_count > count) {
        shown_count = 1;
    }
    while (shown_count <= count && lengths[shown_count] > soFar)
        shown_count++;
    printf("%d/%d\n", shown_count, count);
    int j;
    struct visits_node* p = NULL;
    p = Head[shown_count];
    for (j = 0; j < soFar; j++) {
        printf("%d,%d->", p->x, p->y);
        colorBlock(RED, p->x, p->y);
        p = p->next;
    }
    printf("\n");
    shown_count++;
}
