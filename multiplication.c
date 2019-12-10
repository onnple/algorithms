//
// Created by Once on 2019/11/29.
//

#include "multiplication.h"
#include <math.h>

static long multi(long X, long Y, int n){
    if(X == 0 || Y == 0)
        return 0;
    if(n == 1)
        return X * Y;
    long P = (long)pow(10, (double)n / 2);
    long Q = P * P;
    long XL = X / P;
    long XR = X % P;
    long YL = Y / P;
    long YR = Y % P;
//  XL * YL * Q + ((XL - XR) * (YR - YL) + XL * YL + XR * YR) * P + XR * YR;
    long XLYL = multi(XL, YL, n / 2);
    long XRYR = multi(XR, YR, n / 2);
    long XLXRYRYL = multi(XL - XR, YR - YL, n / 2);
    return XLYL * Q + (XLXRYRYL + XLYL + XRYR) * P + XRYR;
}

static int bite(long x, int b){
    if(x == 0)
        return b;
    return bite(x / 10, b + 1);
}

// X: n, Y: m
long multiply(long X, long Y){
    if(X == 0 || Y == 0)
        return 0;
    int n = bite(X, 0);
    int m = bite(Y, 0);
    if(n != m)
        return -1;
    return multi(X, Y, n);
}