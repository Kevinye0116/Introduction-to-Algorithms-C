# 10	Elementary Data Structures

***By Kevin Ye***

---

In this chapter, we examine the representation of dynamic sets by simple data structures that use pointers. Although you can construct many complex data structures using pointers, we present only the rudimentary ones: arrays, metrices, stacks, queues, linked lists, and rooted trees.



## 10.1	Simple array-based data structures: arrays, matrices, stacks, queues

### 10.1.1	Arrays

We assume that, as in most programming languages, an array is stored as a contiguous sequence of bytes in memory. If the first element of an array has index $s$, the array starts at memory address $a$, and each array element occupies $b$ bytes, the the $i$th element occupies bytes $a+b(i-s)$ through $a+b(i-s+1)-1$. Assuming that the computer can access all memory locations in the same amount of time, it takes constant time to access any array element, regardless of the index.

Most programming languages require each element of a particular array to be the same size. If the elements of a given array might occupy different numbers of bytes, then the above formulas fail to apply, since the element size $b$ is not a constant. In such cases, the array elements are usually objects of varying sizes, and what actually appears in each array element is a pointer to the object. The number of bytes occupied by a pointer is typically the same, no matter what the pointer references, so that to access an object in an array, the above formulas give the address of the pointer to the object and then the pointer must be followed to access the object itself.



### 10.1.2	Matrices

We typically represent a matrix or two-dimensional array by one or more one-dimensional arrays. The two most common ways to store a matrix are row-major and column-major order. Let’s consider an $m\times n$ matrix - a matrix with $m$ rows and $n$ columns. In ***row-major order***, the matrix is stored row by row, and in ***column-major order***, the matrix is stored column by column. For example, consider the $2\times 3$ matrix
$$
M=\begin{pmatrix}
1 & 2 & 3 \\
4 & 5 & 6
\end{pmatrix}.
\tag{10.1}
$$
Row-major order stores the two rows $1$ $2$ $3$ and $4$ $5$ $6$, whereas column-major order stores the three columns $1$ $4$; $2$ $5$; and $3$ $6$.

Occasionally, other schemes are used to store matrices. In the ***block representation***, the matrix is divided into blocks, and each block is stored contiguously.



### 10.1.3	Stacks and queues

Stacks and queues are dynamic sets in which the element removed from the set by the **DELETE** operation is prespecified. In a ***stack***, the element deleted from the set is the one most recently inserted: the stack implements a ***last-in***, ***first-out***, or ***LIFO***, policy. Similarly, in a ***queue***, the element deleted is always the one that has been in the set for the longest time: the queue implements a ***first-in***, ***first-out***, or ***FIFO***, policy. There are several efficient ways to implement stacks and queues on a computer. Here, you will see how to use an array with attributes to store them.

#### Stacks

The **INSERT** operation on a stack is  often called **PUSH**, and the **DELETE** operation, which does not take an element argument, is often called **POP**. These names are allusions to physical stacks.

How to implement a stack of at most $n$ elements with an array $S[1:n]$. The stack has attributes $S.top$, indexing the most recently inserted element, and $S.size$, equaling the size $n$ of the array. The stack consists of elements $S[1:S.top]$, where $S[1]$ is the element at the bottom of the stack and $S[S.top]$ is the element at the top.

When $S.top=0$, the stack contains no elements and is ***empty***. We can test whether the stack is empty with the query operation **STACK-EMPTY**. Upon an attempt to pop an empty stack, the stack ***underflows***, which is normally an error. If $S.top$ exceeds $S.size$, the stack ***overflows***.

The procedures **STACK-EMPTY**, **PUSH**, and **POP** implement each of the stack operations with just a few lines of code. Each of the three stack operations takes $O(1)$ time.

##### STACK-EMPTY($S$)

```pseudocode
if S.top == 0
	return True
else return False
```

##### PUSH($S$, $x$)

```pseudocode
if S.top == S.size
	error "overflow"
else S.top = S.top + 1
	S[S.top] = x
```

##### POP($S$)

```pseudocode
if STACK-EMPTY(S)
	error "underflow"
else S.top = S.top - 1
	return S[S.top + 1]
```

---

The C source code of **Stack** (using struct): 

```c
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

```

##### Queues

We call the **INSERT** operation on a queue **ENQUEUE**, and we call the **DELETE** operation **DEQUEUE**. Like the stack operation **POP**, **DEQUEUE** takes no element argument. The **FIFO** property of a queue causes it to operate like a line of customers waiting for service. The queue has a ***head*** (front) and a ***tail*** (rear). When an element is enqueued, it takes its place at the tail of the queue, just as a newly arriving customer takes a place at the end of the line. The element dequeued is always the one at the head of the queue, like the customer at the head of the line, who has waited the longest.

Figure 10.3 shows one way to implement a queue of at most $n-1$ elements using an array $Q[1:n]$, with the attribute $Q.size$ equaling the size $n$ of the array. The queue has an attribute $Q.size$ equaling the size $n$ of the array. The queue has an attribute $Q.head$ that indexes, or points to, its head. The attribute $Q.tail$ indexes the next location at which a newly arriving element will be inserted into the queue. The elements in the queue reside in locations $Q.head, Q.head+1,\dots,Q.tail-1$, where we “wrap around” in the sense that location $1$ immediately follows location $n$ in a circular order. When $Q.head=Q.tail$, the queue is empty. Initially, we have $Q.head=Q.tail=1$. An attempt to dequeue an element from an empty queue causes the queue to underflow. When $Q.head=Q.tail+1$ or both $Q.head=1$ and $Q.tail=Q.size$, the queue is full, and an attempt to enqueue an element causes the queue to overflow.

In the procedures **ENQUEUE** and **DEQUEUE**, we have omitted the error checking for underflow and overflow.

##### ENQUEUE($Q$, $x$)

```pseudocode
Q[Q.tail] = x
if Q.tail ==Q.size
	Q.tail = 1
else Q.tail = Q.tail + 1
```

##### DEQUEUE($Q$)

```pseudocode
x = Q[Q.head]
if Q.head == Q.size
	Q.head = 1
else Q.head = Q.head + 1
return x
```

