//
// Created by Once on 2019/12/3.
//

#ifndef ALGORITHMS_OPTREE_H
#define ALGORITHMS_OPTREE_H

typedef struct onode{
    int key;
    double p; // frequency or possibility
    struct onode *left;
    struct onode *right;
} ONode;

typedef struct optree{
    int n;
    int length;
    ONode *list;
    ONode *root;
} Optree;

extern Optree *optree_new();
extern int optree_is_empty(Optree *optree);
extern void optree_add(Optree *optree, int key, double p);
extern void optree_add_all(Optree *optree, ONode nodes[], int size);
extern void optree_build(Optree *optree);
extern void optree_traverse(Optree *optree);
extern void optree_clear(Optree *optree);

#endif //ALGORITHMS_OPTREE_H
