//
// Created by Once on 2019/12/2.
//

#include "basicnumber.h"

int fib_table(int n){
    int table[n];
    table[0] = table[1] = 1;
    if(n - 1 <= 1)
        return 1;
    for (int i = 2; i < n; ++i) {
        table[i] = table[i - 1] + table[i - 2];
    }
    return table[n - 1];
}

extern int fib_iterative(int n){
    if(n <= 2)
        return 1;
    int fib1 = 1;
    int fib2 = 1;
    int fibn = 0;
    for (int i = 3; i <= n; ++i) {
        fibn = fib1 + fib2;
        fib2 = fib1;
        fib1 = fibn;
    }
    return fibn;
}
