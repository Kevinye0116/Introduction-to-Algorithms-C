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

> - [ ] There’s something wrong with the source code? (Now from ChatGPT solved.)

The C source code of **QUEUE** given by ChatGPT: 

```c
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

```

---



## 10.2	Linked lists

A ***linked list*** is a data structure in which the objects are arranged in a linear order. Unlike an array, however, in which the linear order is determined by the array indices, the order in a linked list is determined by a pointer in each object. Since the elements of linked lists often contain keys that can be searched for, linked lists are sometimes called ***search lists***. Linked lists provide a simple, flexible representation for dynamic sets.

Each element of a ***double linked list*** $L$ is an object with an attribute $key$ and two pointer attributes: $next$ and $prev$. The object ma also contain other satellite data. Given an element $x$ in the list, $x.next$ points to its successor in the linked list, and $x.prev$ points to its predecessor. If $x.prev=NIL$, the element $x$ has no predecessor and is therefore the first element, or ***head***, of the list. If $x.next=NIL,$ the element $x$ has no successor and is therefore the last element, or ***tail***, of the list. An attribute $L.head$ points to the first element of the list. If $L.head=NIL,$ the list is empty.

A list may have one of several forms. It may be either singly linked or doubly linked, it may by sorted or not, and it may be circular or not. If a list is ***singly linked***, each element has a $next$ pointer but not a $prev$ pointer. If a list is ***sorted***, the linear order of the list corresponds to the linear order of keys stored in elements of the list. The minimum element is then the head of the list, and the maximum element is the tail. If the list is ***unsorted***, the elements can appear in any order. In a ***circular list***, the $prev$ pointer of the head of the list points to the tail, and the $next$ pointer of the tail of the list points to the head. You can think of a circular list as a ring of elements. In the remainder of this section, we assume that the lists we are working with are unsorted and doubly linked.

### Searching a linked list

The procedure **LIST-SEARCH($L$, $k$)** finds the first element with key $k$ in  list $L$ by a simple linear search, returning a pointer to this element. If no object with key $k$ appears in the list, then the procedure returns **NIL**. For the linked list in Figure 10.4(a), the call **LIST-SEARCH($L$, $4$)** returns a pointer to the third element, and the call **LIST-SEARCH($L$, $7$)** returns **NIL**. To search a list of $n$ objects, the **LIST-SEARCH** procedure takes $\Theta(n)$ time in the worst case, since it may have to search the entire list.

##### LIST-SEARCH($L$, $k$)

```pseudocode
x = L.head
while x != NIL and x.key != k
	x = x.next
return x
```

### Inserting into a linked list

Given an element $x$ whose $key$ attribute has already been set, the **LIST-PREPEND** procedure adds $x$ to the front of the linked list. The running time for **LIST-PREPEND** on a list of $n$ elements is $O(1)$.

##### LIST-PREPEND($L$,$x$)

```pseudocode
x.next = L.head
x.prev = NIL
if L.head != NIL
	L.head.prev = x
L.head = x
```

You can insert anywhere within a linked list. If you have a pointer $y$ to an object in the list, the **LIST-INSERT** procedure “splices”a new element $x$ into the list, immediately following $y$, in $O(1)$ time. Since **LIST-INSERT** never references the list object $L$, it is not supplied as a parameter.

##### LIST-INSERT($x$, $y$)

```pseudocode
x.next = y.next
x.prev = y
if y.next != NIL
	y.next.prev = x
y.next = x
```

### Deleting from a linked list

The procedure **LIST-DELETE** removes an element $x$ from a linked list $L$. It must be given a pointer to $x$, and it then “splices” $x$ out of the list by updating pointers. To delete an element with a given key, first call **LIST-SEARCH** to retrieve a pointer to the element. **LIST-DELETE** runs in $O(1)$ time, but to delete an element with a given key, the call to **LIST-SEARCH** makes the worst-case running time be $\Theta(n)$.

##### LIST-DELETE($L$, $x$)

```pseudocode
if x.prev != NIL
	x.prev.next = x.next
else L.head = x.next
if x.next != NIL
	x.next.prev = x.prev
```

Insertion and deletion are faster operations on doubly linked lists than on arrays. If you want to insert a new first element into an array or delete the first element in an array, maintaining the relative order of all the existing elements, then each of the existing elements needs to be moved by one position. In the worst case, therefore, insertion and deletion takes $\Theta(n)$ time in an array, compared with $O(1)$ time for a doubly linked list. If, however, you want to find the $k$th element in the linear order, it takes just $O(1)$ time in an array regardless of $k$, but in a linked list, you’d have to traverse $k$ elements, taking $\Theta(k)$ time.

### Sentinels

