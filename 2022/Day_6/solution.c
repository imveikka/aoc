/*  Advent of Code: Day 6:
    Tuning Trouble

    Big boy in the house!

    Author: Veikka Immonen */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 1 << 27

/*  Check if any duplicates occurs in string
    lenght of n. Returns 1 if yes, 0 if no. */
int strndub(char *str, int n) {
    short table[26] = {0};
    for (int i = 0; str[i], i < n; ++i) {
        if (table[str[i]-97] == 1) return 1;
        table[str[i]-97]++;
    }
    return 0;
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    char *foo = calloc(N, 1);
    int S = 4, G = 14;

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }
    fscanf(file, "%s", foo);
    fclose(file);

    /* Solution 1 */
    for (int i = 0; foo[i]; ++i) {
        if (strndub(foo+i, S) == 0) {
            printf("Silver: %d\n", i + S);
            break;
        }
    }

    /* Solution 2 */
    for (int i = 0; foo[i]; ++i) {
        if (strndub(foo+i, G) == 0) {
            printf("Gold: %d\n", i + G);
            break;
        }
    }
    
    free(foo);
    
    return 0;
}
