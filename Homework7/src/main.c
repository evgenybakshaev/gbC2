#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char T;

typedef struct Node {
    T data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    unsigned int size;
} List;

void listInit(List * lst) {
    lst->head = NULL;
    lst->size = 0;
}

int listInsert(List *lst, T data) {
    Node *new = (Node *) malloc(sizeof (Node));
    if(new == NULL){
        //printf("Out of memory\n");
        return -1;
    }
    new->data = data;
    new->next = NULL;

    Node *current = lst->head;
    if(current == NULL) {
        lst->head = new;
    } else {
        while(current->next != NULL)
            current = current->next;
        current->next = new;
    }
    lst->size++;
    return 0;
}

int listRemove(List *lst, unsigned int index){
    Node *current = lst->head;
    Node *parrent = NULL;
    if(current == NULL)
        return -2;
    if(index >= lst->size)
        return -3;

    while(index--){
        parrent = current;
        current = current->next;
    }

    if(current == lst->head)
        lst->head = current->next;

    if(parrent != NULL)
        parrent->next = current->next;

    free(current);
    lst->size--;

    return 0;
}

T listAt(List *lst, int index) {
    Node *current = lst->head;
    if(current == NULL)
        return -2;
    if(index >= lst->size)
        return -3;
    while(index--){
        current = current->next;
    }
    return current->data;
}

void printNode(Node *n){
    if(n == NULL)
        printf("[]");
    else
        printf("[%d]", n->data);
}

void listPrint(List *lst){
    Node *current = lst->head;
    if(current == NULL){
        printNode(current);
    }
    else {
        do{
            printNode(current);
            current = current->next;
        }while(current != NULL);
    }
    printf(" Size: %d", lst->size);
}

typedef struct Stack {
    Node *head;
    unsigned int size;
} Stack;

void stackInit(Stack *stack) {
    stack->head = NULL;
    stack->size = 0;
}

int stackPush(Stack *stack, T value) {
    Node *tmp = (Stack *)malloc(sizeof (Node));
    if(tmp == NULL){
        return -1;
    }

    tmp->data = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;

    return 0;
}

int stackPop(Stack *stack, T *pOut) {
    if(stack->size == 0) {
        return -4;
    }

    Node *tmp = stack->head;
    *pOut = tmp->data;
    stack->head = tmp->next;
    stack->size--;
    free(tmp);
    return 0;
}

void stackPrint(Stack *stack){
    Node *current = stack->head;
    if(current != NULL){
        do{
            printf("[%c]", current->data);
            current = current->next;
        }while(current != NULL);
    }
    printf(" Size: %d\n", stack->size);
}

void checkBrackets(const char *str) {

    Stack stack, *pStack;
    List err, *pErr;
    int ret = 0;
    pStack = &stack;
    pErr = &err;
    stackInit(pStack);
    listInit(pErr);

    char c = '\0';
    int i;
    for(i = 0; str[i] != '\0'; ++i) {
        switch(str[i]){
        case '(':
           stackPush(pStack, ')');
           break;
        case '{':
           stackPush(pStack, '}');
           break;
        case '[':
            stackPush(pStack, ']');
            break;
        case ')':
        case '}':
        case ']':
            ret = stackPop(pStack, &c);
            if(c != str[i] || ret != 0){
                listInsert(pErr, i);
            }
            break;
        }
    }
    for(unsigned int j = 0; pStack->size > 0; ++j){
        stackPop(pStack, &c);
        listInsert(pErr, i+j);
    }
    if(pErr->size > 0){
        printf("Errors found:\n%s\n", str);
        int j = -1;
        int cnt = 0;
        for(unsigned int i = 0; pErr->size > 0; ++i){
            j = listAt(pErr, 0);
            listRemove(pErr, 0);

            while(j-cnt > 0){
                printf(" ");
                ++cnt;
            }
            printf("^");
            ++cnt;

        }
        printf("\n");
    }
    else {
        printf("%s\nNo errors found\n", str);
    }
    //stackPrint(pStack);
}

void task1(){
        const char *str = "([(2+({)2*2))))";
        const char *str2 = "[2/{5*(4+7)}]";
        checkBrackets(str);
        checkBrackets(str2);
}

void listCopy(List *lstFrom, List *lstTo){
    for(unsigned int i = 0; i < lstFrom->size; ++i){
        listInsert(lstTo, listAt(lstFrom, i));
    }
}

void task2(){
    List lst1, lst2, *pLst1, *pLst2;

    pLst1 = &lst1;
    pLst2 = &lst2;

    listInit(pLst1);
    listInit(pLst2);
    printf("List1: ");
    listPrint(pLst1);
    printf("\n");
    printf("List2: ");
    listPrint(pLst2);
    printf("\n");

    listInsert(pLst1, 1);
    listInsert(pLst1, 4);
    listInsert(pLst1, 2);
    printf("List1: ");
    listPrint(pLst1);
    printf("\n");
    listCopy(pLst1, pLst2);
    printf("List2: ");
    listPrint(pLst2);
    printf("\n");
}

bool listIsSorted(List *lst){
    Node *current = lst->head;
    while(current->next != NULL){
        if(current->data > current->next->data)
            return false;
        current = current->next;
    }
    return true;
}

void task3(){
    List lst1, lst2, *pLst1, *pLst2;

    pLst1 = &lst1;
    pLst2 = &lst2;
    listInit(pLst1);
    listInit(pLst2);

    listInsert(pLst1, 1);
    listInsert(pLst1, 4);
    listInsert(pLst1, 2);

    listInsert(pLst2, 1);
    listInsert(pLst2, 4);
    listInsert(pLst2, 8);

    printf("List1: ");
    listPrint(pLst1);
    if(listIsSorted(pLst1))
        printf(" is sorted\n");
    else
        printf(" is not sorted\n");
    printf("List2: ");
    listPrint(pLst2);
    if(listIsSorted(pLst2))
        printf(" is sorted\n");
    else
        printf(" is not sorted\n");
}

int main() {
    printf("Task1\n");
    task1();
    printf("Task2\n");
    task2();
    printf("Task3\n");
    task3();

    return 0;
}
