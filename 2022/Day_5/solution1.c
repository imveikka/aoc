/*  Advent of Code: Day 5, Problem 1:
    Supply Stacks

    I slightly start to regret that I'm doing this in C

    Author: Veikka Immonen */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*  Please note that this solution may not work on any input.
    Only when theres 9 stack in total. */
#define N 9


#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)


typedef struct Stack {
    char stack[128];
    int top;
} Stack;


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    Stack stacks[N];
    for (int i = 0; i < N; ++i) stacks[i].top = -1;

    char *line = NULL;
    size_t bytes = 0;
    size_t read;

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    /* Constructing stacks */
    char c1, c2, c3, c4; 
    int i = 0;
    fscanf(file, "%c%c%c%c", &c1, &c2, &c3, &c4);
    while (c2 != '1') {
        i = i % N;
        if (c2 != ' ') stacks[i].stack[++stacks[i].top] = c2;
        fscanf(file, "%c%c%c%c", &c1, &c2, &c3, &c4);
        ++i;
    }

    /* Still constructing stacks (they are reversed)*/
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < (stacks[i].top+1) / 2; ++j) {
            SWAP(stacks[i].stack[j], stacks[i].stack[stacks[i].top - j], char);
        }
    }

    /* Read two line out of the way */
    getline(&line, &bytes, file);
    getline(&line, &bytes, file);

    /* The real stuff */
    int how_many, from, to;
    while(getline(&line, &bytes, file) != -1) {
        sscanf(line, "%*s %d%*s %d%*s %d", &how_many, &from, &to);
        for (int i = 0; i < how_many; ++i) {
            stacks[to-1].stack[++stacks[to-1].top] = stacks[from-1].stack[stacks[from-1].top--];
        }
    }

    printf("The top of each stack: ");
    for (int i = 0; i < N; ++i) printf("%c", stacks[i].stack[stacks[i].top]);
    printf("\n");

    fclose(file);
    free(line);
    return 0;
}
