//
// Created by Once on 2019/12/4.
//

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue* queue_new(){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if(!queue){
        perror("alloc for queue error");
        return NULL;
    }
    queue->size = 0;
    queue->head = queue->tail = NULL;
    return queue;
}

int queue_is_empty(Queue *queue){
    if(queue == NULL)
        return 1;
    return queue->size == 0;
}

void queue_push(Queue *queue, QValue value){
    if(queue == NULL)
        return;
    QNode *node = (QNode*)malloc(sizeof(QNode));
    node->value = value;
    node->next = NULL;
    if(queue->size == 0){
        queue->head = queue->tail = node;
        queue->size++;
        return;
    }
    QNode *tail = queue->tail;
    tail->next = node;
    queue->tail = node;
    queue->size++;
}

QValue queue_pop(Queue *queue){
    if(queue == NULL || queue->size == 0)
        return NULL;
    QNode *head = queue->head;
    queue->head = head->next;
    QValue value = head->value;
    free(head);
    queue->size--;
    return value;
}

void queue_clear(Queue *queue){
    if(queue == NULL)
        return;
    QNode *node = queue->head, *temp;
    while(node != NULL){
        temp = node->next;
        free(node);
        node = temp;
    }
    free(queue);
}