//
// Created by Once on 2019/12/3.
//

#include "optree.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Optree *optree_new(){
    Optree *optree = (Optree*)malloc(sizeof(Optree));
    if(!optree){
        perror("alloc for opt tree error");
        return NULL;
    }
    optree->n = optree->length = 0;
    optree->list = optree->root = NULL;
    return optree;
}

int optree_is_empty(Optree *optree){
    if(optree == NULL)
        return 1;
    return optree->n == 0;
}

void optree_add(Optree *optree, int key, double p){
    if(optree == NULL)
        return;
    if(optree->n == optree->length){
        optree->length += 16;
        optree->list = (ONode*)realloc(optree->list, sizeof(ONode) * optree->length);
    }
    optree->list[optree->n].key = key;
    optree->list[optree->n].p = p;
    optree->list[optree->n].left = optree->list[optree->n].right = NULL;
    optree->n++;
}

// add all data once
void optree_add_all(Optree *optree, ONode nodes[], int size){
    if(optree == NULL || nodes == NULL || size < 3)
        return;
    optree->length = size;
    optree->list = (ONode*)malloc(sizeof(ONode) * size);
    for (int i = 0; i < size; ++i) {
        optree->list[i].key = nodes[i].key;
        optree->list[i].p = nodes[i].p;
        optree->list[i].left = optree->list[i].right = NULL;
    }
    optree->n = size;
}

static int compare(const void *a, const void *b){
    return ((ONode*)a)->p > ((ONode*)b)->p;
}

static ONode *build_tree(Optree *optree, int *s, int i, int j){
    if(i - 1 == j){
        if(i < optree->n)
            return &optree->list[i];
        else
            return &optree->list[j];
    }
    if(i == j)
        return &optree->list[i];
    int k = s[i * optree->n + j];
    ONode *left = i != k ? build_tree(optree, s, i, k - 1) : NULL;
    ONode *right = j !=k ? build_tree(optree, s, k + 1, j) : NULL;
    ONode *root = &optree->list[k];
    root->left = root != left ? left : NULL;
    root->right = root != right ? right : NULL;
    return root;
}

// core algorithm for creating optimal binary search tree
void optree_build(Optree *optree){
    if(optree == NULL || optree->n == 0)
        return;
//    qsort(optree->list, optree->n, sizeof(ONode), compare);
    int n = optree->n;
    double m[n * n];
    int s[optree->n * optree->n];
    for (int i = 0; i < optree->n; ++i) {
        m[i * n + i] = optree->list[i].p;
    }
    int j;
    double psum;
    for (int l = 1; l < optree->n; ++l) {
        for (int i = 0; i < optree->n - l; ++i) {
            j = i + l;
            m[i * n + j] = INT_MAX;
            psum = 0;
            for (int x = i; x <= j; ++x) {
                psum += optree->list[x].p;
            }
            for (int k = i; k <= j; ++k) {
                double q = m[i * n + (k - 1)] + m[(k + 1) * n + j] + psum;
                if(m[i * n + j] > q){
                    m[i * n + j] = q;
                    s[i * n + j] = k;
                }
            }
        }
    }

    optree->root = build_tree(optree, s, 0 , optree->n - 1);
}

void optree_traverse(Optree *optree){
    if(optree == NULL || optree->n == 0 || optree->root == NULL)
        return;
    Queue *queue = queue_new();
    queue_push(queue, optree->root);
    ONode *node;
    while(!queue_is_empty(queue)){
        node = queue_pop(queue);
        printf("[%d: %.2f] ", node->key, node->p);
        if(node->left != NULL)
            queue_push(queue, node->left);
        if(node->right != NULL)
            queue_push(queue, node->right);
    }
}

static void _free_node(ONode *root){
    if(root == NULL)
        return;
    _free_node(root->left);
    _free_node(root->right);
    free(root);
}

void optree_clear(Optree *optree){
    if(optree == NULL)
        return;
    if(optree->list != NULL)
        free(optree->list);
    if(optree->root != NULL)
        _free_node(optree->root);
    free(optree);
}