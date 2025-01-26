#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
    List *adj;       // Array of Lists to store adjacency lists
    int *color;      // Array to store colors of vertices
    int *parent;     // Array to store parents of vertices
    int *dist;       // Array to store distances from the source
    int order;       // Number of vertices
    int size;        // Number of edges
    int source;      // Source vertex for BFS
} GraphObj;

typedef GraphObj* Graph;

Graph newGraph(int n) {
    Graph g = malloc(sizeof(GraphObj));
    if (g == NULL) {
        fprintf(stderr, "Graph Error: malloc failed\n");
        exit(1);
    }
    g->adj = malloc((n + 1) * sizeof(List));
    g->color = malloc((n + 1) * sizeof(int));
    g->parent = malloc((n + 1) * sizeof(int));
    g->dist = malloc((n + 1) * sizeof(int));
    if (g->adj == NULL || g->color == NULL || g->parent == NULL || g->dist == NULL) {
        fprintf(stderr, "Graph Error: malloc failed\n");
        free(g);
        exit(1);
    }
    g->order = n;
    g->size = 0;
    g->source = NIL;
    for (int i = 0; i <= n; i++) {
        g->adj[i] = newList();
        g->color[i] = 0;
        g->parent[i] = NIL;
        g->dist[i] = INF;
    }
    return g;
}

void freeGraph(Graph* g) {
    if (g != NULL && *g != NULL) {
        for (int i = 0; i <= (*g)->order; i++) {
            freeList(&((*g)->adj[i]));
        }
        free((*g)->adj);
        free((*g)->color);
        free((*g)->parent);
        free((*g)->dist);
        free(*g);
        *g = NULL;
    }
}

int getOrder(Graph g) {
    return g->order;
}

int getSize(Graph g) {
    return g->size;
}

int getSource(Graph g) {
    return g->source;
}

int getParent(Graph g, int u) {
    if (u < 1 || u > g->order) {
        fprintf(stderr, "Graph Error: invalid vertex\n");
        exit(1);
    }
    return g->parent[u];
}

int getDist(Graph g, int u) {
    if (u < 1 || u > g->order) {
        fprintf(stderr, "Graph Error: invalid vertex\n");
        exit(1);
    }
    return g->dist[u];
}

void getPath(List lst, Graph g, int u) {
    if (g->source == NIL) {
        fprintf(stderr, "Graph Error: BFS not called\n");
        exit(1);
    }
    if (u < 1 || u > g->order) {
        fprintf(stderr, "Graph Error: invalid vertex\n");
        exit(1);
    }
    if (u == g->source) {
        append(lst, u);
    } else if (g->parent[u] == NIL) {
        append(lst, NIL);
    } else {
        getPath(lst, g, g->parent[u]);
        append(lst, u);
    }
}

void makeNull(Graph g) {
    if (g == NULL) {
        fprintf(stderr, "Graph Error: NULL graph\n");
        exit(1);
    }
    for (int i = 1; i <= g->order; i++) {
        clear(g->adj[i]);
    }
    g->size = 0;
    g->source = NIL;
}

void addEdge(Graph g, int u, int v) {
    if (g == NULL) {
        fprintf(stderr, "Graph Error: NULL graph\n");
        exit(1);
    }
    if (u < 1 || u > g->order || v < 1 || v > g->order) {
        fprintf(stderr, "Graph Error: invalid vertices\n");
        exit(1);
    }
    moveFront(g->adj[u]);
    while (index(g->adj[u]) != -1) {
        if (get(g->adj[u]) > v) {
            insertBefore(g->adj[u], v);
            break;
        }
        moveNext(g->adj[u]);
    }
    if (index(g->adj[u]) == -1) {
        append(g->adj[u], v);
    }
    moveFront(g->adj[v]);
    while (index(g->adj[v]) != -1) {
        if (get(g->adj[v]) > u) {
            insertBefore(g->adj[v], u);
            break;
        }
        moveNext(g->adj[v]);
    }
    if (index(g->adj[v]) == -1) {
        append(g->adj[v], u);
    }
    g->size++;
}

void addArc(Graph g, int u, int v) {
    if (g == NULL) {
        fprintf(stderr, "Graph Error: NULL graph\n");
        exit(1);
    }
    if (u < 1 || u > g->order || v < 1 || v > g->order) {
        fprintf(stderr, "Graph Error: invalid vertices\n");
        exit(1);
    }
    moveFront(g->adj[u]);
    while (index(g->adj[u]) != -1) {
        if (get(g->adj[u]) > v) {
            insertBefore(g->adj[u], v);
            break;
        }
        moveNext(g->adj[u]);
    }
    if (index(g->adj[u]) == -1) {
        append(g->adj[u], v);
    }
    g->size++;
}

void BFS(Graph g, int s) {
    if (g == NULL) {
        fprintf(stderr, "Graph Error: NULL graph\n");
        exit(1);
    }
    if (s < 1 || s > g->order) {
        fprintf(stderr, "Graph Error: invalid source\n");
        exit(1);
    }
    for (int i = 1; i <= g->order; i++) {
        g->color[i] = 0;
        g->dist[i] = INF;
        g->parent[i] = NIL;
    }
    g->source = s;
    g->color[s] = 1;
    g->dist[s] = 0;
    g->parent[s] = NIL;
    List queue = newList();
    append(queue, s);
    while (length(queue) > 0) {
        int u = front(queue);
        deleteFront(queue);
        moveFront(g->adj[u]);
        while (index(g->adj[u]) != -1) {
            int v = get(g->adj[u]);
            if (g->color[v] == 0) {
                g->color[v] = 1;
                g->dist[v] = g->dist[u] + 1;
                g->parent[v] = u;
                append(queue, v);
            }
            moveNext(g->adj[u]);
        }
        g->color[u] = 2;
    }
    freeList(&queue);
}

void printGraph(FILE* out, Graph g) {
    if (g == NULL) {
        fprintf(stderr, "Graph Error: NULL graph\n");
        exit(1);
    }
    for (int i = 1; i <= g->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, g->adj[i]);
        fprintf(out, "\n");
    }
}