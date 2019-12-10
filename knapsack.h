//
// Created by Once on 2019/11/23.
//

#ifndef ALGORITHMS_KNAPSACK_H
#define ALGORITHMS_KNAPSACK_H

// 背包问题, knapsack problem

// 有效，已选，无效(不再选择)
typedef enum goodflag{
    Available, Chosen, Invalid
} GoodFlag;

// 物品, good or item
typedef struct good{
    float weight; // weight of good
    float price; // price of good
} Good;

typedef struct gnode{
    Good good;
    GoodFlag flag; // type of choosing
    float rate; // key: price/weight
} GNode;

// 使用二叉堆储存所有物品(最大堆)
// use a binary heap to store all goods
typedef struct knapsack{
    int length; // max size of heap
    int size; // used size
    float capacity;
    float left_capacity;
    GNode *goods;
} Knapsack;

extern Knapsack* new_knapsack(int length, float capacity);
extern int knapsack_is_empty(Knapsack *knapsack);
extern int knapsack_is_full(Knapsack *knapsack);
extern void knapsack_push(Knapsack *knapsack, Good *good);
extern GNode* knapsack_top(Knapsack *knapsack);
extern void knapsack_pop(Knapsack *knapsack);
extern void knapsack_decrease_key(Knapsack *knapsack, int i, float new_rate);
extern void knapsack_build(Knapsack *knapsack, Good *goods, int n);
extern int knapsack_clear(Knapsack *knapsack);
// 求最大价值
extern float knapsack_max_price(Knapsack *knapsack);

#endif //ALGORITHMS_KNAPSACK_H
