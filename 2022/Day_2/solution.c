/*  Advent of Code: Day 2:
    Calculate total score of RPS-event

    Author: Veikka Immonen */


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    FILE * file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    char opponent, you;    
    int result, total1 = 0, total2 = 0;

    while (fscanf(file, "%c %c\n", &opponent, &you) != -1) {
        result = you - opponent;

        /* First problem */
        total1 += (you - 'W');
        total1 += ((result == 23) * 3 + ((result == 24) || (result == 21)) * 6);

        /* Second problem (could not find any cool patterns) */
        if (you == 'X') 
            total2 += opponent == 'A' ? 3 : opponent == 'B' ? 1 : 2;
        else if (you == 'Y')
            total2 += opponent - '=';
        else
            total2 += opponent == 'A' ? 8 : opponent == 'B' ? 9 : 7; 
    }
    
    printf("1st score is %d\n", total1);
    printf("2nd score is %d\n", total2);

    fclose(file);
    return 0;
}
