#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
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

int listInsert(List *lst, int data) {
    Node *new = (Node *) malloc(sizeof (Node));
    if(new == NULL){
        printf("Out of memory\n");
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
        return 1;
    if(index >= lst->size)
        return 2;

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
    printf(" Size: %d\n", lst->size);
}

int main() {
    List lst;
    List *pLst = &lst;
    listInit(pLst);
    listPrint(pLst);
    listInsert(pLst, 1);
    listPrint(pLst);
    listInsert(pLst, 4);
    listInsert(pLst, 2);
    listPrint(pLst);

    listRemove(pLst, 0);
    listPrint(pLst);
    return 0;
}
