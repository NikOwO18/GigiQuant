#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lib.h"

int main(int argc, char *argv[])
{
    FILE *fisin = fopen(argv[1], "r");
    FILE *fisout = fopen(argv[2], "w");

    if (fisin == NULL || fisout == NULL)
    {
        printf("Eroare\n");
        return 1;
    }

    // verificare task
    if (strstr(argv[1], "data1.in") || strstr(argv[1], "data2.in") || strstr(argv[1], "data3.in") || strstr(argv[1], "data4.in") || strstr(argv[1], "data5.in"))
    {
        // task ul 1
        Node *port = NULL;
        createList(port);
        int n;       // nr de portofolii
        double temp; // valoare dintr un portofoliu

        fscanf(fisin, "%d", &n);
        for (int i = 0; i < n; i++)
        {
            fscanf(fisin, "%lf", &temp);
            addNodeEnd(&port, temp); // se citesc preturile din fisiere
        }

        randa(&port); // se calculeaza randamentele

        double rm;
        rm = randMed(&port, n - 1); // se calculeaza randamentul mediu

        double vol;
        vol = volatilitate(&port, n - 1, rm); // se calculeaza volatilitatea

        double sr;
        sr = rm / vol * 1.0; // se calculeaza sharperatio

        // afisare trunchiata
        rm = trunc(rm * 1000.0) / 1000.0;
        vol = trunc(vol * 1000.0) / 1000.0;
        sr = trunc(sr * 1000.0) / 1000.0;
        fprintf(fisout, "%.3lf\n", rm);
        fprintf(fisout, "%.3lf\n", vol);
        fprintf(fisout, "%.3lf\n", sr);

        freePort(port);
    }

    if (strstr(argv[1], "data6.in") || strstr(argv[1], "data7.in") || strstr(argv[1], "data8.in") || strstr(argv[1], "data9.in") || strstr(argv[1], "data10.in"))
    {
        // task ul 2
        char piata1[50], piata2[50], piata3[50]; // numele pietelor
        Node2 *s1 = NULL;                        // stiva 1
        Node2 *s2 = NULL;                        // stiva 2
        Node2 *s3 = NULL;                        // stiva 3
        Queue *q = createQueue();

        citirePiata(fisin, &s1, &s2, &s3, piata1, piata2, piata3);

        verifArb(&s1, &s2, &s3, q, piata1, piata2, piata3);

        while (!isEmptyQueue(q))
        {
            Node2 *temp = q->front;
            fprintf(fisout, "ziua %d - %0.2lf - %s", temp->info.zi, temp->info.dif, temp->info.piata);
            q->front = q->front->next;
            free(temp);
        }

        while (!isEmpty(s1))
            pop(&s1);
        while (!isEmpty(s2))
            pop(&s2);
        while (!isEmpty(s3))
            pop(&s3);
        free(q);
    }

    if (strstr(argv[1], "data11.in") || strstr(argv[1], "data12.in") || strstr(argv[1], "data13.in") || strstr(argv[1], "data14.in") || strstr(argv[1], "data15.in"))
    {
        // task ul 3
        char sym[10][5];
        int ev[10][500]; // 0 daca pretul scade, 1 daca pretul creste
        Node3 *root = createTreeNode(0);

        int cnt = nrZile(fisin, root, sym, ev);

        int vizitat[10][10];
        int lin = 1;

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                vizitat[i][j] = 0; // verificam sa nu se afiseze duplicat

        for (int i = 0; i < 10; i++)
        {
            Node3 *mirr = ogl(root, ev[i], cnt);

            if (mirr != NULL)
            {
                Sl *aux = mirr->stocks;
                while (aux != NULL)
                {
                    int j = 0;
                    for (int k = 0; k < 10; k++)
                        if (strcmp(sym[k], aux->symbol) == 0)
                        {
                            j = k;
                            break;
                        }
                    if (i != j && vizitat[i][j] == 0)
                    {
                        if (lin == 1)
                        {
                            fprintf(fisout, "%s-%s", sym[i], sym[j]);
                            vizitat[i][j] = 1;
                            vizitat[j][i] = 1;
                            lin = 0;
                        }
                        else
                        {
                            fprintf(fisout, "\n%s-%s", sym[i], sym[j]);
                            vizitat[i][j] = 1;
                            vizitat[j][i] = 1;
                        }
                    }
                    aux = aux->next;
                }
            }
        }
        freeTree(root);
    }

    if (strstr(argv[1], "data16.in") || strstr(argv[1], "data17.in") || strstr(argv[1], "data18.in") || strstr(argv[1], "data19.in") || strstr(argv[1], "data20.in"))
    {
        // task ul 4
        Input input;
        Interval *stari = createInterval(fisin, &input);

        if (stari != NULL)
        {
            Fr *curr = (Fr *)malloc(input.nr * sizeof(Fr));
            Fr *next = (Fr *)malloc(input.nr * sizeof(Fr));

            int idx_start = (int)floor(input.pStart / input.d); // idx-ul intervalului de start

            // ziua 0
            for (int i = 0; i < input.nr; i++)
            {
                int idx = input.min + stari[i].idx; // idx-ul intervalului curent
                if (idx == idx_start)
                {
                    curr[i].numarator = 1;
                    curr[i].numitor = 1;
                }
                else
                {
                    curr[i].numarator = 0;
                    curr[i].numitor = 1;
                }
            }

            int idx_target1 = (int)floor(input.pTarget / input.d);
            int idx_tinta1 = idx_target1 - input.min;

            if (idx_tinta1 >= 0 && idx_tinta1 < input.nr)
            {
                Fr raspuns = simplificare(curr[idx_tinta1]);

                if (raspuns.numarator == 0)
                    fprintf(fisout, "0");
                else if (raspuns.numarator == raspuns.numitor)
                    fprintf(fisout, "1");
                else
                    fprintf(fisout, "%lld/%lld", raspuns.numarator, raspuns.numitor);
            }

            // cele k zile
            for (int i = 0; i < input.K-1; i++)
            {
                for (int j = 0; j < input.nr; j++)
                {
                    next[j].numarator = 0;
                    next[j].numitor = 1;
                }

                for (int j = 0; j < input.nr; j++)
                {
                    if (curr[j].numarator != 0)
                    {
                        if (stari[j].out != 0)
                        {
                            for (int k = 0; k < input.nr; k++)
                            {
                                if (stari[j].vecini[k] != 0)
                                {
                                    Fr aux;
                                    aux = inmultire(curr[j], (Fr){stari[j].vecini[k], stari[j].out}); // calculam probabilitatea de a ajunge in starea k din starea j
                                    next[k] = adunare(next[k], aux);
                                }
                            }
                        }
                    }
                    else
                        next[j] = adunare(next[j], curr[j]);
                }

                for (int j = 0; j < input.nr; j++)
                    curr[j] = next[j];

                int idx_target2 = (int)floor(input.pTarget / input.d);
                int idx_tinta2 = idx_target2 - input.min;

                if (idx_tinta2 >= 0 && idx_tinta2 < input.nr)
                {
                    Fr raspuns = simplificare(curr[idx_tinta2]);

                        if (raspuns.numarator == 0)
                            fprintf(fisout, "\n0");
                        else if (raspuns.numarator == raspuns.numitor)
                            fprintf(fisout, "\n1");
                        else
                            fprintf(fisout, "\n%lld/%lld", raspuns.numarator, raspuns.numitor);

                    for (int p = 0; p < input.nr; p++)
                        free(stari[p].vecini);
                }

                free(stari);
                free(curr);
                free(next);
            }
        }
    }

    fclose(fisin);
    fclose(fisout);

    return 0;
}