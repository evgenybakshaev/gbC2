#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int **init2dIntArray(int **array, const int row, const int col){
    array = (int **)calloc(sizeof(int *), row);
    for(int i = 0; i < row; ++i){
        *(array + i) = (int *)calloc(sizeof(int), col);
    }
    return array;
}

typedef struct OneLinkNode {
    int dat;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct OneLinkList {
    OneLinkNode *head;
    unsigned int size;
} OneLinkList;

void initOneLinkList(OneLinkList *lst) {
    lst->head = NULL;
    lst->size = 0;
}

bool pushOneLinkStack(OneLinkList *stack, int value){
    OneLinkNode *tmp = (OneLinkNode *)malloc(sizeof (OneLinkNode));
    if(tmp == NULL){
        return false;
    }

    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;

    return 0;
}

int popOneLinkStack(OneLinkList *stack) {
    if(stack->size == 0) {
        return -1;
    }

    OneLinkNode *tmp = stack->head;
    int out = tmp->dat;
    stack->head = tmp->next;
    stack->size--;
    free(tmp);
    return out;
}

typedef struct TwoLinkNode {
    int dat;
    struct TwoLinkNode *next;
    struct TwoLinkNode *prev;
} TwoLinkNode;

typedef struct TwoLinkList {
    struct TwoLinkNode *head;
    struct TwoLinkNode *tail;
    int size;
} TwoLinkList;

void initTwoLinkList(TwoLinkList *lst){
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

bool TwoLinkEnqueue(TwoLinkList *queue, int value){
    TwoLinkNode *tmp = (TwoLinkNode *)malloc(sizeof(TwoLinkNode));
    if(tmp == NULL){
        printf("Out of memory\n");
        return false;
    }
    tmp->dat = value;
    tmp->next = NULL;
    tmp->prev = queue->tail;
    if(queue->tail != NULL){
        queue->tail->next = tmp;
    }
    if(queue->head == NULL){
        queue->head = tmp;
    }
    queue->tail = tmp;
    queue->size++;
    return true;

}

int TwoLinkDequeue(TwoLinkList *queue){
    if(queue->size == 0){
        printf("Queue is empty\n");
        return -1;
    }
    TwoLinkNode *tmp = queue->head;
    int data = queue->head->dat;
    queue->head = queue->head->next;

    if(queue->head != NULL){
        queue->head->prev = NULL;
    }
    if(tmp == queue->tail){
        queue->tail = NULL;
    }

    free(tmp);
    queue->size--;
    return data;
}

void clearIntArray(int *visit, int size){
    for(int i = 0; i < size ; ++i){
        visit[i] = 0;
    }
}

int get2dInt(int **matrix, int i, int j){
    return matrix[i][j];
}

int visit[14] = {0};

int getUnvisitedVertex (int** matrix, int ver, int size) {
    for (int i = 0; i < size; i++) {
        if (get2dInt(matrix, ver, i) == 1 && !visit[i])
            return i;
    }
    return -1;
}

void depthTraversStack(int** matrix, int size) {
    OneLinkList* stack = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(stack);

    visit[0] = true;
    printf("%c ", 0 + 65);
    pushOneLinkStack(stack, 0);

    while (stack->size) {
        int v = getUnvisitedVertex(matrix, stack->head->dat, size);
        if (v == -1) {
            popOneLinkStack(stack);
        } else {
            visit[v] = true;
            printf("%c ", v + 65);
            pushOneLinkStack(stack, v);
        }
    }
    clearIntArray(visit, size);
    printf("\n");
}

int traversalLinks[14] = {0};
int adjacencyLinks[14] = {0};

void adjacencyCount (int** matrix, const int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[j][i] == 1)
                if (i != j) adjacencyLinks[i]++;
        }
    }
}

void traversalCount (int** matrix, int start, const int size) {
    TwoLinkList* queue = (TwoLinkList*) malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    clearIntArray(visit, size);
    TwoLinkEnqueue(queue, start);
    while (queue->size > 0) {
        int indx = TwoLinkDequeue(queue);
        if (visit[indx]) continue;
        visit[indx] = true;
        for (int i = 0; i < size; ++i) {
            if (get2dInt(matrix, indx, i) == 1) {
                if (i != indx)
                    traversalLinks[i]++;
                if (!visit[i])
                    TwoLinkEnqueue (queue, i);
            }
        }
    }
    clearIntArray(visit, size);
}

int graph[14][14] = {{0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                     {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                     {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
                     {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};

void fillGraph(int **matrix, int i, int j){
    for(int r = 0; r < i; ++r){
        for(int c = 0; c < j; ++c){
            matrix[r][c] = graph[r][c];
        }
    }
}

void printIntArray(int *array, const int size){

        for(int i = 0; i < size; ++i){
            printf("%4d", array[i]);
        }
        printf("\n");

}

void print2dIntArray(int **array, const int row, const int col){
    for(int r = 0; r < row; ++r){
        for(int c = 0; c < col; ++c){
            printf("%4d", *(*(array + c)+r));
        }
        printf("\n");
    }
}

int main() {
    int** adj = init2dIntArray(adj, 14, 14);
    fillGraph(adj, 14, 14);
    //print2dIntArray(adj, 14, 14);
    depthTraversStack (adj, 14);

    adjacencyCount(adj, 14);
    printIntArray(adjacencyLinks, 14);//, 3);

    traversalCount(adj, 0, 14);
    printIntArray(traversalLinks, 14);//, 3);
    return 0;
}
