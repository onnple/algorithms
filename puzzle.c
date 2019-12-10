//
// Created by Once on 2019/12/10.
//

#include "puzzle.h"
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

static Square *square_new(int n, const int *v, Square *parent, int level){
    Square *square = (Square*)malloc(sizeof(Square));
    square->parent = parent;
    square->p = INT_MAX;
    square->level = level;
    square->boxes = (int*)malloc(sizeof(int) * n * n);
    for (int i = 0; i < n * n; ++i) {
        square->boxes[i] = v[i];
    }
    return square;
}

static int h_cost(const int *x, const int *t, int n){
    int value = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(x[i * n + j] != t[i * n + j])
                value++;
        }
    }
    return value;
}

Puzzle *puzzle_new(const int *s, const int *t, int n){
    if(s == NULL || t == NULL || n < 1){
        perror("null pointer exception or n is small");
        return NULL;
    }
    Puzzle *puzzle = (Puzzle*)malloc(sizeof(Puzzle));
    puzzle->n = n;
    puzzle->s = square_new(n, s, NULL, 1);
    puzzle->s->p = 1 + h_cost(s, t, n);
    puzzle->t = square_new(n, t, NULL, INT_MAX);
    puzzle->t->p = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(s[i * n + j] == 0){
                puzzle->s->i = i;
                puzzle->s->j = j;
                break;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(t[i * n + j] == 0){
                puzzle->t->i = i;
                puzzle->t->j = j;
                break;
            }
        }
    }
    return puzzle;
}

static int compare(void *a, void *b){
    return ((Square*)a)->p < ((Square*)b)->p;
}

// (i, j) => botton, left, top, right
static int row[] = {1, 0, -1, 0};
static int col[] = {0, -1, 0, 1};

static int is_safe(Puzzle *puzzle, int x, int y){
    return (x >= 0 && x < puzzle->n && y >= 0 && y < puzzle->n);
}

static void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int puzzle_solve(Puzzle *puzzle){
    if(puzzle == NULL)
        return -1;
    Heap *min = new_heap(10, compare);
    heap_push(min, puzzle->s);
    Square *s;
    int n = puzzle->n;
    while(!heap_is_empty(min)){
        s = heap_top(min);
        heap_pop(min);
        if(h_cost(s->boxes, puzzle->t->boxes, n) == 0){
            free(puzzle->t->boxes);
            puzzle->t = s;
            return s->level;
        }
        for (int i = 0; i < 4; ++i) {
            if (is_safe(puzzle, s->i + row[i], s->j + col[i])){
                Square* ch = square_new(n, s->boxes, s, 1 + s->level);
                swap(&ch->boxes[s->i * n + s->j], &ch->boxes[(s->i + row[i]) * n + (s->j + col[i])]);
                ch->i = s->i + row[i];
                ch->j = s->j + col[i];
                ch->p = ch->level + h_cost(ch->boxes, puzzle->t->boxes, n);
                heap_push(min, ch);
            }
        }
    }
    return -1;
}

static void print_detail(Square *s, int n){
    if(s == NULL)
        return;
    print_detail(s->parent, n);
    printf("level - %d: \n", s->level);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d  ", s->boxes[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void puzzle_detail(Puzzle *puzzle){
    if(puzzle == NULL || puzzle->t == NULL || puzzle->s == NULL)
        return;
    print_detail(puzzle->t, puzzle->n);
}

static void clear(Square *s, int n){
    if(s == NULL)
        return;
    clear(s->parent, n);
    free(s);
}

void puzzle_clear(Puzzle *puzzle){
    if(puzzle == NULL)
        return;
    if(puzzle->s != NULL && puzzle->t != NULL)
        clear(puzzle->t, puzzle->n);
    free(puzzle);
}
