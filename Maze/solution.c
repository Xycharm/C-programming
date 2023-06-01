#include"macro_and_system.h"
#include"solution.h"


Node* add_node(Node* head, int i, int j) {
    //add at tail,discuss whether head is null
    Node* p = (Node*)malloc(sizeof(Node));
    p->i = i;
    p->j = j;
    p->next = NULL;
    if (head == NULL) {
        head = p;
        return head;
    }
    Node* q = head;
    while (q->next != NULL) {
        q = q->next;
    }
    q->next = p;
    return head;
}

void print_linkedlist() {
    int i;
    for (i = 0; i < count; i++) {
        Node* p = nodes[i];
        while (p != NULL) {
            printf("(%d,%d)", p->i, p->j);
            p = p->next;
        }
        printf("length=%d\n",lengths[i]);
    }
}
void traverse_linkedlist(int _count) {


        Node* p = nodes[_count];
        while (p != NULL) {
            colorBlock(RED,p->i, p->j);
            p = p->next;
        }
        printf("end%d\n",_count);

}
Node* delete_node(Node* head, int i, int j) {
    //delete the last node
    if (head == NULL) {
        return NULL;
    }
    Node* p = head;
    Node* q = NULL;
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
Node* copy_linkedlist(Node* source, Node* target) {
    //copy source to target
    if (source == NULL) {
        return NULL;
    }
    Node* p = source;
    while (p != NULL) {
        target = add_node(target, p->i, p->j);
        p = p->next;
    }
    return target;
}
//void solve(int i, int j) {
//    visit[i][j] = 1;
//    nodes[count]=add_node(nodes[count], i, j);
//    if (i == X - 2 && j == X - 2 && count < N_list) {
//
//        count++;
//        nodes[count] = copy_linkedlist(nodes[count - 1], nodes[count]);
//    }
//    int di[] = { 0,0,1,-1 };
//    int dj[] = { 1,-1,0,0 };
//    int k;
//    for (k = 0; k < 4; k++) {
//        int _i = i + di[k];
//        int _j = j + dj[k];
//        if ((blockState[_i][_j] == VACANT || blockState[_i][_j] == DEST) && visit[_i][_j] == 0) {
//            solve(_i, _j);
//        }
//    }
//    visit[i][j] = 0;
//    nodes[count] = delete_node(nodes[count], i, j);
//
//}
void free_node(){
    int i = 0;
    //free all linked list node[]
    for (i = 0; i < count; i++) {
        Node* p = nodes[i];
        while (p != NULL) {
            Node* q = p;
            p = p->next;
            free(q);
        }
        nodes[i] = NULL;
    }
}
int shortest_index(){
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
void callsolve(int I,int J) {
    free_node();
    count = 0;
    solve(I, J);
    print_linkedlist();
    printf("%d", count);
}
void linklist_length(Node* head){
int i = 0;
    Node* p = head;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    lengths[count] = i;

}
void solve(int i, int j) {
    visit[i][j] = 1;
    nodes[count]=add_node(nodes[count], i, j);
    if (i == X - 2 && j == X - 2 && count < N_list) {
        linklist_length(nodes[count]);
        count++;
        nodes[count] = copy_linkedlist(nodes[count - 1], nodes[count]);
    }
    int di[] = { 0,0,1,-1 };
    int dj[] = { 1,-1,0,0 };
    int k;
    for (k = 0; k < 4; k++) {
        int _i = i + di[k];
        int _j = j + dj[k];
        if ((blockState[_i][_j] == VACANT || blockState[_i][_j] == DEST) && visit[_i][_j] == 0) {
            solve(_i, _j);
        }
    }
    visit[i][j] = 0;
    nodes[count] = delete_node(nodes[count], i, j);

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

        char *str = "No valid path!";
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
    struct visits_node *p = NULL;
    p = Head[shown_count];
    for (j = 0; j < soFar; j++) {
        printf("%d,%d->", p->i, p->j);
        colorBlock(RED, p->i, p->j);
        p = p->next;
    }
    printf("\n");
    shown_count++;
}
