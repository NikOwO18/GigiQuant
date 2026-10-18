#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Elem{
    double val;
    double randament;
    struct Elem *next;
};

typedef struct Elem Node;

struct Arb{
    int zi;
    double dif;
    char piata[50];
};

typedef struct Arb Arbitraj;

struct Elem2{
    double pret;
    Arbitraj info;
    struct Elem2 *next;
};

typedef struct Elem2 Node2;

struct Q{
    Node2 *front, *rear;
};

typedef struct Q Queue;

struct StockList{
    char symbol[5];
    struct StockList *next;
};

typedef struct StockList Sl;

struct TreeNode{
    Sl *stocks;
    struct TreeNode *left; //scadere
    struct TreeNode *right; //crestere
    int depth; //ziua
};

typedef struct TreeNode Node3;

struct fractie{
    long long numarator;
    long long numitor;
};

typedef struct fractie Fr;

struct Markov{
    int idx; //al catelea interval
    int out; //de cate ori iese din interval
    int in; //de cate ori intra in interval
    double st; //capatul din stanga
    double dr; //capatul din dreapta
    int *vecini;
};

typedef struct Markov Interval;

struct Inp{
    int N;
    int K;
    double d;
    double pStart;
    double pTarget;
    int min;
    int nr;
};

typedef struct Inp Input;

Node *createList();
void addNodeBeg(Node **head, double v);
void addNodeEnd(Node **head, double v);
void randa(Node **head);
double randMed(Node **head, int n);
double volatilitate(Node **head, int n, double rm);
void freePort(Node *head);
void push(Node2 **top, double v);
double pop(Node2 **top);
int isEmpty(const Node2 *top);
void enQueue(Queue *q, int ziua, double dife, const char nume[]);
int isEmptyQueue(const Queue *q);
Queue *createQueue();
void citirePiata(FILE *fisin, Node2 **s1, Node2 **s2, Node2 **s3, char n1[], char n2[], char n3[]);
void verifArb(Node2 **s1, Node2 **s2, Node2 **s3, Queue *q, char n1[], char n2[], char n3[]);
Node3 *createTreeNode();
void addStock(Sl **head, const char nume[]);
Node3 *createTreeNode(int d);
double StD(const char s[]);
int nrZile(FILE *fisin, Node3 *root, char s[10][5], int ev[10][500]);
Node3 *ogl(Node3 *root, const int ev[], int n);
void freeStocks(Sl *head);
void freeTree(Node3 *root);
Interval *createInterval(FILE *fisin, Input *input);
long long cmmdc(long long a, long long b);
Fr simplificare(Fr f);
Fr adunare(Fr f1, Fr f2);
Fr inmultire(Fr f1, Fr f2);