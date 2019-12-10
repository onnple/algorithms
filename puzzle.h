//
// Created by Once on 2019/12/10.
//

#ifndef ALGORITHMS_PUZZLE_H
#define ALGORITHMS_PUZZLE_H

typedef struct square{
    int p; // priority: p = f(x) = g(x) + h(x)
    int *boxes;
    int level;
    int i, j;
    struct square *parent;
} Square;

typedef struct puzzle{
    int n;
    Square *s;
    Square *t;
} Puzzle;

extern Puzzle *puzzle_new(const int *s, const int *t, int n);
extern int puzzle_solve(Puzzle *puzzle);
extern void puzzle_detail(Puzzle *puzzle);
extern void puzzle_clear(Puzzle *puzzle);

#endif //ALGORITHMS_PUZZLE_H
