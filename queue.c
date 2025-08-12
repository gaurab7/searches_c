// learned u could do this today.
#include "queue.h"
#include <stdio.h>



void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front == -1;
}

bool isFull(Queue* q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue* q, char value) {
    if (isFull(q)) {
        prcharf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

char dequeue(Queue* q) {
    if (isEmpty(q)) {
        prcharf("Queue is empty!\n");
        return -1;
    }
    char item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

char peek(Queue* q) {
    if (isEmpty(q)) {
        prcharf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}
