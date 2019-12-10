//
// Created by Once on 2019/12/4.
//

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph *graph_new(int n){
    if(n < 3){
        perror("n is too small");
        return NULL;
    }
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    if(!graph){
        perror("alloc for graph error");
        return NULL;
    }
    graph->n = n;
    graph->matrix = (int*)malloc(sizeof(int) * n * n);
    if(!graph->matrix){
        perror("alloc for matrix error");
        free(graph);
        return NULL;
    }
    graph->d = (int*)malloc(sizeof(int) * n * n);
    if(!graph->d){
        perror("alloc for distance error");
        free(graph->matrix);
        free(graph);
        return NULL;
    }
    graph->path = (int*)malloc(sizeof(int) * n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            graph->matrix[i * n + j] = INT_MAX;
            graph->matrix[j * n + i] = INT_MAX;
            graph->d[i * n + j] = INT_MAX;
            graph->d[j * n + i] = INT_MAX;
            graph->path[i * n + j] = INT_MIN;
            graph->path[j * n + i] = INT_MIN;
        }
    }
    return graph;
}

void graph_add(Graph *graph, int u, int v, int w){
    if(graph == NULL || u < 0 || v < 0)
        return;
    graph->matrix[u * graph->n + v] = w;
    graph->d[u * graph->n + v] = w;
    graph->path[u * graph->n + v] = v;
}

void graph_add_all(Graph *graph, Edge edges[], int n){
    if(graph == NULL || edges == NULL || n < 3)
        return;
    int u;
    int v;
    for (int i = 0; i < n; ++i) {
        u = edges[i].u;
        v = edges[i].v;
        graph->matrix[u * graph->n + v] = edges[i].w;
        graph->d[u * graph->n + v] = edges[i].w;
        graph->path[u * graph->n + v] = v;
    }
}

void graph_shortest_path_of_pair(Graph *graph){
    if(graph == NULL)
        return;
    int n = graph->n;
    for (int m = 0; m < n; ++m) {
        graph->d[m * n + m] = 0;
        graph->path[m * n + m] = m;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if(graph->d[i * n + k] == INT_MAX || graph->d[k * n + j] == INT_MAX)
                    continue;
                if(graph->d[i * n + k] + graph->d[k * n + j] < graph->d[i * n + j]){
                    graph->d[i * n + j] = graph->d[i * n + k] + graph->d[k * n + j];
                    graph->path[i * n + j] = k;
                }
            }
        }
    }
}

static void print_path(Graph *graph, int u, int v){
    if(u == v)
        return;
    if(graph->path[u * graph->n + v] == INT_MIN){
//        printf("No Path Found.\n");
        return;
    }
    int k = graph->path[u * graph->n + v];
    if(k == v){
        return;
    }
    printf("(%d %d %d) ", u, k, v);
    print_path(graph, u, k);
    print_path(graph, k, v);
}

void graph_print_path(Graph *graph, int u, int v){
    if(graph == NULL)
        return;
    print_path(graph, u, v);
    printf("\n");
}

void graph_clear(Graph *graph){
    if(graph == NULL)
        return;
    free(graph->matrix);
    free(graph->path);
    free(graph->d);
    free(graph);
}