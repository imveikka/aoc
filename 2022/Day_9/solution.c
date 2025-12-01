/*  Advent of Code: Day 8:
    Rope Bridge

    I'm back.

    Author: Veikka Immonen @imveikka */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N (1 << 10)
#define LEN 10
#define NORM2(x1, y1, x2, y2) ((x1) - (x2))*((x1) - (x2)) + ((y1) - (y2))*((y1) - (y2))
#define SIGN(a) (a) < 0 ? -1 : (a) > 0 ? 1 : 0


void update(int*, int);


int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    size_t bytes = 0, read;
    char *move = NULL, dir;
    int silver = 0, gold = 0, steps;

    /* NxN map */
    int *map = calloc(N * N, sizeof *map); 

    /* Rope, each point correspond one knot */
    int *rope = calloc(LEN * 2, sizeof *rope);
    for (int i = 0; i < LEN * 2; ++i) rope[i] = N >> 1;

    while ((read = getline(&move, &bytes, file)) != -1)
    {
        sscanf(move, "%c %d", &dir, &steps);
        for (int step = 0; step < steps; ++step)
        {
            rope[0] += (dir == 'R') - (dir == 'L');
            rope[1] += (dir == 'U') - (dir == 'D');
            for (int knot = 1; knot < LEN; ++knot) update(rope, knot);

            /* Gold */
            if ((map[rope[2] * N + rope[3]]) % 2 == 0)
            {
                silver++;
                map[rope[2] * N + rope[3]]++;
            }

            /* Silver */
            if (map[rope[18] * N + rope[19]] < 2)
            {
                gold++;
                map[rope[18] * N + rope[19]] += 2;
            }
        }
    }
    printf("Silver: %d\n", silver);
    printf("Gold: %d\n", gold);

    free(map);
    free(rope);
    free(move);
}


void update(int *rope, int knot)
{
    /* for better understanding */
    int *h_x = &rope[2 * (knot - 1)],
        *h_y = &rope[2 * (knot - 1) + 1],
        *t_x = &rope[2 * knot],
        *t_y = &rope[2 * knot + 1];

    if (NORM2(*h_x, 0, *t_x, 0) == 4)
    {
        *t_x += (*h_x - *t_x) / 2;
        *t_y += SIGN(*h_y - *t_y);
    }
    else if (NORM2(0, *h_y, 0, *t_y) == 4)
    {
        *t_y += (*h_y - *t_y) / 2;
        *t_x += SIGN(*h_x - *t_x);
    }
}
