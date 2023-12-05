//
// Created by Kevin Ye on 12/5/2023.
// Copyright (c) KevinYe on 12/5/2023.


#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
  int arr[MAX_SIZE];
  int front, rear;
} Queue;

void Initialize(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isFull(const Queue *queue) {
    return (queue->front == -1 && queue->rear == -1);
}

int isEmpty(const Queue *queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

void Enqueue(Queue *queue, int value) {
    if (isFull(queue))
}

int main(void) {
    Queue myQueue;
    Initialize(&myQueue);
    char op[10];
    while (1) {
        fgets(op, 10, stdin);
        op[9] = '\0';
        if (!strncmp(op, "exit", 4)) break;
        else if (!strncmp(op, "enqueue", 7)) {
            int value;
            scanf("%d", &value)
            Enqueue(&myQueue, value);
        } else if (!strncmp(op, "dequeue", 7)) {
            continue;
        } else printf("Invalid Operation!\n");
    }
    return 0;
}
