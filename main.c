#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // for use boolean type
#include <time.h>

FILE *file;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} BinTreeIntNode;

BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data) {
    BinTreeIntNode *newNode;
    newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    BinTreeIntNode *current = t;
    BinTreeIntNode *parent = t;
    if (t == NULL) {
        t = newNode;
    } else {
        while (true) {//(current->key != data) {
            parent = current;
            if (current->key > data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printBinTree(BinTreeIntNode *root) {
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right) {
            printf("(");
            if (root->left)
                printBinTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printBinTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

BinTreeIntNode* getSuccessor(BinTreeIntNode *node) {
    BinTreeIntNode *current = node->right;
    BinTreeIntNode *parent = node;
    BinTreeIntNode *s = node;

    while (current != NULL) {
        parent = s;
        s = current;
        current = current->left;
    }
    if (s != node->right) {
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}

bool treeNodeDelete(BinTreeIntNode *root, int key) {
    BinTreeIntNode *current = root;
    BinTreeIntNode *parent = root;
    bool isLeftChild = true;
    while (current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
        if (current == NULL)
            return false;
    }
    if (current->left == NULL && current->right == NULL) {
        if (current == root)
            root == NULL;
        else if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (current->right == NULL) {
        if (isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if (current->left == NULL) {
        if (isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else {
        BinTreeIntNode *successor = getSuccessor(current);
        if (current == root)
            root = successor;
        else if (isLeftChild)
            parent->left = successor;
        else
            parent->right = successor;
        successor->left = current->left;
    }
    free(current);
    return true;
}


void freeBinTree(BinTreeIntNode *node)
{
    if (node != NULL)
    {
        freeBinTree(node->right);
        freeBinTree(node->left);
        free(node);
    }
}

bool binSearch(BinTreeIntNode *root, int value) {
    if (root == NULL)
        return false;
    if (root->key == value)
        return true;

    BinTreeIntNode *current = root;
    while (current->key != value) {
        if (value < current->key)
            current = current->left;
        else
            current = current->right;

        if (current == NULL)
            return false;
    }
}

BinTreeIntNode* balancedTree(int n, bool bal) {
    BinTreeIntNode *newNode;
    int x;
    int nL;
    int nR;

    if (n == 0) {
        return NULL;
    } else {
        fscanf(file, "%d", &x);
        if (bal) {
         nL = n / 2;
         nR = n - nL - 1;
         newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
         newNode->key = x;
         newNode->left = balancedTree(nL,bal);
         newNode->right = balancedTree(nR,bal);
        }
        else {
         newNode=treeInsert(NULL, x );
         for (int i=0;i<(n-1);i++) {
          fscanf(file, "%d", &x);
          treeInsert(newNode, x);
         }
        }
    }
    return newNode;
}

int maxDepth(BinTreeIntNode* root) {
    if (!root) {
        return 0;
    }
    int l=maxDepth(root->left);
    int r=maxDepth(root->right);
    return  (( l >= r ? l : r)+1);
}

int minDepth(BinTreeIntNode* root) {
    if (!root) {
        return 0;
    }
    int l=minDepth(root->left);
    int r=minDepth(root->right);
    return  ((l >= r ? r : l)+1);
}

bool isBalanced(BinTreeIntNode *root) {
    int a1=maxDepth(root);
    int a2= minDepth(root);
//    printf("%d %d\n",a1,a2);
    if ((a1 - a2) <= 1)
        return true;
    else
        return false;     
}

BinTreeIntNode* binSearchRec(BinTreeIntNode *root, int dat) {
    if (!root) return NULL;
    if (root->key==dat) return root;

    BinTreeIntNode *current = root;


    if (dat < current->key) {
        current = binSearchRec(current->left,dat);
        if (current!=NULL) return current;

    }
    else {
        current = binSearchRec(current->right,dat);
        if (current!=NULL) return current;
    }

    return NULL;
}


int main()
{
//  Task 1
    printf("Task 1\n");
    const int count = 15;
    BinTreeIntNode* tree;
    file = fopen("balance.txt", "r");
    tree = balancedTree(count,false);
    printBinTree(tree);
    printf("\nTree is ");
    printf(isBalanced(tree)? "balanced\n" : "not balanced\n");
    freeBinTree(tree);
    fclose(file);

    file = fopen("balance.txt", "r");
    tree = balancedTree(count,true);
    printBinTree(tree);
    printf("\nTree is ");
    printf(isBalanced(tree)? "balanced\n" : "not balanced\n");
    freeBinTree(tree);
    fclose(file);

//  Task 2
    printf("\nTask 2\n");
    srand(time(NULL));
    const int cNodes=10000;
    const int cTree=50;
    const int rnd=10000;
    int z;
    BinTreeIntNode* TT[cTree];
//    BinTreeIntNode* tree;
    for (int i=0; i<cTree; i++) {
      tree=treeInsert(NULL, (rand()%rnd));
     for (int j=1; j<cNodes; j++) {
        z= (rand()%rnd);
        treeInsert(tree, z);
     }
     TT[i]=tree;
    }
    z=0;
    for (int i=0;i<cTree;i++) {
        //printBinTree(TT[i]); printf("\n");
     if (isBalanced(TT[i])) z++;
     freeBinTree(TT[i]);
    }
    printf("Percent balanced %d trees %0.2f\n",cTree,((double) (z*100/cTree)));

//  Task 3
    printf("\nTask 3\n");
    tree = treeInsert(NULL, 10);
    treeInsert(tree, 8);
    treeInsert(tree, 19);
    treeInsert(tree, 5);
    treeInsert(tree, 9);
    treeInsert(tree, 16);
    treeInsert(tree, 21);
    printBinTree(tree);
    printf(" \n");
    z=22;
    printf("Find value %d\n", z);
    printf( (binSearch(tree, z)? "present" : "not present"));
    printf(" \n");

    BinTreeIntNode* elem=binSearchRec(tree, z);
    if (elem) {
     printf("\nPointer present");
     printf("\nValue %d is found",elem->key );
    }
    else printf("\nPointer is NULL");
    printf(" \n");
    freeBinTree(tree);

    return 0;
}
