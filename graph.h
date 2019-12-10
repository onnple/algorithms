//
// Created by Once on 2019/12/4.
//

#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

typedef struct edge{
    int u;
    int v;
    int w;
} Edge;

// 默认为有向图, a directed graph
// vertices: 0, 1, ..., n-2, n-1
typedef struct graph{
    int n;
    int *matrix;
    int *path;
    int *d;
} Graph;

extern Graph *graph_new(int n);
extern void graph_add(Graph *graph, int u, int v, int w);
extern void graph_add_all(Graph *graph, Edge edges[], int n);
extern void graph_shortest_path_of_pair(Graph *graph);
extern void graph_print_path(Graph *graph, int u, int v);
extern void graph_clear(Graph *graph);


#endif //ALGORITHMS_GRAPH_H
