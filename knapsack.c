//
// Created by Once on 2019/11/23.
//

#include "knapsack.h"
#include <stdlib.h>
#include <stdio.h>

Knapsack* new_knapsack(int length, float capacity){
    if(length < 3){
        perror("length is too small");
        return NULL;
    }
    Knapsack *knapsack = (Knapsack*)malloc(sizeof(Knapsack));
    if(!knapsack){
        perror("alloc for knapsack error");
        return NULL;
    }
    knapsack->length = length;
    knapsack->capacity = knapsack->left_capacity = capacity;
    knapsack->size = 0;
    knapsack->goods = (GNode*)malloc(sizeof(GNode) * length);
    if(!knapsack->goods){
        perror("alloc for goods error");
        free(knapsack);
        return NULL;
    }
    return knapsack;
}

int knapsack_is_empty(Knapsack *knapsack){
    if(knapsack == NULL)
        return 1;
    return knapsack->size == 0;
}

int knapsack_is_full(Knapsack *knapsack){
    if(knapsack == NULL)
        return 1;
    return knapsack->size == knapsack->length;
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

static void swap(Knapsack *knapsack, int i, int j){
    float rate = knapsack->goods[i].rate;
    GoodFlag flag = knapsack->goods[i].flag;
    float weight = knapsack->goods[i].good.weight;
    float price = knapsack->goods[i].good.price;
    knapsack->goods[i].rate = knapsack->goods[j].rate;
    knapsack->goods[i].flag = knapsack->goods[j].flag;
    knapsack->goods[i].good.weight = knapsack->goods[j].good.weight;
    knapsack->goods[i].good.price = knapsack->goods[j].good.price;
    knapsack->goods[j].rate = rate;
    knapsack->goods[j].flag = flag;
    knapsack->goods[j].good.weight = weight;
    knapsack->goods[j].good.price = price;
}

void knapsack_push(Knapsack *knapsack, Good *good){
    if(knapsack_is_full(knapsack) || good == NULL) {
        perror("overflow or null exception");
        return;
    }
    float rate = good->price / good->weight;
    knapsack->size++;
    int i = knapsack->size - 1;
    knapsack->goods[i].rate = rate;
    knapsack->goods[i].flag = Available;
    knapsack->goods[i].good.weight = good->weight;
    knapsack->goods[i].good.price = good->price;
    while(i != 0 && knapsack->goods[i].rate > knapsack->goods[parent(i)].rate){
        swap(knapsack, i, parent(i));
        i = parent(i);
    }
}

GNode* knapsack_top(Knapsack *knapsack){
    if(knapsack == NULL || knapsack->size == 0)
        return NULL;
    return &knapsack->goods[0];
}

static void heapify(Knapsack *knapsack, int i){
    int l = left(i);
    int r = right(i);
    int max = i;
    if(l < knapsack->size && knapsack->goods[i].rate < knapsack->goods[l].rate)
        max = l;
    if(r < knapsack->size && knapsack->goods[max].rate < knapsack->goods[r].rate)
        max = r;
    if(max != i){
        swap(knapsack, i, max);
        heapify(knapsack, max);
    }
}

void knapsack_pop(Knapsack *knapsack){
    if(knapsack == NULL || knapsack->size == 0)
        return;
    knapsack->goods[0].rate = INT_MIN;
    swap(knapsack, 0, knapsack->size - 1);
    knapsack->size--;
    heapify(knapsack, 0);
}

void knapsack_decrease_key(Knapsack *knapsack, int i, float new_rate){
    if(knapsack == NULL || knapsack->size == 0 || i < 0 || i > knapsack->size - 1)
        return;
    knapsack->goods[i].rate = new_rate;
    heapify(knapsack, i);
}

void knapsack_build(Knapsack *knapsack, Good *goods, int n){
    if(knapsack == NULL || goods == NULL || n < 0 || n > knapsack->length)
        return;
    knapsack->size = n;
    for (int j = 0; j < n; ++j) {
        knapsack->goods[j].flag = Available;
        knapsack->goods[j].rate = goods[j].price / goods[j].weight;
        knapsack->goods[j].good.weight = goods[j].weight;
        knapsack->goods[j].good.price = goods[j].price;
    }
    for (int i = knapsack->size / 2; i >= 0; --i)
        heapify(knapsack, i);
}

int knapsack_clear(Knapsack *knapsack){
    if(knapsack == NULL)
        return -1;
    free(knapsack->goods);
    free(knapsack);
    return 1;
}

// 贪心算法求最大价值
float knapsack_max_price(Knapsack *knapsack){
    if(knapsack == NULL || knapsack->size == 0)
        return 0;
    GNode *node;
    float max_price = 0;
    while(!knapsack_is_empty(knapsack) && knapsack->left_capacity > 0){
        node = knapsack_top(knapsack);
        if(node->flag == Available && node->good.weight <= knapsack->left_capacity){
            max_price += node->good.price;
            node->flag = Chosen;
            knapsack->left_capacity -= node->good.weight;
        }
        else
            node->flag = Invalid;
        knapsack_pop(knapsack);
    }
    return max_price;
}