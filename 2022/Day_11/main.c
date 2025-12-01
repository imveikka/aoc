/*  Advent of Code: Day 11:
    Monkey in the Middle

    "Yeah just figure it out how to get
    the right output, good luck!"

    Author: Veikka Immonen @imveikka */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N (1 << 5)

/* Change these to solve silver/gold */
#define ROUNDS 10000
#define WORRY 3


typedef struct monke
{
    char oper;
    long items[N],
        divider;
    int next,
        len,
        n_oper,
        monke_true,
        monke_false;
} monke;


int monke_list_init(char *, monke *);
int cmp(const void *, const void *);


int main(int argc, char *argv[])
{   
    monke *monkes = calloc(N >> 1, sizeof *monkes);
    int total = monke_list_init(argv[1], monkes);
    long *inspects = calloc(total, sizeof *inspects);

    long divider = 1;
    for (int i = 0; i < total; i++) divider *= monkes[i].divider;

    for (int round = 0; round < ROUNDS; ++round)
    {
        for (int m = 0; m < total; ++m)
        {
            for (int i = 0; i < monkes[m].len; i++)
            {   
                inspects[m]++;
                if (monkes[m].oper == '+')
                    monkes[m].items[i] += (monkes[m].n_oper ? monkes[m].n_oper : monkes[m].items[i]);
                else
                    monkes[m].items[i] *= (monkes[m].n_oper ? monkes[m].n_oper : monkes[m].items[i]);

                /* Change this for silver/gold solution */
                monkes[m].items[i] %= divider;
                if (monkes[m].items[i] % monkes[m].divider == 0)
                    monkes[monkes[m].monke_true].items[monkes[monkes[m].monke_true].len++] = monkes[m].items[i];
                else
                    monkes[monkes[m].monke_false].items[monkes[monkes[m].monke_false].len++] = monkes[m].items[i];
            }
            monkes[m].len = 0;
        }
    }
    
    qsort(inspects, total, sizeof *inspects, cmp);
    printf("Result: %ld\n", inspects[0] * inspects[1]);

    free(inspects);
    free(monkes);
    return 0;
}


int monke_list_init(char *filename, monke *monkes)
{
    FILE *file = fopen(filename, "r");
    size_t bytes = 0;
    char *line, *token;
    int m = 0;

    for (; getline(&line, &bytes, file) != -1; m++)
    {
        /* 1. Skip title */

        /* 2. Read starting items */
        getline(&line, &bytes, file);
        token = strtok(line, " ");
        token = strtok(NULL, " ");
        for (int i = 0; (token = strtok(NULL, " ")) != NULL; monkes[m].len = ++i)
            monkes[m].items[i] = atoi(token);

        /* 3. Read operation */
        getline(&line, &bytes, file);
        token = strtok(line, " ");
        for (int i = 0; i < 4; ++i) token = strtok(NULL, " ");
        monkes[m].oper = *token;
        token = strtok(NULL, " ");
        monkes[m].n_oper = (strcmp(token, "old") == 0) ? 0 : atoi(token);

        /* 4. Divider */
        getline(&line, &bytes, file);
        token = strtok(line, " ");
        for (int i = 0; i < 3; ++i) token = strtok(NULL, " ");
        monkes[m].divider = atoi(token);

        /* 4.1. true */
        getline(&line, &bytes, file);
        token = strtok(line, " ");
        for (int i = 0; i < 5; ++i) token = strtok(NULL, " ");
        monkes[m].monke_true = atoi(token);

        /* 4.2 false */
        getline(&line, &bytes, file);
        token = strtok(line, " ");
        for (int i = 0; i < 5; ++i) token = strtok(NULL, " ");
        monkes[m].monke_false = atoi(token);

        /* Flush newline character */
        getline(&line, &bytes, file);
        
        monkes[m].next = 0;
    }

    free(line);
    fclose(file);

    return m;
}


int cmp(const void *a, const void *b)
{
    return *(long *) b - *(long *) a;
}
