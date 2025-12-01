/*  Advent of Code: Day 10:
    Hill Climbing Algorithm

    Dijkstra!

    Author: Veikka Immonen @imveikka */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* map size */
#define R 43
#define C 72
#define INF 1 << 30
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))


int locate(char, char **);
int min_vertex(int *, int *);
int search_silver(char **, int, int);
void update_silver(char **, int *, int);
int search_gold(char **, int , char);
void update_gold(char **, int *, int);


int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    size_t bytes = 0, read;
    char *line, **map = calloc(R, sizeof *map);

    /* indexing starts at 1 so all edges has null */
    *map = calloc(C, sizeof **map);
    for (char **row = map+1; (read = getline(&line, &bytes, file)) != -1; ++row)
    {
        *row = calloc(C, sizeof **row);
        strncpy(*row+1, line, read-1);
    }
    map[R-1] = calloc(C, sizeof **map);

    int start = locate('S', map), end = locate('E', map);

    int silver = search_silver(map, start, end),
        gold = search_gold(map, end, 'a');

    printf("Silver: %d\n", silver);
    printf("Gold: %d\n", gold);


    for (char **row = map; row != map + R - 1; ++row) free(*row);
    free(map);
    free(line);
    return 0;
}


int locate(char c, char **map)
{
    for (int i = 1; i < R-1; ++i)
    {
        for (int j = 1; j < C-1; ++j)
        {
            if (map[i][j] == c)
            {
                map[i][j] = c == 'S' ? 'a' : 'z';   
                return i * C + j;
            }
        }
    }
    return 0;
}


int min_vertex(int *distance, int *visited)
{
    int min = INF, location = 0;
    for (int i = 0; i < R * C; ++i)
    {
        if (visited[i] == 0 && distance[i] < min)
        {
            location = i;
            min = distance[i];
        }
    }
    return location;
}


int search_silver(char **map, int start, int end)
{
    int distance[R * C], visited[R * C] = {0}, min_loc;

    for (int i = 0; i < R * C; ++i) distance[i] = INF;
    distance[start] = 0;

    while (visited[end] == 0)
    {   
        min_loc = min_vertex(distance, visited);
        if (min_loc == 0 || min_loc == end) break;
        visited[min_loc] = 1;
        update_silver(map, distance, min_loc);
    }

    return distance[end];
}


void update_silver(char **map, int *distance, int location)
{
    int x = location % C;
    int y = (location - x) / C;


    /* Check surroundings clockwise */
    if (map[y-1][x] && (map[y-1][x] - map[y][x] < 2))
        distance[(y-1) * C + x] = MIN(distance[location] + 1, distance[(y-1) * C + x]);
    
    if (map[y][x+1] && (map[y][x+1] - map[y][x] < 2))
        distance[y * C + x+1] = MIN(distance[location] + 1, distance[y * C + x+1]);

    if (map[y+1][x] && (map[y+1][x] - map[y][x] < 2))
        distance[(y+1) * C + x] = MIN(distance[location] + 1, distance[(y+1) * C + x]);

    if (map[y][x-1] && (map[y][x-1] - map[y][x] < 2))
        distance[y * C + x-1] = MIN(distance[location] + 1, distance[y * C + x-1]);
}


int search_gold(char **map, int start, char end)
{
    int distance[R * C], visited[R * C] = {0}, min_loc, x, y;

    for (int i = 0; i < R * C; ++i) distance[i] = INF;
    distance[start] = 0;

    while (1)
    {   
        min_loc = min_vertex(distance, visited);
        x = min_loc % C;
        y = (min_loc - x) / C;

        if (min_loc == 0 || (map[y][x] == end && (x == 1 || x == 70 || y == 1 || y == 42))) break;
        visited[min_loc] = 1;
        update_gold(map, distance, min_loc);
    }

    return distance[min_loc];
}


void update_gold(char **map, int *distance, int location)
{
    int x = location % C;
    int y = (location - x) / C;

    /* Check surroundings clockwise */
    if (map[y-1][x] && (map[y-1][x] - map[y][x] > -2))
        distance[(y-1) * C + x] = MIN(distance[location] + 1, distance[(y-1) * C + x]);
    
    if (map[y][x+1] && (map[y][x+1] - map[y][x] > -2))
        distance[y * C + x+1] = MIN(distance[location] + 1, distance[y * C + x+1]);

    if (map[y+1][x] && (map[y+1][x] - map[y][x] > -2))
        distance[(y+1) * C + x] = MIN(distance[location] + 1, distance[(y+1) * C + x]);

    if (map[y][x-1] && (map[y][x-1] - map[y][x] > -2))
        distance[y * C + x-1] = MIN(distance[location] + 1, distance[y * C + x-1]);
}
