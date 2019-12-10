//
// Created by Once on 2019/11/26.
//

#include "binpacking.h"
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

static int q_compare(const void *a, const void *b){
    int *a_ = (int*)a;
    int *b_ = (int*)b;
    return *a_ < *b_;
}

static int compare(void *a, void *b){
    Box *a_ = (Box*)a;
    Box *b_ = (Box*)b;
    return a_->left > b_->left;
}

int binpacking(double capacity, Item items[], int n){
    if(capacity < 0 || items == NULL || n < 1)
        return -1;
    qsort(items, n, sizeof(items[0]), q_compare);
    Heap *max_heap = new_heap(n, compare);
    Box *box;
    for (int i = 0; i < n; ++i) {
        box = heap_top(max_heap);
        if(box == NULL || items[i] > box->left){
           box = (Box*)malloc(sizeof(Box));
           box->capacity = box->left = capacity;
           box->left -= items[i];
           heap_push(max_heap, box);
        }
        else{
            box->left -= items[i];
            heap_max_decrease_key_just(max_heap, 0);
        }
    }
    int size = max_heap->size;
    for (int j = 0; j < size; ++j)
        printf("%.2f ", ((Box*)(max_heap->array[j].value))->left);
    printf("\n");
    heap_clear(max_heap);
    return size;
}