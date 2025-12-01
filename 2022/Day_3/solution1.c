/*  Advent of Code: Day 3, Problem 1:
    Rearrange rucksacks

    Author: Veikka Immonen */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Very unsafe char evaluation macro */
#define CHR_EVAL(c) (c) < 91 ? (c) - 38 : (c) - 96


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    char *line = NULL;
    size_t bytes = 0;
    size_t read; 

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    int result1 = 0;
    char *comp1, *comp2;

    while ((read = getline(&line, &bytes, file)) != -1) {
        comp1 = line;
        comp2 = line + (read / 2);
        while (comp1 < comp2) {
            /* Find common char using strchr */
            if ((strchr(comp2, *comp1)) != NULL) {
                result1 += CHR_EVAL(*comp1);
                break;
            }
            comp1++;
        } 
    }

    printf("Sum of priorities is %d\n", result1);

    fclose(file);
    free(line);
    return 0;
}
