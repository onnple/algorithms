//
// Created by Once on 2019/11/26.
//

#ifndef ALGORITHMS_BINPACKING_H
#define ALGORITHMS_BINPACKING_H

typedef double Item;

typedef struct box{
    double capacity;
    float left;
} Box;

extern int binpacking(double capacity, Item items[], int n);

#endif //ALGORITHMS_BINPACKING_H
