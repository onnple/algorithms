//
// Created by Once on 2019/12/7.
//

#ifndef ALGORITHMS_SKIPLIST_H
#define ALGORITHMS_SKIPLIST_H

typedef void* value;

typedef enum stype{
    HEAD, DATA, TAIL
} SType;

typedef struct snode{
    int key;
    value value;
    struct snode *up, *down, *left, *right;
//    SType type;
} SNode;

typedef struct skiplist{
    SNode *head;
    int size;
    int height;
} SkipList;

extern SkipList *slist_new(void);
extern int slist_is_empty(SkipList *slist);
extern SNode *slist_find(SkipList *slist, int key);
extern value slist_search(SkipList *slist, int key);
extern void slist_add(SkipList *slist, int key, value value);
extern void slist_traverse(SkipList *slist);
extern void slist_delete(SkipList *slist, int key);
extern void slist_clear(SkipList *slist);

#endif //ALGORITHMS_SKIPLIST_H
