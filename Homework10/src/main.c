#include <stdio.h>
#include <stdlib.h>

typedef int T;

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

T listAt(List *lst, unsigned int index) {
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
    if(n == NULL){
        printf("[]");
    }
    else{
        printf("%d", n->data);
        if(n->next != NULL)
            printf(", ");
    }
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
    printf("\n");
    //printf(" Size: %d", lst->size);
}


//Task 1
int hash(char *str){
    int result = 0;
    for(int i = 0; str[i] != '\0'; ++i){
        result+=str[i];
    }
    return result;
}

//Task 2
List* money(int* money, int size, int sum) {
    List *rslt = (List*) malloc(sizeof(List));
    listInit(rslt);
    int current;
    int balance = sum;
    for (int i = 0; i < size; ++i) {
        current = 0;
        while (balance - current >= money[i]) {
            current += money[i];
            listInsert(rslt, money[i]);
            if (balance == current)
                return rslt;
        }
        balance -= current;
    }
    printf("The amount %d cannot be collected with coins \n", sum);
    return NULL;
}


int main() {
    printf("%d \n", hash("HelloWorld!"));


    int coins[] = {50, 10, 5, 2, 1};
    listPrint(money(coins, 5, 98));

    return 0;
}
