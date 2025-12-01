/*  Advent of Code: Day 8:
    Treetop Tree House

    Very readable and easily expandable.
    Oh yeah!

    Author: Veikka Immonen @imveikka*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 1 << 14
#define MAX(a, b) (a) > (b) ? (a) : (b)


int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    char **T = calloc(N, sizeof *T), *line = NULL, **temp; /* Forest map */
    size_t bytes = 0, read;

    int M = 0; /* Total rows */

    /* Read data */
    for (temp = T; (read = getline(&line, &bytes, file)) != -1; temp++, M++)
    {
        *temp = calloc(read, sizeof **temp);
        strncpy(*temp, line, read - 1);
    }

    /* Variables */
    int silver = 0;
    int gold = 0, gold_candidate;
    int m_w, m_e, m_n, m_s; /* Current maximums from each side */
    int dist;

    /* Crunch numbers */
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            m_w = m_e = m_n = m_s = -1;
            gold_candidate = 1;

            /*  Get max tree from each side of tree ij
                and evaluate its distance */

            dist = 0;
            for (int k = j - 1; k >= 0; --k)
            {
                dist++;
                m_w = MAX(m_w, T[i][k]);
                if (m_w >= T[i][j]) break;
            }
            gold_candidate *= dist;

            dist = 0;
            for (int k = j + 1; k < M; ++k)
            {
                dist++;
                m_e = MAX(m_e, T[i][k]);
                if (m_e >= T[i][j]) break;
            }
            gold_candidate *= dist;

            dist = 0;
            for (int k = i - 1; k >= 0; --k)
            {
                dist++;
                m_n = MAX(m_n, T[k][j]);
                if (m_n >= T[i][j]) break;
            }
            gold_candidate *= dist;

            dist = 0;
            for (int k = i + 1; k < M; ++k)
            {
                dist++;
                m_s = MAX(m_s, T[k][j]);
                if (m_s >= T[i][j]) break;
            }
            gold_candidate *= dist;

            silver += (m_w < T[i][j]) || (m_e < T[i][j]) ||
                      (m_n < T[i][j]) || (m_s < T[i][j]);

            gold = MAX(gold, gold_candidate);
        }
    }

    printf("Silver: %d\n", silver);
    printf("Gold: %d\n", gold);

    /* Kindly give memory back */
    for (temp = T; *temp; temp++) free(*temp);
    free(T);
    free(line);
    fclose(file);

    return 0;
}
