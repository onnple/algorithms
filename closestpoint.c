//
// Created by Once on 2019/11/28.
//

#include "closestpoint.h"
#include <stdlib.h>
#include <math.h>

static double distance(Point *a, Point *b){
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

static double min(double a, double b){
    if(a > b)
        return a;
    else
        return b;
}

static int compare_x(const void *a, const void *b){
    Point *_a = (Point*)a;
    Point *_b = (Point*)b;
    return _a->x > _b->x;
}

static int compare_y(const void *a, const void *b){
    Point *_a = (Point*)a;
    Point *_b = (Point*)b;
    return _a->y > _b->y;
}

static double _shortest_distance(Point points[], int left, int right){
    if(left == right)
        return INT_MAX;
    if(left + 1 == right)
        return distance(&points[left], &points[right]);
    if(left + 2 == right)
        return min(min(distance(&points[left], &points[left + 1]), distance(&points[left], &points[right])),
                distance(&points[left + 1], &points[right]));
    int center = (left + right) / 2;
    double c = points[center].x;
    double dl = _shortest_distance(points, left, center);
    double dr = _shortest_distance(points, center + 1, right);
    double m = min(dl, dr);

    Point Q[right - left + 1];
    int n = 0;
    for (int k = left; k <= right; ++k) {
        if(fabs(points[k].x - c) < m)
            Q[n] = points[k], n++;
    }
    qsort(Q, n, sizeof(Point), compare_y);

    // O(n)
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if(Q[j].y - Q[i].y > m)
                break;
            if(distance(&Q[i], &Q[j]) < m)
                m = distance(&Q[i], &Q[j]);
        }
    }
    return m;
}

double find_shortest_distance(Point points[], int n){
    if(points == NULL || n < 2){
        perror("null point exception or n is too small");
        return -1;
    }
    qsort(points, n, sizeof(Point), compare_x);
    return _shortest_distance(points, 0, n - 1);
}