/*  Advent of Code: Day 10:
    Cathode-Ray Tube

    Compiling is less painful if file name is not so long...

    Author: Veikka Immonen @imveikka */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ABS(a) ((a) < 0 ? -(a) : (a))


int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    size_t bytes = 0, read;
    char *executable = NULL, command[5] = {0};
    int silver = 0, gold = 0, number, X = 1, time;

    printf("Gold message:\n");

    for (int cycle = 1; (read = getline(&executable, &bytes, file)) != -1; ++cycle)
    {
        printf("%c", ABS(cycle % 40 - (X+1)) < 2 ? '#' : ' ');
        if (cycle % 40 == 0) printf("\n");

        if ((cycle - 20) % 40 == 0) silver += cycle*X;

        if (sscanf(executable, "%s %d", command, &number) == 1) continue;
        
        /* Additional cycle to addx */
        cycle++;

        printf("%c", ABS(cycle % 40 - (X+1)) < 2 ? '#' : ' ');
        if (cycle % 40 == 0) printf("\n");

        if ((cycle - 20) % 40 == 0) silver += cycle*X;
        X += number; 
    }

    printf("\nSilver: %d\n", silver);
    free(executable);
    return 0;
}
