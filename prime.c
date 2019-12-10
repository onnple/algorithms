//
// Created by Once on 2019/12/7.
//

#include "prime.h"
#include "random.h"

static long witness(long a, long i, long N){
    long X, Y;
    if(i == 0)
        return 1;
    X = witness(a, i/2, N);
    if(X == 0)
        return 0;
    Y = (X * X) % N;
    if(Y == 1 && X != 1 && X != N - 1)
        return 0;
    if(i % 2 != 0)
        Y = (a * Y) % N;
    return Y;
}

int is_prime(long N){
    for (int i = 0; i < 5; ++i) {
        if(witness(random_int_range(2, N -2), N - 1, N) != 1)
            return 0;
    }
    return 1;
}