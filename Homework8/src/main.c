#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} TreeNode;

TreeNode *treeInsert(TreeNode *t, int data){
    TreeNode *new = (TreeNode *)malloc(sizeof (TreeNode));
    new->key = data;
    new->left = NULL;
    new->right = NULL;
    TreeNode *current = t;
    TreeNode *parent = t;

    if(t == NULL){
        t = new;
    } else {

        while(current->key != data){
            parent = current;
            if(current->key > data){
                current = current->left;
                if(current == NULL){
                    parent->left = new;
                    return t;
                }
            } else {
                 current = current->right;
                 if(current == NULL){
                     parent->right = new;
                     return t;
                 }
            }
        }
    }
    return t;
}

bool treeDelete(TreeNode *root, int key){
    TreeNode *current = root;
    TreeNode *parent = root;
    bool isLeftChild = true;

    while(current->key != key){
        parent = current;
        if(key < current->key){
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
        if(current == NULL)
            return false;
    }

    if(current->left == NULL && current->right == NULL){
        if(current == root)
            root = NULL;
        else if(isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if(current->right == NULL){
        if(isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if(current->left == NULL){
        if(isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else{
        TreeNode *successor = current->right;
        TreeNode *successsorParent;
        while(successor->left != NULL){
            successsorParent = successor;
            successor = successor->left;
        }

        if(successor != current->right){
            successsorParent->left = successor->right;
            successor->right = current->right;
        }

        if(current == root)
            root = successor;
        else if(isLeftChild)
            parent->left = successor;
        else
            parent->right = successor;
        successor->left = current->left;
    }
}

void printTree(TreeNode *root){
    if(root){
        printf("%d",root->key);
        if(root->left || root->right){
            printf("(");
            if(root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");
            if(root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

int treeDepthCount(TreeNode *root){
    if(root == NULL)
        return 0;

    int nR = 0;
    int nL = 0;
    if(root->left)
        nL = treeDepthCount(root->left);
    if(root->right)
        nR = treeDepthCount(root->right);

    return 1 + ((nL > nR) ? nL : nR);
}

bool treeIsBalanced(TreeNode *t){
    int nR = 0;
    int nL = 0;

    nL = treeDepthCount(t->left);
    nR = treeDepthCount(t->right);
    //printf("nL = %d, nR = %d\n", nL, nR);
    return abs(nL - nR) <= 1;
}

void treeFree(TreeNode *root){
    if(root){
        if(root->left){
            treeFree(root->left);
            free(root->left);
            root->left = NULL;
        }
        if(root->right){
            treeFree(root->right);
            free(root->right);
            root->right = NULL;
        }

    }
}

void task1(){
    printf("Task1\n");
    int balanced = 0;
    const int TREES = 50;
    srand(time(NULL));

    for(int i = 1; i <= 50; ++i){
        TreeNode *root = NULL;
        TreeNode *tree = treeInsert(root, rand() % 1000);
        for(int j = 0; j < 10000; ++j)
            treeInsert(tree, rand() % 1000);

        balanced += treeIsBalanced(tree) ? 1 : 0;
        treeFree(root);
    }
    printf("Balanced trees %d%% of %d\n", balanced * 100 / TREES, TREES);
}

TreeNode* treeSearchNode(TreeNode *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return treeSearchNode(root->left, key);
    else
        return treeSearchNode(root->right, key);
}

void task2(){
    printf("Task2\n");
    TreeNode *tree = treeInsert(tree, rand() % 1000);
    for(int j = 0; j < 10000; ++j)
        treeInsert(tree, rand() % 1000);

    int searchKey = 10;
    printf("Key %d %sfound in tree\n", searchKey, treeSearchNode(tree, searchKey) == NULL ? "not " : "");
    treeFree(tree);
}
int main() {

    task1();
    task2();

    return 0;
}
