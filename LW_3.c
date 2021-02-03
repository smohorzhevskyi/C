#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef struct treeNode {
    int key;
    struct treeNode * left;
    struct treeNode * right;
} tree;

typedef struct {
    tree ** array;
    int n;
    int head;
    int tail;
} queue;

void enqueue(queue*, tree*);
tree* dequeue(queue*);
queue * initQueue(int size);
int isEmpty(queue*);
int isFull(queue*);
void freeQueue(queue**);

tree * buildTree(tree*, int);
tree * createNode(int);
void freeNode(tree*);
int freeTree(tree*);
void levelOrder(tree*);

void inorder(tree*);
void post(tree*);
void pre(tree*);

queue * getAllOnLevelUsingPreorder(tree* root, int findOnLevel, int currentLevel, queue * q);
int sumOfNumbers(int integer);

int getLevelCount(tree*);


int main() {
    tree * root = NULL;
    int array[N] = {536, 679, 711, 561, 487, 339, 199, 695, 687, 851, 113, 65, 149, 466, 234, 579, 943, 387, 551, 92};

    for(int i = 0; i < N; i++) {
        root = buildTree(root, array[i]);
    }

printf("-------------- INORDER --------------\n"); inorder(root);
printf("\n-------------------------------------\n");

printf("------------- PREORDER --------------\n"); pre(root);
printf("\n-------------------------------------\n");

printf("------------- POSTORDER -------------\n"); post(root);
printf("\n-------------------------------------\n");

printf("------------ LEVEL ORDER ------------\n"); levelOrder(root);
printf("\n-------------------------------------\n");


    queue * q = initQueue(N);

    queue * qOnLevel = getAllOnLevelUsingPreorder(root, 4, 0, q);

    tree * node = dequeue(qOnLevel);
    if(isEmpty(q)){
        exit(42);
    }
    int min = sumOfNumbers(node->key);
    int minKey = node->key;
    while (!isEmpty(qOnLevel)) {
        tree * node = dequeue(qOnLevel);
       int sum = sumOfNumbers(node->key);
        if(sum<min){
            minKey= node->key;
            min = sum;
        }
    }

    freeTree(root);
    return 0;
}

int sumOfNumbers(int integer){
    int sum = 0;
    while(integer){
    int lastNumber = integer%10;
    sum = sum + lastNumber;
    integer = (integer - lastNumber)/10;
    }
    return sum;
}

tree * buildTree(tree* root, int key) {
    if (root == NULL) {
        root = createNode(key);
    } else {
        if (key < root->key) {
            root->left = buildTree(root->left, key);
        } else {
            root->right = buildTree(root->right, key);
        } }
    return root;
}

tree * createNode(int key) {
    tree * new = (tree*) malloc(sizeof(tree));
    assert(new != NULL);
    new->left = NULL;
    new->right = NULL;
    new->key = key;
    return new;
}

void inorder(tree* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%4d", root->key);
        inorder(root->right);
    }
}

void post(tree* root) {
    if (root != NULL) {
        post(root->left);
        post(root->right);
        printf("%4d", root->key);
    }
}

queue * getAllOnLevelUsingPreorder(tree* root, int findOnLevel, int currentLevel, queue * q) {
    currentLevel++;
    if (root != NULL) {
        if(currentLevel == findOnLevel){
            enqueue(q, root);
        } else {
            getAllOnLevelUsingPreorder(root->left, findOnLevel, currentLevel, q);
            getAllOnLevelUsingPreorder(root->right, findOnLevel, currentLevel, q);
        }
    }
    return q;
}

void pre(tree* root) {
   if (root != NULL) {
      printf("%4d", root->key);
       pre(root->left);
       pre(root->right);
} }

int freeTree(tree* root) {
    int counter =0;
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        freeNode(root);
        counter++;
    }
    return counter;
}

void freeNode(tree* addrOfNodeInHeap) {
    free(addrOfNodeInHeap);
}

int getLevelCount(tree* root) {
    if (root == NULL) {
        return 0;

    }
    int leftMaxLevel = 1 + getLevelCount(root->left); int rightMaxLevel = 1 + getLevelCount(root->right); if (leftMaxLevel > rightMaxLevel) {
        return leftMaxLevel;
    } else {
        return rightMaxLevel;
    }
}

void levelOrder(tree* root) {
    queue * q = initQueue(N);
    assert(root != NULL);
    enqueue(q, root);
    while (!isEmpty(q)) {
        tree * node = dequeue(q);
        printf("%4d", node->key);
        if (node->left != NULL) enqueue(q, node->left);
        if (node->right != NULL) enqueue(q, node->right);
    }
    freeQueue(&q);
    assert(q == NULL);
}

void freeQueue(queue** q) {
    free((*q)->array);
    free(*q);
    *q = NULL;
}

queue * initQueue(int size) {
    queue * newQueue = (queue*) malloc(sizeof(queue)); assert(newQueue != NULL);
    newQueue->n = size;
    newQueue->head = 0;
    newQueue->tail = 0;
    newQueue->array = (tree**) malloc(sizeof(tree*) * newQueue->n); assert(newQueue->array != NULL);
    return newQueue;
}

int isFull(queue * q) {
    if (q->tail == q->n - 1 && q->head == 0) return 1;
    if (q->tail + 1 == q-> head) return 1;
    return 0;
}

int isEmpty(queue * q) {
    if (q->tail == q-> head) return 1;
    return 0;
}

void enqueue(queue* q, tree* node) {
    if (isFull(q) == 1) exit(2);
    else {
        (q->array)[q->tail] = node;
        if (q->tail == q->n - 1) {
            q->tail = 0;
        } else {
            q->tail = q->tail + 1;
        }
    }
}

tree* dequeue(queue* q) {
    tree * result;
    if (isEmpty(q) == 1) exit(3);
    result = (q->array)[q->head];
    if (q->head == q->n - 1) {
        q->head = 0;
    } else {
        q->head = q->head + 1;
    }
    return result;
}