//
// Created by Once on 2019/12/4.
//

#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

typedef void* QValue;

typedef struct qnode{
    QValue value;
    struct qnode *next;
} QNode;

typedef struct queue{
    int size;
    QNode *head;
    QNode *tail;
} Queue;

extern Queue* queue_new();
extern int queue_is_empty(Queue *queue);
extern void queue_push(Queue *queue, QValue value);
extern QValue queue_pop(Queue *queue);
extern void queue_clear(Queue *queue);

#endif //ALGORITHMS_QUEUE_H
