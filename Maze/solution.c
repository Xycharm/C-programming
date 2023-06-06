#include"macro_and_system.h"
#include"solution.h"


Node *add_node(Node *head, int i, int j)
{
    //add at tail,discuss whether head is null
    Node *p = (Node *) malloc(sizeof(Node));
    p->i = i;
    p->j = j;
    p->next = NULL;
    if (head == NULL) {
        head = p;
        return head;
    }
    Node *q = head;
    while (q->next != NULL) {
        q = q->next;
    }
    q->next = p;
    return head;
}

void win_judge()
{
    //judge whether the agent wins
    if(biplayer==1){
        if(agent.i==X-2&&agent.j==X-2){
            biplayer=0;
            subtitle("red win!win!win!!!\nnew game will be started");
            agent.i=1;
            agent.j=1;
            another_agent.i=1;
            another_agent.j=1;
            biplayer=1;
            play=1;
            InitGame();
            Display();
            lock_change=1;
        } else if(another_agent.i==X-2&&another_agent.j==X-2){
            play=0;
            subtitle("blue win!win!win!!!\nnew game will be started");
            agent.i=1;
            agent.j=1;
            another_agent.i=1;
            another_agent.j=1;
            play=1;
            InitGame();
            Display();
            lock_change=1;
        }

    }else{
        if (agent.i == X - 2 && agent.j == X - 2) {
            subtitle("win!win!win!!!\nnew game will be started");
            agent.i = 1;
            agent.j = 1;
            play = 0;
            InitGame();
            Display();
            lock_change = 1;
        }
    }

}

void print_linkedlist()
{
    //print all linked list nodes
    int i;
    for (i = 0; i < count; i++) {
        Node *p = nodes[i];
        while (p != NULL) {
            printf("(%d,%d)", p->i, p->j);
            p = p->next;
        }
        printf("length=%d\n", lengths[i]);
    }
}

void path_()
{
    //print path
    Node *p = path;
    while (p != NULL) {
        printf("(%d,%d)", p->i, p->j);
        p = p->next;
    }
    printf("\ntry and error\n");
    startTimer(-1, 100);
}


void traverse_linkedlist(int _count)
{
    //traverse the linked list nodes and color them
    if (count == 0) {
        subtitle("no solution");

        return;
    }

    Node *p = nodes[_count];
    while (p != NULL) {
        colorBlock(RED, p->i, p->j);
        p = p->next;
    }
    printf("end%d\n", _count);

}

Node *delete_node(Node *head, int i, int j)
{
    //delete the last node
    if (head == NULL) {
        return NULL;
    }
    Node *p = head;
    Node *q = NULL;
    while (p->next != NULL) {
        q = p;
        p = p->next;
    }
    if (q == NULL) {
        head = NULL;
        return head;
    }
    q->next = NULL;
    return head;
}

Node *copy_linkedlist(Node *source, Node *target)
{
    //copy source to target
    if (source == NULL) {
        return NULL;
    }
    Node *p = source;
    while (p != NULL) {
        target = add_node(target, p->i, p->j);
        p = p->next;
    }
    return target;
}

void free_node()
{
    //free all linked list node[]
    int i = 0;
    for (i = 0; i < count; i++) {
        Node *p = nodes[i];
        while (p != NULL) {
            Node *q = p;
            p = p->next;
            free(q);
        }
        nodes[i] = NULL;
    }
}

void free_path()
{
    //free path
    Node *p = path;
    while (p != NULL) {
        Node *q = p;
        p = p->next;
        free(q);
    }
    path = NULL;
}

int shortest_index()
{
    //find the shortest path
    int i = 0;
    int min = lengths[0];
    int index = 0;
    for (i = 0; i < count; i++) {
        if (lengths[i] < min) {
            min = lengths[i];
            index = i;
        }
    }
    return index;
}

void callsolve(int I, int J)
{
    //call solve
    free_node();
    free_path();
    count = 0;
    solve(I, J);
    print_linkedlist();
    printf("%d", count);
}

void linklist_length(Node *head)
{
    //calculate the length of linked list
    int i = 0;
    Node *p = head;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    lengths[count] = i;

}


