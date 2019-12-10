//
// Created by Once on 2019/11/25.
//

#ifndef ALGORITHMS_HEAP_H
#define ALGORITHMS_HEAP_H

// binary heap: min heap & max heap

typedef void* Object;

typedef struct hnode{
//    int key;
    Object value;
} HNode;

typedef struct heap{
    int length;
    int size;
    HNode *array;
    int (*compare)(void*, void*);
} Heap;

extern Heap* new_heap(int length, int (*compare)(void*, void*));
extern int heap_is_empty(Heap *heap);
extern int heap_is_full(Heap *heap);
//extern void heap_push(Heap *heap, int key, Object value);
extern void heap_push(Heap *heap, Object value);
extern Object heap_top(Heap *heap);
extern void heap_pop(Heap *heap);
extern void heap_min_decrease_key_just(Heap *heap, int i);
extern void heap_max_increase_key_just(Heap *heap, int i);
extern void heap_max_decrease_key_just(Heap *heap, int i);
extern void heap_clear(Heap *heap);

#endif //ALGORITHMS_HEAP_H
