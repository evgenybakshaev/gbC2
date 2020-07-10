#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//task 1
#define SZ 10

typedef struct {
    int pr;
    int dat;
} Node;

Node *arr[SZ];
int head;
int tail;
int items;

void queueInit(){
    for(int i = 0; i < SZ; ++i){
        arr[i] = NULL;
    }
    head = 0;
    tail = 0;
    items = 0;
}

bool queueIn(int pr, int dat){
    Node *node = (Node*)malloc(sizeof(Node));
    node->pr = pr;
    node->dat = dat;

    if(items == SZ){
        printf("Queue is full\n");
        return true;
    }

    arr[tail % SZ] = node;
    ++items;
    ++tail;
    tail %= SZ;
    return false;
}

bool queueOut(int *outPr, int *outDat){
    if(items == 0){
        printf("Queue is empty\n");
        return true;
    }
    int idx = head;
    for(int i = 1; i < items; ++i){
        if(arr[(head + i) % SZ]->pr > arr[idx % SZ]->pr)
            idx = head + i;
    }

    *outDat = arr[idx % SZ]->dat;
    *outPr = arr[idx % SZ]->pr;

    for(int i = idx; i >= head; --i){
        arr[i % SZ] = arr[(i - 1) % SZ];
    }
    free(arr[head % SZ]);
    ++head;
    head %= SZ;
    --items;

    return false;
}

void queuePrint(){
    printf("   pr\t|   dat\n");
    printf("--------+--------\n");
    for(int i = items; i > 0; --i){
        int dat, pr;
        if(!queueOut(&pr, &dat))
            printf("   %d\t|   %d\n", pr, dat);
    }
    printf("\n");
}

//task 2
#define T bool
#define STACKSIZE 1000
T stack[STACKSIZE];
int cursor = -1;

int push(T data){
    if(cursor < STACKSIZE){
        stack[++cursor] = data;
        return cursor;
    }
    else{
        printf("Stack is full \n");
        return -1;
    }
}

T pop(){
    if(cursor != -1){
        return stack[cursor--];
    }
    else {
        printf("Stack is empty \n");
        return - 1;
    }
}

void int2bin(int number){
    printf("number %d in positioanl base 2 = ", number);
    do{
        push(number % 2);
    }while(number /= 2);


    for(int i = 0; cursor != -1; ++i){
        if(i != 0 && (i % 8) == 0)
            printf(" ");
        printf("%d", pop());
    }
    printf("\n");
}


int main() {
    //task 1
    printf("Task 1\n");
    queueIn(1,1);
    queueIn(1,2);
    queueIn(2,3);
    queueIn(1,4);
    queueIn(1,5);
    queuePrint();

    queueIn(1,6);
    queueIn(1,7);
    queueIn(2,8);
    queueIn(1,9);
    queueIn(1,10);
    queueIn(3,11);
    queueIn(1,12);
    queuePrint();

    queueIn(1,13);
    queueIn(1,14);
    queueIn(2,15);
    queueIn(1,16);
    queueIn(1,17);
    queueIn(3,18);
    queueIn(1,19);
    queuePrint();

    queueIn(1,20);
    queueIn(1,21);
    queueIn(2,22);
    queueIn(1,23);
    queueIn(1,24);
    queueIn(3,25);
    queueIn(1,26);
    queuePrint();

    //task 2
    printf("Task 2G\n");
    int2bin(65533);

    return 0;
}
