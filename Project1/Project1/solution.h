#ifndef solution
#define solution
#define N_list 999 //capacity of nodes[]
#define EPOCH   99
#define DECAY  0.8

extern double epsilon;
extern double alpha;
extern double gamma;
typedef struct visits_node {
    int i;
    int j;
    struct visits_node *next;
} Node;//linked list node
extern Node *nodes[N_list];
extern struct visits_node *Head[N_list];
extern int count;
extern int soFar;
extern int visit[X][X];
extern int shown_count;
extern int lengths[N_list];
extern int play;
extern int lock_change;
extern Node *path;
extern Node *reinforce;
extern void (*agent_move[4])();
extern double Q[X][X][4];
extern int rein_visit[X][X];

int EpsilonGreedy(int i,int j,double epsilon);
double reward(int i,int j,int action);
double maxQ(int i,int j);
void callsolve(int I, int J);
void Q_Intialization();
void solve(int i, int j);
void free_path();
void path_();

void ClearMaze();

void win_judge();

void free_node();

int shortest_index();

void print_linkedlist();

void traverse_linkedlist(int _count);

void Q_learning();
int Greedy(int i,int j);
#endif // !solution

