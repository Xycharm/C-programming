#ifndef solution
#define solution
#define N_list 9
typedef struct visits_node {
    int i;
    int j;
    struct visits_node *next;
}Node;
extern Node* nodes[N_list];
extern struct visits_node *Head[N_list];
extern int count;
extern int soFar;
extern int visit[X][X];
extern int shown_count;
extern int lengths[X * X];

void callsolve(int I,int J);

void solve(int i,int j);

void visualize();

void ClearMaze();

void free_node();
int shortest_index();
void print_linkedlist();
void traverse_linkedlist(int _count);
#endif // !solution

