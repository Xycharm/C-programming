#ifndef solution
#define solution
struct visits_node {
    int x;
    int y;
    struct visits_node* next;
};
extern struct visits_node* Head[99];
extern int count;
extern int soFar;
extern int visit[X][X];
extern int shown_count;
extern int lengths[X * X];

void callsolve(int I, int J);

void solve(int visit[X][X], int ci, int cj, int length);

void visualize();

void ClearMaze();

#endif // !solution

