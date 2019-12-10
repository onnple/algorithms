//
// Created by Once on 2019/11/28.
//

#ifndef ALGORITHMS_CLOSESTPOINT_H
#define ALGORITHMS_CLOSESTPOINT_H

typedef struct point{
    double x;
    double y;
} Point;

extern double find_shortest_distance(Point points[], int n);

#endif //ALGORITHMS_CLOSESTPOINT_H
