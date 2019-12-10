#include <stdio.h>
#include "knapsack.h"
#include "huffman.h"
#include "binpacking.h"
#include "closestpoint.h"
#include "multiplication.h"
#include "basicnumber.h"
#include "matrix.h"
#include "optree.h"
#include "graph.h"
#include "random.h"
#include "skiplist.h"
#include "prime.h"
#include "game.h"
#include "puzzle.h"

static void knapsack_problem(void){
    Knapsack *knapsack = new_knapsack(3, 50);
    Good g;
    g.weight = 10;
    g.price = 60;
    knapsack_push(knapsack, &g);
    g.weight = 20;
    g.price = 100;
    knapsack_push(knapsack, &g);
    g.weight = 30;
    g.price = 120;
    knapsack_push(knapsack, &g);
    float max_price = knapsack_max_price(knapsack);
    printf("max price: %.2f\n", max_price);
    knapsack_clear(knapsack);

    int n = 7;
    Knapsack *sack = new_knapsack(n, 150);
    Good goods[] = {{35, 10}, {30, 40}, {60, 30}, {50, 50},
                      {40, 35}, {10, 40}, {25, 30}};
    knapsack_build(sack, goods, n);
    float max = knapsack_max_price(sack);
    printf("max price: %.2f\n", max);
    knapsack_clear(sack);
}

static void huffman(void){
    char *string = "<<The Price Of Salt>>";
    huffman_encode(string);
    printf("\n");
    char *temp = "A_DEAD_DAD_CEDED_A_BAD_BABE_A_BEADED_ABACA_BED";
    huffman_encode(temp);
}

static void binpack(void){
    Item items[7] = {0.5, 0.3, 0.1, 0.7, 0.8, 0.4, 0.2};
    int size_of_boxes = binpacking(1.0, items, 7);
    printf("size of boxes: %d\n", size_of_boxes);

    printf("\n");

    Item items2[] = {0.42, 0.25, 0.27, 0.07, 0.72, 0.86, 0.09, 0.44, 0.50, 0.68, 0.73, 0.31, 0.78, 0.17, 0.79, 0.37, 0.73, 0.23, 0.30};
    int size_of_boxes2 = binpacking(1.0, items2, sizeof(items2) / sizeof(items2[0]));
    printf("size of boxes: %d\n", size_of_boxes2);
}

static void closest_point(void){
    Point P[] = {{9, 3}, {30, 14}, {60, 50}, {4, 6}, {8, 13}, {1, 8}};
    int n = sizeof(P) / sizeof(P[0]);
    printf("smallest distance: %f\n" , find_shortest_distance(P, n));
}

static void muti(void){
    printf("%ld\n", multiply(3241, 6894));
}

static void fib(void){
    printf("%d %d\n", fib_table(15), fib_iterative(15));
}

static void matrix(void){
    int n = 5;
    int m[] = {2, 3, 5, 9, 6, 7};
    int s[n * n];
    matrix_opt(m, n, s);
    print_opt(s, n);
}

static void optree(void){
    Optree *optree = optree_new();
    int n = 6;
    ONode nodes[] = {
            {0, 0.6, NULL, NULL},
            {1, 0.12, NULL, NULL},
            {2, 0.82, NULL, NULL},
            {3, 0.09, NULL, NULL},
            {4, 0.3, NULL, NULL},
            {5, 0.7, NULL, NULL},
    };
    optree_add_all(optree, nodes, n);
    optree_build(optree);
    optree_traverse(optree);
    optree_clear(optree);
}

static void shortest_path(void){
    Graph *g1 = graph_new(3);
    Edge ed1[] = {
            {0, 1, 2},
            {1, 0, 8},
            {1, 2, 6},
            {0, 2, 9},
            {2, 0, 1}
    };
    graph_add_all(g1, ed1, 5);
    graph_shortest_path_of_pair(g1);
    graph_print_path(g1, 0, 2);
    graph_clear(g1);

    Graph *g2 = graph_new(6);
    Edge ed2[] = {
            {0, 1, 4},
            {0, 2, 2},
            {1, 2, 5},
            {1, 3, 10},
            {2, 4, 3},
            {4, 3, 4},
            {3, 5, 11}
    };
    graph_add_all(g2, ed2, 7);
    graph_shortest_path_of_pair(g2);
    graph_print_path(g2, 0, 5);
    graph_clear(g2);
}

static void random(void){
    random_set_seed(9);
    for (int i = 0; i < 200; ++i) {
        printf("%d ", random_int() % 200);
    }
    printf("\n");
}

static void skiplist(void){
    SkipList *slist = slist_new();
    slist_add(slist, 5, 5);
    slist_add(slist, 20, 20);
    slist_add(slist, 1, 1);
    slist_add(slist, 14, 14);
    slist_add(slist, 36, 36);
    slist_add(slist, 7, 7);
    int value = (int)slist_search(slist, 20);
    printf("search result: %d\n", value);
    value = (int)slist_search(slist, 79);
    printf("search result: %d\n", value);

    printf("\noriginal: %d\n", slist->height);
    slist_traverse(slist);
    slist_delete(slist, 1);

    printf("\nafter deletion: %d\n", slist->height);
    slist_traverse(slist);
    slist_add(slist, 3, 3);
    slist_add(slist, 86, 86);
    printf("\nnew insertion: %d\n", slist->height);
    slist_traverse(slist);
    slist_clear(slist);
}

static void prime(void){
    int number = 10601;
    printf("number 10601 is prime? %d\n", is_prime(number));
    number = 12654;
    printf("number 12654 is prime? %d\n", is_prime(number));
}

static void game(void){
    game_start();
//    Board *board = game_board_new(4);
//    int p, v;
//    game_find_comp_move_basic(board, &p, &v);
//    printf("%d %d\n", p, v);
}

static void puzzle(void){
    int s[] = {
                    1, 2, 3,
                    5, 6, 0,
                    7, 8, 4
            };

    int t[] =
            {
                    1, 2, 3,
                    5, 8, 6,
                    0, 7, 4
            };
    Puzzle *puzzle = puzzle_new(s, t, 3);
    int steps = puzzle_solve(puzzle);
    printf("steps: %d\n", steps);
    puzzle_detail(puzzle);
    puzzle_clear(puzzle);
}

int main(void) {
    puzzle();
    return 0;
}