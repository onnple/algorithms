//
// Created by Once on 2019/12/2.
//

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * {2, 3, 5, 9, 6, 7} => A0:2x3 A1:3x5 A2:5x9 A3:9x6 A4:6x7
 * n is size of the matrix
 * assume [0][4]=1 => (A0 A1)(A2 A3 A4)
 */
void matrix_opt(const int *m, int n, int *s){
    if(m == NULL || n - 1 < 3 || s == NULL)
        return;
    int p[n * n];
    for (int x = 0; x < n; ++x)
        p[x * n + x] = 0;
    for (int l = 1; l < n; ++l) {
        for (int i = 0; i < n - l; ++i) {
            int j = i + l;
            p[i * n + j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int q = p[i * n + k] + p[(k + 1) * n + j] + m[i] * m[k + 1] * m[j + 1];
                if(p[i * n + j] > q){
                    p[i * n + j] = q;
                    s[i * n + j] = k;
                }
            }
        }
    }
}

static void _print_opt(const int *s, int i, int j, int n){
    if(i + 1 == j || i == j)
        return;
    int k = s[i * n + j];
    printf("(%d %d %d)\n", i, k, j);
    _print_opt(s, i, k, n);
    _print_opt(s, k + 1, j, n);
}

void print_opt(const int *s, int n){
    if(s == NULL || n < 1)
        return;
    _print_opt(s, 0, n - 1, n);
}