void solve(int i, int j)
{
    if (count>=N_list){
        return;
    }
    //solve the maze with recursion
    path = add_node(path, i, j);
    visit[i][j] = 1;
    nodes[count] = add_node(nodes[count], i, j);
    if (i == X - 2 && j == X - 2 && count < N_list) {
        linklist_length(nodes[count]);
        count++;
        if (count>=N_list){
            visit[i][j] = 0;
            return;
        }
        nodes[count] = copy_linkedlist(nodes[count - 1], nodes[count]);
    }
    int di[] = {0, 0, 1, -1};
    int dj[] = {1, -1, 0, 0};
    int k;
    for (k = 0; k < 4; k++) {
        int _i = i + di[k];
        int _j = j + dj[k];
        if ((blockState[_i][_j] == VACANT || blockState[_i][_j] == DEST) && visit[_i][_j] == 0) {
            solve(_i, _j);
            if (count>=N_list){
                visit[i][j] = 0;
                return;
            }
        }
    }
    visit[i][j] = 0;
    nodes[count] = delete_node(nodes[count], i, j);

}

void agent_up(){
    if (check(agent.i + 1, agent.j) != 1)
        agent.i++;
    block_display();
    Display();
}
void agent_down(){
    if (check(agent.i - 1, agent.j) != 1)
        agent.i--;
    block_display();
    Display();
}
void agent_left(){
    if (check(agent.i, agent.j - 1) != 1)
        agent.j--;
    block_display();
    Display();
}
void agent_right(){
    if (check(agent.i, agent.j + 1) != 1)
        agent.j++;
    block_display();
    Display();
}
//create a functional pointer
void (*agent_move[4])() = {agent_up, agent_down, agent_left, agent_right};
//0 up 1 down 2 left 3 right
double Q[X][X][4];
double epsilon=0.1;
double alpha=0.1;
double gamma=0.9;
int Greedy(int i,int j){
    int max=0;
    for (int k=0;k<4;k++){
        if (Q[i][j][k]>Q[i][j][max]){
            max=k;
        }
    }
    return max;
}
int EpsilonGreedy(int i,int j,double epsilon){
    //randomize a number
    double r=((double)(rand()%10000))/10000;
//    printf("%lf,%lf",r,epsilon);
    if (r<epsilon/3){

//        printf("random");
        return rand()%2+1;

    }
    else if(r<2*epsilon/3){
        return 3;

    } else if(r<epsilon){
        return 0;
    }
    else{
        int max=0;
        for (int k=0;k<4;k++){
            if (Q[i][j][k]>Q[i][j][max]){
                max=k;
            }
        }
//        printf("max",max);
        return max;
    }

}
void Q_Intialization(){
    for (int i=0;i<X;i++){
        for (int j=0;j<X;j++){
            for (int k=0;k<4;k++){
                Q[i][j][k]=100*(sqrt(2)-sqrt((X-2-i)*(X-2-i)+(X-2-j)*(X-2-j))/(X*X));
            }
        }
    }
};
double reward(int i,int j,int action){
    int di[4]={1,-1,0,0};
    int dj[4]={0,0,-1,1};
    int state=blockState[i+di[action]][j+dj[action]];
    double activation=sqrt((X-2-i)*(X-2-i)+(X-2-j)*(X-2-j))/(X*X);
    if(rein_visit[i+di[action]][j+dj[action]]>=1)return -1000;
//    printf("%d",action);
    if(state==DEST){
//        printf("DEST");
        return 10000000;
    }
    else if(state==VACANT){
//        printf("VACANT");
        return -10;
    }
    else if(state==BARRIER){
//        printf("BARRIER");
        return -10000;
    }
    else{
//        printf("ERROR");
        return -1;
    }
}

double maxQ(int i,int j){
    int max=0;
    for (int k=0;k<4;k++){
        if (Q[i][j][k]>Q[i][j][max]){
            max=k;
        }
    }
    return Q[i][j][max];
}

void Q_learning(){
//        Q_Intialization();
        startTimer(-2,1);


}
