#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

Node *createList(){
    Node *head=NULL;
    //head=(Node*)malloc(sizeof(Node));
    //head->next=NULL;
    return head;
}

Node3 *createTreeNode(int d){
    Node3 *newNode=(Node3*)malloc(sizeof(Node3));
    if(newNode==NULL)
        return NULL;
    newNode->stocks=NULL;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->depth=d;
    return newNode;
}

void addNodeBeg(Node **head, double v){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->val=v;
    newNode->randament=0;
    newNode->next=*head;
    *head=newNode;
}

void addNodeEnd(Node **head, double v){
    
    if(*head==NULL)
        addNodeBeg(head,v);
    else{
        Node *aux=*head;
        Node *newNode=(Node*)malloc(sizeof(Node));
        newNode->val=v;
        newNode->randament=0;
        while(aux->next!=NULL)
        aux=aux->next;
    aux->next=newNode;
    newNode->next=NULL;
    }
}

void randa(Node **head){
    Node *copy=*head;
    while(copy!=NULL && copy->next!=NULL)
    {
        copy->next->randament=(copy->next->val-copy->val)/(copy->val);
        copy=copy->next;
    }
}

double randMed(Node **head, int n){
    Node *copy=*head;
    double rm=0;
    copy=copy->next;
    while(copy!=NULL)
    {
        rm=rm+copy->randament;
        copy=copy->next;
    }
    rm=rm/n;
    return rm;
}

double volatilitate(Node **head, int n, double rm){
    Node *copy=*head;
    double vol=0;
    copy=copy->next;
    while(copy!=NULL)
    {
        vol=vol+(copy->randament-rm)*(copy->randament-rm);
        copy=copy->next;
    }
    double top=vol/n;
    top=sqrt(top);
    return top;
}

void freePort(Node *head){
    while(head!=NULL)
    {
        Node *copy=head;
        head=head->next;
        free(copy);
    }
}

int isEmpty(const Node2 *top){
    return top==NULL;
}

void push(Node2 **top, double v){
    Node2 *newNode=(Node2*)malloc(sizeof(Node2));
    newNode->pret=v;
    newNode->next=*top;
    *top=newNode;
}

double pop(Node2 **top){
    if(isEmpty(*top)) return -1;
    Node2 *temp=*top;
    double aux=temp->pret;
    *top=(*top)->next;
    free(temp);
    return aux;
}

Queue *createQueue(){
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    if(q==NULL) return NULL;
    q->front=q->rear=NULL;
    return q;
}

void enQueue(Queue *q, int ziua, double dife, const char nume[]){
    Node2 *newNode=(Node2*)malloc(sizeof(Node2));
    if(newNode==NULL) return;
    newNode->info.zi=ziua;
    newNode->info.dif=dife;
    strcpy(newNode->info.piata, nume);
    newNode->next=NULL;
    if(q->rear==NULL)
        q->rear=newNode;
    else
        {
            q->rear->next=newNode;
            q->rear=newNode;
        }
    if(q->front==NULL) q->front=q->rear;
}

int isEmptyQueue(const Queue *q){
    return(q->front==NULL);
}

void citirePiata(FILE *fisin, Node2 **s1, Node2 **s2, Node2 **s3, char n1[], char n2[], char n3[]){
    char buffer[100];
    char line[100];
    double p;
    long poz;
    
    if(fgets(line, sizeof(line), fisin))
        strcpy(n1, line);

    while(1) //piata 1
    {
        poz=ftell(fisin);
        if(fgets(line, sizeof(line), fisin)==NULL)
            break;
        strcpy(buffer, line);
        if(buffer[0]>='0' && buffer[0]<='9') //se verifica daca este cifra, respectiv pret
            {
                fseek(fisin, poz, SEEK_SET);
                fscanf(fisin, "%lf", &p);
                push(s1, p);
                fgets(line, sizeof(line), fisin);
            }
            else
                {
                    strcpy(n2, buffer); //numele pietei 2
                    break;
                }
    }
    while(1) //piata 2
    {
        poz=ftell(fisin);
        if(fgets(line, sizeof(line), fisin)==NULL)
            break;
        strcpy(buffer, line);
        if(buffer[0]>='0' && buffer[0]<='9') //se verifica daca este cifra, respectiv pret
            {
                fseek(fisin, poz, SEEK_SET);
                fscanf(fisin, "%lf", &p);
                push(s2, p);
                fgets(line, sizeof(line), fisin);
            }
            else
                {
                    strcpy(n3, buffer); //numele pietei 2
                    break;
                }
    }
    while(fscanf(fisin, "%lf", &p)==1)
        push(s3, p);
}

