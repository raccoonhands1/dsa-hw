#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 1024

int readFile(FILE *f, char ***arr) {
    if (f == NULL || arr == NULL) return -1;

    int cnt = 0;
    char buf[MAX_LEN];
    *arr = NULL;

    while (fgets(buf, sizeof(buf), f)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';

        char **tmp = realloc(*arr, (cnt + 1) * sizeof(char *));
        if (tmp == NULL) {
            for (int i = 0; i < cnt; i++) free((*arr)[i]);
            free(*arr);
            *arr = NULL;
            return -1;
        }
        *arr = tmp;

        (*arr)[cnt] = malloc(strlen(buf) + 1);
        if ((*arr)[cnt] == NULL) {
            for (int i = 0; i < cnt; i++) free((*arr)[i]);
            free(*arr);
            *arr = NULL;
            return -1;
        }
        strcpy((*arr)[cnt], buf);
        cnt++;
    }
    return cnt;
}

void freeArr(char **arr, int cnt) {
    if (arr != NULL) {
        for (int i = 0; i < cnt; i++) free(arr[i]);
        free(arr);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
        return 1;
    }

    char **lines = NULL;
    int cnt = readFile(in, &lines);
    fclose(in);

    if (cnt == -1) {
        fprintf(stderr, "Error: Failed to read input\n");
        return 1;
    }

    int n = atoi(lines[0]);
    if (n <= 0) {
        fprintf(stderr, "Error: Invalid graph size\n");
        freeArr(lines, cnt);
        return 1;
    }

    Graph g = newGraph(n);

    int idx = 1;
    while (idx < cnt && strcmp(lines[idx], "0 0") != 0) {
        int u, v;
        if (sscanf(lines[idx], "%d %d", &u, &v) != 2) {
            fprintf(stderr, "Error: Invalid edge at line %d\n", idx + 1);
            freeGraph(&g);
            freeArr(lines, cnt);
            return 1;
        }
        addEdge(g, u, v);
        idx++;
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Error: Cannot open %s\n", argv[2]);
        freeGraph(&g);
        freeArr(lines, cnt);
        return 1;
    }

    printGraph(out, g);

    idx++;
    List lst = newList();
    while (idx < cnt && strcmp(lines[idx], "0 0") != 0) {
        int s, t;
        if (sscanf(lines[idx], "%d %d", &s, &t) != 2) {
            fprintf(stderr, "Error: Invalid query at line %d\n", idx + 1);
            freeList(&lst);
            freeGraph(&g);
            freeArr(lines, cnt);
            fclose(out);
            return 1;
        }

        BFS(g, s);
        int d = getDist(g, t);
        fprintf(out, "\nThe distance from %d to %d is ", s, t);
        if (d == INF) fprintf(out, "infinity\n");
        else fprintf(out, "%d\n", d);

        if (d != INF) {
            fprintf(out, "A shortest %d-%d path is: ", s, t);
            getPath(lst, g, t);
            printList(out, lst);
            fprintf(out, "\n");
        } else {
            fprintf(out, "No %d-%d path exists\n", s, t);
        }

        clear(lst);
        idx++;
    }

    fclose(out);
    freeList(&lst);
    freeGraph(&g);
    freeArr(lines, cnt);

    return 0;
}