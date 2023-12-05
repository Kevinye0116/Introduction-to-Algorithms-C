//
// Created by Kevin Ye on 11/30/2023.
// Copyright (c) KevinYe on 11/30/2023.

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct {
  int array[MAX_SIZE];
  int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

int isEmpty(const Stack *stack) {
    return stack->top == -1;
}

int isFull(const Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void Push(Stack *stack, int value) {
    if (isFull(stack)) perror("Stack overflow");
    else {
        stack->top++;
        stack->array[stack->top] = value;
        printf("%d pushed to stack.\n", value);
    }
}

int Pop(Stack *stack) {
    if (isEmpty(stack)) {
        perror("Stack underflow");
        return -1;
    } else {
        int poppedValue = stack->array[stack->top];
        stack->top--;
        return poppedValue;
    }
}

int Peek(const Stack *stack) {
    if (isEmpty(stack)) {
        perror("Stack is empty");
        return -1;
    } else {
        return stack->array[stack->top];
    }
}

int main(void) {
    Stack myStack;
    initialize(&myStack);
    while (1) {
        char op[5];
        fgets(op, 5, stdin);
        getchar();
        op[4] = '\0';
        if (!strncmp(op, "exit", 4)) break;
        else if (!strncmp(op, "push", 4)) {
            int value;
            scanf("%d", &value);
            Push(&myStack, value);
        } else if (!strncmp(op, "pop", 3)) printf("%d popped from stack\n", Pop(&myStack));
        else if (!strncmp(op, "peek", 4)) printf("Top element: %d\n", Peek(&myStack));
        else {
            printf("Invalid Operation!\n");
        }
    }
    return 0;
}