void verifArb(Node2 **s1, Node2 **s2, Node2 **s3, Queue *q, char n1[], char n2[], char n3[]){
    int z=1;
    while(!isEmpty(*s1) && !isEmpty(*s2) && !isEmpty(*s3))
    {
        double p1=pop(s1);
        double p2=pop(s2);
        double p3=pop(s3);

        if(p1==p2 && p1!=p3)
            enQueue(q, z, fabs(p1-p3), n3);
        else if(p1==p3 && p1!=p2)
            enQueue(q, z, fabs(p1-p2), n2);
        else if(p2==p3 && p2!=p1)
            enQueue(q, z, fabs(p2-p1), n1);

        z++;
    }
}

void addStock(Sl **head, const char nume[]){
    Sl *newNode=(Sl*)malloc(sizeof(Sl));
    strcpy(newNode->symbol, nume);
    newNode->next=NULL;
    if(*head==NULL)
        *head=newNode;
    else
    {
        Sl *aux=*head;
        while(aux->next!=NULL)
            aux=aux->next;
        aux->next=newNode;
    }
}

double StD(const char s[]){
    double val=0;
    int i=0;

    while(s[i]>='0' && s[i]<='9')
    {
        val=val*10+(s[i]-'0');
        i++;
    }
    if(s[i]=='.')
    {
        i++;
        double div=10;
        while(s[i]>='0' && s[i]<='9')
        {
            val=val+(s[i]-'0')/div;
            div=div*10;
            i++;
        }
    }
    return val;
}

int nrZile(FILE *fisin, Node3 *root, char s[10][5], int ev[10][500]){
    char buffer[500];
    double pret[10];
    Node3 *temp[10];
    int cnt=0;

    if(!fgets(buffer, sizeof(buffer), fisin)) //simbolurile
        return 0;
    char *p=strtok(buffer, ",\n\r");
    for(int i=0; i<10 && p!=NULL; i++)
        {
            strcpy(s[i], p);
            temp[i]=root;
            addStock(&(root->stocks), s[i]);
            p=strtok(NULL, ",\n\r");
        }

    if(!fgets(buffer, sizeof(buffer), fisin)) //prima zi - o luam ca fiind ziua 0
        return 0;
    p=strtok(buffer, ",\n\r");
    for(int i=0; i<10 && p!=NULL; i++)
        {
            pret[i]=StD(p);
            p=strtok(NULL, ",\n\r");
        }
    
    while(fgets(buffer, sizeof(buffer), fisin))
    {
        p=strtok(buffer, ",\n\r");
        for(int i=0; i<10 && p!=NULL; i++)
        {
            double aux=StD(p);
            if(aux>=pret[i]) //crestere de pret
            {
                if(temp[i]->right==NULL)
                    temp[i]->right=createTreeNode(temp[i]->depth+1); //o zi noua, adancime+1
                temp[i]=temp[i]->right;
                ev[i][cnt]=1; //se misca la dreapta
            }
            else //scadere de pret
            {
                if(temp[i]->left==NULL)
                    temp[i]->left=createTreeNode(temp[i]->depth+1); //o zi noua, adancime+1
                temp[i]=temp[i]->left;
                ev[i][cnt]=0; //se misca la stanga
            }
            addStock(&(temp[i]->stocks), s[i]);
            pret[i]=aux;
            p=strtok(NULL, ",\n\r");
        }
        cnt++;
    }
    return cnt;
}

Node3 *ogl(Node3 *root, const int ev[], int n){
    Node3 *temp=root;
    for(int k=0; k<n; k++)
    {
        if(ev[k]==1)
            temp=temp->left; //actiunea a crescut, deci mergem spre stanga (unde scade)
        else 
            temp=temp->right; //actiunea a scazut, deci mergem spre dreapta (unde creste)
        if(temp==NULL)
            return NULL;
    }
    return temp;
}

