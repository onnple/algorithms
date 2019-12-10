//
// Created by Once on 2019/11/25.
//

#include "heap.h"
#include <stdlib.h>

Heap* new_heap(int length, int (*compare)(void*, void*)){
    if(length < 3 || compare == NULL){
        perror("length too small for null exception");
        return NULL;
    }
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    if(!heap){
        perror("alloc for heap error");
        return NULL;
    }
    heap->length = length;
    heap->size = 0;
    heap->compare = compare;
    heap->array = (HNode*)malloc(sizeof(HNode) * length);
    if(!heap->array){
        perror("alloc for array error");
        free(heap);
        return NULL;
    }
    return heap;
}

int heap_is_empty(Heap *heap){
    if(heap == NULL)
        return 1;
    return heap->size == 0;
}

int heap_is_full(Heap *heap){
    if(heap == NULL)
        return 1;
    return heap->size == heap->length;
}

static int parent(int i){
    return (i - 1) / 2;
}

static int left(int i){
    return 2 * i + 1;
}

static int right(int i){
    return 2 * i + 2;
}

static void swap(Heap *heap, int i, int j){
    Object value = heap->array[i].value;
    heap->array[i].value = heap->array[j].value;
    heap->array[j].value = value;
}

void heap_push(Heap *heap, Object value){
    if(heap == NULL){
        perror("null pointer exception");
        return;
    }
    if(heap_is_full(heap)){
        heap->length += heap->length;
        heap->array = (HNode*)realloc(heap->array, heap->length);
    }
    heap->size++;
    int i = heap->size - 1;
    heap->array[i].value = value;
    while(i != 0 && heap->compare(heap->array[i].value, heap->array[parent(i)].value)){
        swap(heap, i, parent(i));
        i = parent(i);
    }
}

Object heap_top(Heap *heap){
    if(heap == NULL || heap->size == 0)
        return NULL;
    return heap->array[0].value;
}

static void heapify(Heap *heap, int i){
    int l = left(i);
    int r = right(i);
    int small_max = i;
    if(l <  heap->size && heap->compare(heap->array[l].value, heap->array[i].value))
        small_max = l;
    if(r < heap->size && heap->compare(heap->array[r].value, heap->array[small_max].value))
        small_max = r;
    if(i != small_max){
        swap(heap, i, small_max);
        heapify(heap, small_max);
    }
}

void heap_pop(Heap *heap){
    if(heap == NULL || heap->size == 0)
        return;
    if(heap->size == 1){
        heap->size--;
        return;
    }
    swap(heap, 0, heap->size - 1);
    heap->size--;
    heapify(heap, 0);
}

void heap_min_decrease_key_just(Heap *heap, int i){
    if(heap == NULL || heap->size == 0 || i < 0)
        return;
    while(i != 0 && heap->compare(heap->array[i].value, heap->array[parent(i)].value)){
        swap(heap, i, parent(i));
        i = parent(i);
    }
}

void heap_max_increase_key_just(Heap *heap, int i){
    if(heap == NULL || heap->size == 0 || i < 0)
        return;
    while(i != 0 && heap->compare(heap->array[i].value, heap->array[parent(i)].value)){
        swap(heap, i, parent(i));
        i = parent(i);
    }
}

void heap_max_decrease_key_just(Heap *heap, int i){
    if(heap == NULL || heap->size == 0 || i < 0)
        return;
    heapify(heap, i);
}

void heap_clear(Heap *heap){
    if(heap == NULL)
        return;
    free(heap->array);
    free(heap);
}