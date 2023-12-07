//
// Created by Kevin Ye on 11/30/2023.
// Copyright (c) KevinYe on 11/30/2023.

#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
  int arr[MAX_SIZE];
  int front, rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(const Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

int isFull(const Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }

    q->arr[q->rear] = value;
    printf("Enqueued: %d\n", value);
}

int dequeue(Queue *q) {
    int value;

    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    value = q->arr[q->front];

    if (q->front == q->rear) {
        initializeQueue(q);
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }

    printf("Dequeued: %d\n", value);
    return value;
}

int main() {
    Queue myQueue;
    initializeQueue(&myQueue);

    enqueue(&myQueue, 10);
    enqueue(&myQueue, 20);
    enqueue(&myQueue, 30);

    dequeue(&myQueue);
    dequeue(&myQueue);

    enqueue(&myQueue, 40);

    return 0;
}
