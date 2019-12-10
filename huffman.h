//
// Created by Once on 2019/11/25.
//

#ifndef ALGORITHMS_HUFFMAN_H
#define ALGORITHMS_HUFFMAN_H

typedef struct cnode{
    char ch;
    int w;
    struct cnode *left;
    struct cnode *right;
} CNode;

typedef struct pair{
    char ch;
    char code[258];
} Pair;

extern void huffman_encode(char *string);
extern void huffman_tree_clear(CNode *root);

#endif //ALGORITHMS_HUFFMAN_H
