//
// Created by Once on 2019/12/6.
//

#ifndef ALGORITHMS_RANDOM_H
#define ALGORITHMS_RANDOM_H

static int M = 2147483647;
static int A = 48271;
static int Q = 0;
static int R = 0;
static int state = 1;

extern void random_set_seed(int seed);
extern int random_int(void);
extern int random_int_range(long a, long b);

#endif //ALGORITHMS_RANDOM_H
