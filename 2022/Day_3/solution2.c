/*  Advent of Code: Day 3, Problem 2:
    Rearrange rucksacks to groups of 3

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

    char *line1 = NULL, *line2 = NULL, *line3 = NULL, *foo;
    size_t bytes1 = 0, bytes2 = 0, bytes3 = 0;

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    int result2 = 0;

    while (getline(&line1, &bytes1, file) != -1) {
        foo = line1;
        getline(&line2, &bytes2, file);
        getline(&line3, &bytes3, file);
        while (*foo != '\n') {
            if (strchr(line2, *foo) && strchr(line3, *foo)) {
                result2 += CHR_EVAL(*foo);
                break;
            }
            foo++;
        }
    }

    printf("Sum of priorities is %d\n", result2);

    fclose(file);
    free(line1);
    free(line2);
    free(line3);
    return 0;
}
