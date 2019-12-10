//
// Created by Once on 2019/11/25.
//

#include "huffman.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"

static int compare(void *a, void *b){
    CNode *l = (CNode*)a;
    CNode *r = (CNode*)b;
    return l->w < r->w;
}

static void dfs(CNode *root, Pair pairs[], char chs[]){
    if(root->left == NULL && root->right == NULL){
        pairs[root->ch].ch = root->ch;
        strcpy(pairs[root->ch].code, chs);
        chs[strlen(chs)] = '\0';
        printf("{char: %c, frequency: %d, code: %s}\n", root->ch, root->w, chs);
        return;
    }
    int size = strlen(chs);
    chs[size] = '0';
    dfs(root->left, pairs, chs);
    chs[size] = '1';
    chs[size + 1] = '\0';
    dfs(root->right, pairs, chs);
}

void huffman_encode(char *string){
    if(string == NULL || strlen(string) < 1)
        return;
    char ch[256];
    memset(ch, 0, 256);

    // count frequencies of char
    for (int i = 0; i < strlen(string); ++i)
        ch[string[i]]++;
    int length = 0;
    for (int k = 0; k < 256; ++k)
        if(ch[k] != 0)
            length++;

    // create single node tree
    Heap *min_heap = new_heap(length, compare);
    for (int j = 0; j < 256; ++j) {
        if(ch[j] != 0){
            CNode *node = malloc(sizeof(CNode));
            node->ch = j;
            node->w = ch[j];
            node->left = node->right = NULL;
            heap_push(min_heap, node);
        }
    }

    // create trie tree/huffman tree
    CNode *left, *right;
    while(min_heap->size != 1){
        left = heap_top(min_heap);
        heap_pop(min_heap);
        right = heap_top(min_heap);
        heap_pop(min_heap);
        CNode *root = malloc(sizeof(CNode));
        root->ch = -1;
        root->w = left->w + right->w;
        root->left = left;
        root->right = right;
        heap_push(min_heap, root);
    }

    // traverse huffman tree
    CNode *_root = heap_top(min_heap);
    heap_clear(min_heap);
    Pair pairs[256]; // 可用散列表代替
    char chs[258];
    memset(chs, '\0', 258);
    dfs(_root, pairs, chs);

    // print huffman code
    int count = 0;
    for (int l = 0; l < strlen(string); ++l) {
//        printf("[%c]%s ", string[l], pairs[string[l]].code);
        printf("%s", pairs[string[l]].code);
        count += strlen(pairs[string[l]].code);
    }
    printf("\nafter coding amount of bit: %d, to original: %d, compression rate: %.3f", count, strlen(string) * 8, count / ((float)strlen(string) * 8));
    printf("\n");

    huffman_tree_clear(_root);
}

void huffman_tree_clear(CNode *root){
    if(root == NULL)
        return;
    huffman_tree_clear(root->left);
    huffman_tree_clear(root->right);
    free(root);
}
