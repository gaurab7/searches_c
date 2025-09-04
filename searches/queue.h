#ifndef Q_H
#define Q_H

#include <stdbool.h>

#define MAX 100

typedef struct {
    char items[MAX];
    char front;
    char rear;
} Queue;

void initQueue(Queue* q);
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, char value);
char dequeue(Queue* q);
char peek(Queue* q);

#endif




