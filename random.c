//
// Created by Once on 2019/12/6.
//

#include "random.h"

void random_set_seed(int seed){
    state = seed;
    Q = M / A;
    R = M % A;
}

int random_int(void){
    int temp = A * (state % Q) - R * (state / Q);
    if(temp >= 0)
        state = temp;
    else
        state = temp + M;
    return state;
}

int random_int_range(long a, long b){
    int number = 0;
    random_set_seed(17);
    while(1){
        number = random_int();
        if(number >= a && number <= b)
            break;
    }
    return number;
}