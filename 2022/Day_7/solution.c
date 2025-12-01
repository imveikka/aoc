/*  Advent of Code: Day 7:
    No Space Left On Device

    What...

    Author: Veikka Immonen */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 32


typedef struct file {
    char name[N];
    long size;
} file;


typedef struct dir {
    char name[N];
    struct dir *host;
    struct dir *dirs[N];
    struct file files[N];
    long n_dirs;
    long n_files;
} dir;


dir *new_dir(char *, dir *);
size_t ls(FILE *, char *, size_t *, dir *);
dir *cd(dir *, char *);
long traverse_s(dir *, long, long *);
long traverse_g(dir *, long *, long);
void free_system(dir *);


long main(long argc, char *argv[]) {

    if (argc < 2) {
        printf("Give filename\n");
        return 0;
    }

    FILE * pfile;
    if ((pfile = fopen(argv[1], "r")) == NULL) {
        printf("File not found\n");
        return 0;
    }

    char *line = NULL;
    size_t bytes = 0;
    size_t read; 

    /* Create root */
    dir *host = new_dir("/", NULL);
    dir *root = host;

    read = getline(&line, &bytes, pfile);
    read = getline(&line, &bytes, pfile);
    
    /* Reads file line by line and check what to do next */
    while (read != -1) {
        if (line [2] == 'c') {
            host = cd(host, line);
            read = getline(&line, &bytes, pfile);
        }
        else {
            read = ls(pfile, line, &bytes, host);
        }
    }

    /* Get solutions */

    long silver = 0;
    long total = traverse_s(root, 0, &silver);
    long gold = total;
    long needed = 30000000 - (70000000 - total);

    /* Replace needed for bigboy test */
    long bigboy = 700000000 - (3000000000  - total);
                            
                          /* here */
    traverse_g(root, &gold, bigboy);

    printf("Total: %ld\n", total);
    printf("Silver: %ld\n", silver);
    printf("Gold: %ld\n", gold);

    /* I hope this will do */
    free_system(root);
    
    free(line);

    return 0;
}


/* Allocates new directory*/
dir *new_dir(char *name, dir *host) {
    dir *new = malloc(sizeof(dir));
    strcpy(new->name, name);
    new->host = host;
    new->n_dirs = 0;
    new->n_files = 0;
    if (host) host->n_dirs++;
    return new;
}


/*  Collects the content of the directory host.
    Continues file reading until new command */
size_t ls(FILE *pfile, char *line, size_t *bytes, dir *host) {

    char arg1[N] = {0}, arg2[N] = {0};
    size_t read = getline(&line, bytes, pfile);

    while (line[0] != '$' && read != -1) {
        sscanf(line, "%s %s", arg1, arg2);
        if (arg1[0] == 'd') host->dirs[host->n_dirs] = new_dir(arg2, host);
        else {
            host->files[host->n_files].size = atoi(arg1);
            strcpy(host->files[host->n_files].name, arg2);
            host->n_files++;
        }
        read = getline(&line, bytes, pfile);
    }
    return read;
}


/* Checks the next directory to browse */
dir *cd(dir *host, char *line) {
    
    char arg[16];
    sscanf(line, "%*c %*s %s", arg);

    if (strcmp(arg, "..") == 0) return host->host;
    
    for (long i = 0; i < host->n_dirs; ++i) {
        if (strcmp(arg, host->dirs[i]->name) == 0) return host->dirs[i];
    }

    return host;
}


/* Solution 1 */
long traverse_s(dir *host, long depth, long *silver) {
    long sum = 0;
    for (long i = 0; i < host->n_files; ++i) sum += host->files[i].size;
    for (long i = 0; i < host->n_dirs; ++i) sum += traverse_s(host->dirs[i], depth + 1, silver);
    if (sum <= 100000) *silver += sum;
    return sum;
}


/* Solution 2 */
long traverse_g(dir *host, long *gold, long needed) {
    long new = 0;
    for (long i = 0; i < host->n_files; ++i) new += host->files[i].size;
    for (long i = 0; i < host->n_dirs; ++i) new += traverse_g(host->dirs[i], gold, needed);
    *gold = (new > needed && new < *gold) ? new: *gold;
    return new;
}


/* Prevents most memory leaks */
void free_system(dir *host) {
    for (long i = 0; i < host->n_dirs; ++i) free_system(host->dirs[i]);
    free(host);
}
