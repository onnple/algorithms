//
// Created by Once on 2019/12/7.
//

#include "skiplist.h"
#include <stdlib.h>
#include <stdio.h>
#include "random.h"
#include <time.h>

SkipList *slist_new(void){
    SkipList *slist = (SkipList*)malloc(sizeof(SkipList));
    if(!slist){
        perror("alloc for skip list error");
        return NULL;
    }
    slist->head = NULL;
    slist->size = 0;
    slist->height = 0;
    random_set_seed(time(NULL));
    return slist;
}

int slist_is_empty(SkipList *slist){
    if(slist == NULL)
        return 1;
    return slist->size == 0;
}

SNode *slist_find(SkipList *slist, int key){
    if(slist == NULL || slist->size == 0)
        return NULL;
    SNode *node = slist->head;
    while(1){
        while(node->right != NULL && node->right->key <= key){
            node = node->right;
        }
        if(node->down != NULL)
            node = node->down;
        else
            break;
    }
    return node;
}

value slist_search(SkipList *slist, int key){
    if(slist == NULL || slist->size == 0)
        return NULL;
    SNode *node = slist_find(slist, key);
    if(node->key != key)
        return NULL;
    else
        return node->value;
}

static SNode *node_new(int key, value value){
    SNode *node = (SNode*)malloc(sizeof(SNode));
    node->key = key;
    node->value = value;
    node->up = node->down = node->left = node->right = NULL;
    return node;
}

void slist_add(SkipList *slist, int key, value value){
    if(slist == NULL)
        return;
    SNode *node = slist_find(slist, key);
    if(node != NULL && node->key == key){
        perror("current list contains the same key");
        return;
    }
    SNode *n = node_new(key, value);
    if(node == NULL){
        node = node_new(INT_MIN, NULL);
        slist->head = node;
        slist->height = 1;
    }
    if(node->right != NULL)
        node->right->left = n;
    n->right = node->right;
    n->left = node;
    node->right = n;
    slist->size++;

    SNode *t, *h, *s;
    int current_height = 1;
    while(1){
        if(random_int() % 10 < 5){
            t = node_new(key, value);
            t->down = n;
            n->up = t;
            current_height++;
            if(current_height > slist->height){
                slist->height++;
                h = node_new(INT_MIN, NULL);
                slist->head->up = h;
                h->down = slist->head;
                slist->head = h;
                h->right = t;
                t->left = h;
            }
            else{
                s = n;
                SNode *up = NULL;
                while(s->left != NULL){
                    s = s->left;
                    up = s->up;
                    if(up != NULL)
                        break;
                }
                t->left = up;
                if(up != NULL){
                    t->right = up->right;
                    if(up->right != NULL){
                        up->right->left = t;
                    }
                    up->right = t;
                }
            }
            n = t;
        }
        else
            break;
    }
}

void slist_traverse(SkipList *slist){
    if(slist == NULL || slist->size == 0)
        return;
    SNode *head = slist->head, *temp;
    while(head != NULL){
        temp = head->right;
        printf("HEAD -> ");
        while(temp != NULL){
            printf("%d -> ", temp->key);
            temp = temp->right;
        }
        head = head->down;
        printf("\n");
    }
}

void slist_delete(SkipList *slist, int key){
    if(slist == NULL || slist->size == 0)
        return;
    SNode *node = slist_find(slist, key);
    if(node->key != key)
        return;
    SNode *temp;
    while(node != NULL){
        temp = node->up;
        node->left->right = node->right;
        if(node->right != NULL)
            node->right->left = node->left;
        free(node);
        node = temp;
    }
    slist->size--;
}

void slist_clear(SkipList *slist){
    if(slist == NULL)
        return;
    SNode *head = slist->head, *temp, *s, *t;
    while(head != NULL){
        s = head->down;
        temp = head->right;
        while(temp != NULL){
            t = temp->right;
            free(temp);
            temp = t;
        }
        free(head);
        head = s;
    }
    free(slist);
}
