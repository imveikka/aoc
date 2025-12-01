/*  Advent of Code: Day 4:
    Camp Cleanup

    Author: Veikka Immonen */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    char *line = NULL;
    size_t bytes = 0;
    size_t read;

    int result1 = 0, result2 = 0, 
    a1, b1, a2, b2; /* bounds */

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    while ((read = getline(&line, &bytes, file)) != -1) {
        sscanf(line, "%d-%d,%d-%d", &a1, &b1, &a2, &b2);

        /* 1st problem */
        if ((a1 >= a2) && (b1 <= b2)) result1++;
        else if ((a1 <= a2) && (b1 >= b2)) result1++;
    
        /* 2nd problem */
        result2 += ((b1 >= a2) && (b2 >= a1));
    }

    printf("Assignments that fully contains the other: %d\n", result1);
    printf("Assignments that overlaps at all: %d\n", result2);

    fclose(file);
    free(line);
    return 0;
}
