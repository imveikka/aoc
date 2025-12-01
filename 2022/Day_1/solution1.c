/*  Advent of Code: Day 1, Problem 1:
    Find the elf with most calories carried.

    Author: Veikka Immonen */


#include <stdio.h>
#include <stdlib.h>


#define MAX(a, b) (a) > (b) ? (a) : (b)


/*  All code is in main. The file name is given as
    command line argument. Has simle error handling.
    All output is printed to stdout. */
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    /* Variables to getline */
    char * line = NULL;
    size_t bytes = 0;
    size_t read; 

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    int max = 0;
    int calories = 0;

    /* getline returns -1 on failure/EOF */
    while ((read = getline(&line, &bytes, file)) != -1) {
        if (read == 1) {
            /* line contains '\n' only */
            max = MAX(max, calories);
            calories = 0;
        }
        else calories += atoi(line);
    }

    fclose(file);

    /*  After getline failure line is freed and set to NULL
        which happens in this case. How ever it's good practice
        to free memory manually just in case. */
    free(line);

    printf("Max elf is carrying %d calories.\n", max);
    return 0;
}