void freeStocks(Sl *head){
    while(head!=NULL)
    {
        Sl *temp=head;
        head=head->next;
        free(temp);
    }
}

void freeTree(Node3 *root){
    if(root==NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    if(root->stocks!=NULL)
        freeStocks(root->stocks);
    free(root);
}

Interval *createInterval(FILE *fisin, Input *input){
    if(fscanf(fisin, "%d%lf%d%lf%lf", &input->N, &input->d, &input->K, &input->pStart, &input->pTarget)!=5)
        return NULL;
    
    double *p_trecut=(double*)malloc(input->N*sizeof(double));
    int *idx_trecut=(int*)malloc(input->N*sizeof(int));

    for(int i=0; i<input->N; i++)
        {
        fscanf(fisin, "%lf", &p_trecut[i]);
        idx_trecut[i]=(int)floor(p_trecut[i]/input->d); //calculam intervalul din care face parte fiecare pret trecut
        }
    
    int idx_start=(int)floor(input->pStart/input->d); //intervalul pt pretul de start
    int idx_target=(int)floor(input->pTarget/input->d); //intervalul pt pretul target

    int max_idx=idx_start;
    input->min=idx_start;

    if(idx_target>max_idx)
        max_idx=idx_target;
    if(idx_target<input->min)
        input->min=idx_target;

    for(int i=0; i<input->N; i++)
    {
        if(idx_trecut[i]>max_idx)
            max_idx=idx_trecut[i];
        if(idx_trecut[i]<input->min)
            input->min=idx_trecut[i];
    }

    input->nr=max_idx-input->min+1; //numarul de intervale

    for(int i=0; i<input->N; i++)
        idx_trecut[i]=(int)floor(p_trecut[i]/input->d)-input->min; //idx-urile intervalelor in vectorul de stari

    Interval *stari=(Interval*)calloc(input->nr, sizeof(Interval));

    for(int i=0; i<input->nr; i++)
    {
        int idx=input->min+i; //idx-ul intervalului curent

        stari[i].idx=i;
        stari[i].in=0;
        stari[i].out=0;
        stari[i].st=idx*input->d; //capatul din stanga al intervalului
        stari[i].dr=(idx+1)*input->d; //capatul din dreapta al intervalului
        stari[i].vecini=(int*)calloc(input->nr, sizeof(int));
    }

    if(input->N>0)
    {
        int idx_prev=idx_trecut[0]; //idx-ul intervalului din care face parte primul pret trecut
        stari[idx_prev].in++; //intram in acest interval
    }

    for(int i=0; i<input->N-1; i++)
    {
        int idx_prev=idx_trecut[i]; //idx-ul intervalului din care face parte pretul trecut curent
        int idx_next=idx_trecut[i+1]; //idx-ul intervalului din care face parte pretul trecut urmator

        stari[idx_prev].out++; //iesiri din acest interval
        stari[idx_next].in++; //intrari in acest interval

        stari[idx_prev].vecini[idx_next]++; //adaugam un 'drum' de la idx_prev la idx_next
    }

    free(p_trecut);
    free(idx_trecut);
    return stari;
} 

long long cmmdc(long long a, long long b){
    if(a<0)
        a=(-1)*a;
    if(b<0)
        b=(-1)*b;
    while(b!=0)
    {
        long long r=a%b;
        a=b;
        b=r;
    }
    if(a==0)
        return 1;
    return a;
}

Fr simplificare(Fr f){
    if(f.numarator==0)
    {
        f.numitor=1;
        return f;
    }
    else
    {
    long long div=cmmdc(f.numarator, f.numitor);
    f.numarator=f.numarator/div;
    f.numitor=f.numitor/div;
    if(f.numitor<0)
    {
        f.numitor=(-1)*f.numitor;
        f.numarator=(-1)*f.numarator;
    }
    return f;
    }
}

Fr adunare(Fr f1, Fr f2){
    Fr rez;
    rez.numarator=f1.numarator*f2.numitor+f2.numarator*f1.numitor;
    rez.numitor=f1.numitor*f2.numitor;
    return simplificare(rez);
}

Fr inmultire(Fr f1, Fr f2){
    Fr rez;
    rez.numarator=f1.numarator*f2.numarator;
    rez.numitor=f1.numitor*f2.numitor;
    return simplificare(rez);
}