The code for **LIST-DELETE** is simpler if you ignore the boundary conditions at the head and tail of the list:

##### LIST-DELETE$’$($x$)

```pseudocode
x.prev.next = x.next
x.next.prev = x.prev
```

A ***sentinel*** is a dummy object that allows us to simplify boundary conditions. In a linked list $L$, the sentinel is an object $L.nil$ that represents **NIL** but has all the attributes of the other objects in the list. References to **NIL** are replaced by references to the sentinel $L.nil$. This change turns a regular doubly linked list into a ***circular, doubly linked list with a sentinel***, in which the sentinel $L.nil$ lies between the head and tail. The attribute $L.nil.next$ points to the head of the list, and $L.nil.prev$ points to the tail. Similarly, both the $next$ attribute of the tail and the $prev$ attribute of the head point to $L.nil$. Since $L.nil.next$ points to the head, the attribute $L.head$ is eliminate altogether, with references to it replaced by references to $L.nil.next$.

To delete an element from the list, just use the two-line procedure L**IST-DELETE$’$** from before. Just as **LIST-INSERT** never references the list object $L$, neither does **LIST-DELETE$’$**. ==You should never delete the sentinel $L.nil$ unless you are deleting the entire list!==

The **LIST-INSERT$’$** procedure inserts an element $x$ into the list following object $y$. No separate procedure for prepending is necessary: to insert at the head of the list, let $y$ be $L.nil$; and to insert at the tail, let $y$ be $L.nil.prev$.

##### LIST-INSERT$’$($x$, $y$)

```pseudocode
x.next = y.next
x.prev = y
y.next.prev = x
y.next = x
```

Searching a circular, doubly linked list with a sentinel has the same asymptotic running time as without a sentinel, but it is possible to decrease the constant factor. The test in line 2 of **LIST-SEARCH** makes two comparisons: one to check whether the search has run off the end of the list and, if not, one to check whether the key resides in the current element $x$. Suppose that you *know* that the key is somewhere in the list. Then you do not need to check whether the search runs off the end of the list, thereby eliminating one comparison in each iteration of the **while** loop.

The sentinel provides a place to put the key before starting the search. The search starts at the head $L.nil.next$ of list $L$, and it stops if it finds the key somewhere in the list. Now the search is guaranteed to find the key, either in the sentinel or before reaching the sentinel. If the key is found before reaching the sentinel, then it really is in the element where the search stops. If, however, the search goes through all the elements in the list and finds the key only in the sentinel, then the key is not really in the list, and the search returns **NIL**. The procedure **LIST-SEARCH$’$** embodies this idea.

##### LIST-SEARCH$’$($L$, $k$)

```pseudocode
L.nil.key = k
x = L.nil.next
while x.key != k
	x = x.next
if x == L.nil
	return NIL
else return x
```

Sentinels often simplify code and, as in searching a linked list, they might speed up code by a small constant factor, but they don’t typically improve the asymptotic running time. Use them judiciously. When there are man small lists, the extra storage used by their sentinels can represent significant wasted memory.

C source code of **LinkedList** provided by ChatGPT:

```c
//
// Created by Kevin Ye on 12/11/2023.
// Copyright (c) KevinYe on 12/11/2023.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *InitNode() {
    return NULL;
}

struct Node *Prepend(struct Node *head, int data) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = head;
    head = newNode;

    return head;
}

struct Node *insertAtEnd(struct Node *head, int data) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return head;
}

struct Node *insertAtPosition(struct Node *head, int data, int position) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;

    if (position == 1) {
        newNode->next = head;
        head = newNode;
    } else {
        struct Node *current = head;
        int count = 1;

        while (count < position - 1 && current != NULL) {
            current = current->next;
            count++;
        }

        if (current == NULL) {
            printf("Invalid position\n");
            free(newNode);
            return head;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    return head;
}

struct Node *search(struct Node *head, int key) {
    struct Node *current = head;

    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void printList(struct Node *head) {
    struct Node *current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node *head) {
    struct Node *current = head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(int argc, char *argv[]) {
    struct Node *myList = InitNode();

    myList = Prepend(myList, 1);
    myList = Prepend(myList, 2);
    myList = insertAtEnd(myList, 3);
    myList = insertAtEnd(myList, 4);
    myList = insertAtPosition(myList, 5, 3);

    printList(myList);

    int keyToSearch = 3;
    const struct Node *result = search(myList, keyToSearch);
    if (result != NULL) {
        printf("%d found in the list\n", keyToSearch);
    } else {
        printf("%d not found in the list\n", keyToSearch);
    }

    freeList(myList);

    return 0;
}
```

---

Copyright © Kevin Ye, 2023.

All Rights Reserved.
