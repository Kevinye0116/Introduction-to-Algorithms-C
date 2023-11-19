# 6	Heapsort

***By Kevin Ye***

---

This chapter introduces another sorting algorithm: ***heapsort***. Like merge sort, but unlike insertion sort, heapsort’s running time is $O(n\lg n)$. Like insertion sort, but unlike merge sort, heapsort sorts in place: ==only a constant number of array elements are stored outside the input array at any time==. Thus, heapsort combines the better attributes of the two sorting algorithms we have already discussed.

Heapsort also introduces another algorithm design technique: using a data structure, in this case one we call a “heap”, to manage information. Not only is the heap data structure useful for heapsort, but it also makes an efficient priority queue. The heap data structure will reappear in algorithms in later chapters.





## 6.1	Heaps

The ***(binary) heap*** data structure is an array object that we can ==view as a nearly complete binary tree==. Each node of the tree corresponds to an element of the array. The tree is completely filled on all levels except possibly the lowest, which is filled from the left up to a point. An array ***A[1 : n]*** that represents a heap is an object with an attribute *A.heap-size*, which represents how many elements in the heap are stored within array ***A***. The root of the tree is ***A[1]***, and given the index *i* of a node, there’s a simple way to compute the indices of its parent, left child, and right child with the one-line procedures **PARENT**, **LEFT**, and **RIGHT**.

```pseudocode
PARENT(i)
return i // 2

LEFT(i)
return 2 * i

RIGHT(i)
return 2 * i + 1
```

There are two kinds of binary heaps: **max-heaps** and **min-heaps**. In both kinds, the values in the nodes satisfy a ***heap property***, the specifics of which depend on the kind of heap. In a ***max-heap***, the ***max-heap property*** is that for every node *i* other than the root,
$$
A[PARENT(i)] \geq A[i]，
$$
that is, the value of a node is at most the value of its parent. Thus, the largest element in a max-heap is stored at the root, and the subtree rooted at a node contains values no larger than that contained at the node itself. A ***min-heap*** is organized in the opposite way: the ***min-heap property*** is that for every node *i* other than the root,
$$
A[PARENT(i)] \leq A[i].
$$
The smallest element in a min-heap is at the root.

Viewing a heap as a tree, we define the ***height*** of a node in a heap to be the number of edges on the longest simple downward path from the node to a leaf, and we define the height of the heap to be the height of its root. Since a heap of *n* elements is based on a complete binary tree, its height is $\Theta(\lg n)$. As we’ll see, the basic operations on heaps run in time at most proportional to the height of the tree and thus take $O(\lg n)$ time. The remainder of this chapter presents some basic procedures and shows how they are used in a sorting algorithm and a priority-queue data structure.

- The **MAX-HEAPIFY** procedure, which runs in $O(\lg n)$ time, is ==the key to maintaining the max-heap property==.
- The **BUILD-MAX-HEAP** procedure, which runs in linear time, produces a max-heap from an unordered input array.
- The **HEAPSORT** procedure, which runs in $O(n\lg n)$ time, ==sorts an array in place==.
- The procedures **MAX-HEAP-INSERT**, **MAX-HEAP-EXTRACT-MAX**, **MAX-HEAP-INCREASE-KEY**, and **MAX-HEAP-MAXIMUM** allow the heap data structure to implement a priority queue. They run in $O(\lg n)$ time plus the time for mapping between objects being inserted into the priority queue and indices in the heap.





## 6.2	Maintaining the heap property

The procedure **MAX-HEAPIFY** on the facing page maintains the max-heap property. Its inputs are an array *A* with the *heap-size* attribute and an index *i* into the array. When it is called, **MAX-HEAPIFY** assumes that the binary trees rooted at **LEFT(*i*)** and **RIGHT(*i*)** are max-heaps, but that *A[i]* might be smaller than its children, thus violating the max-heap property. **MAX-HEAPIFY** lets the value at **A[i]** “float down” in the max-heap so that the subtree rooted at index *i* obeys the max-heap property.

##### The action of *MAX-HEAPIFY*

Each step determines the largest of the elements *A[i]*, *A[LEFT(i)]*, and *A[RIGHT(i)]* and stores the index of the largest element in the *largest*. If *A[i]* is largest, then the subtree rooted at node *i* is already a max-heap and nothing else needs to be done. Otherwise, one of the two children contains the largest element. Positions *i* and *largest* swap their contents, which causes node *i* and its children to satisfy the max-heap property. The node indexed by *largest*, however, just had its value decreased, and thus the subtree rooted at *largest* might violate the max-heap property. Consequently, **MAX-HEAPIFY** calls itself recursively on that subtree.

##### MAX-HEAPIFY($A$, $i$)

```pseudocode
l=LEFT(i)
r=RIGHT(i)
if l <= A.heap-size and A[l] > A[i]
	largest = l
else largest = i
if r <= A.heap-size and A[r] > A[largest]
	largest = r
if largest != i
	exchange A[i] with A[largest]
	MAX-HEAPIFY(A, largest)
```





## 6.3	Building a heap

The procedure **BUILD-MAX-HEAP** converts an array *A*[1 : *n*] into a max-heap by calling **MAX-HEAPIFY** in a bottom-up manner. Each leave of the tree is a 1-element heap to begin with. **BUILD-MAX-HEAP** goes through the remaining nodes of the tree and runs **MAX-HEAPIFY** on each one.

##### BUILD-MAX-HEAP($A$, $n$)

```pseudocode
A.heap-size = n
for i = n // 2 downto 1
	MAX-HEAPIFY(A, i)
```

To show why **BUILD-MAX-HEAP** works correctly, we use the following loop invariant:

> At the start of each iteration of the **for** loop of lines 2~3, each node *i* + 1, *i* + 2, … , *n*is the root of a max-heap.[^1]

[^1]: The proof process is omitted here.





## 6.4	The heapsort algorithm

The heapsort algorithm, given by the procedure **HEAPSORT**, starts by calling the **BUILD-MAX-HEAP** procedure to build a max-heap on the input array *A*[1 : *n*]. Since the maximum element of the array is stored at the root *A*[1], **HEAPSORT** can place it into its correct final position by exchanging it with A[*n*]. If the procedure then discards node *n* from the heap - and it can do so by simply decrementing *A.heap-size* - the children of the root remain max-heaps, but the new root  element might violate the max-heap property. To restore the max-heap property, the procedure just calls **MAX-HEAPIFY(*A*, 1)**, which leaves a max-heap in *A*[1 : n - 1]. The **HEAPSORT** procedure then repeats this process for the max-heap of size *n* - 1 down to a heap of size 2.

##### HEAPSORT($A$, $n$)

```pseudocode
BUILD-MAX-HEAP(A, n)
for i = n downto 2
	exchange A[1] with A[i]
	A.heap-size -= 1
	MAX-HEAPIFY(A, 1)
```

The **HEAPSORT** procedure takes $O(n\lg n)$ time, since the call to **BUILD-MAX-HEAP** takes $O(n)$ time and each of the $n - 1$ calls to **MAX-HEAPIFY** takes $O(\lg n)$ time.





## 6.5	Priority queues

In this section, we present one of the most popular applications of a heap: as an efficient priority queue. As with heaps, priority queues come in two forms: max-priority queues and min-priority queues. We’ll focus here on how to implement max-priority queues, which are in turn based on max-heaps.

A ***==priority queue==*** is a data structure for maintaining a set $S$ of elements, each with an associated value called a ***==key==***. A ***==max-priority queue==*** supports the following operations:

- **INSERT($S$, $x$, $k$)** inserts the element $x$ with key $k$ into the set $S$, which is equivalent to the operation $S = S\bigcup \{x\} $.
- **MAXIMUM($S$)** returns the element of $S$ with the largest key.
- **EXTRACT-MAX($S$)** removes and returns the element of $S$ with the largest key.
- **INCREASE-KEY($S$, $x$, $k$)** increases the value of element $x$’s key to the new value $k$, which is assumed to be at least as large as $x$’s current key value.

A ***==min-priority queue==*** supports the operations alternatively.

One way to map between application objects and heap elements uses ***==handles==***, which are additional information stored in the objects and heap elements that give enough information to perform the mapping. 

Let’s see how to implement the operations of a max-priority queue using a max-heap. When a heap implements a priority queue, we instead treat each array element as a pointer to an object in the priority queue, so that the object is analogous to the satellite data when sorting. We further assume that each such object has an attribute *key*, which determines where in the heap the object belongs. For a heap implemented by an array $A$, we refer to $A[i]$.key.

The procedure **MAX-HEAP-MAXIMUM** implements the MAXIMUM operation in $\Theta(1)$ time, and **MAX-HEAP-EXTRACT-MAX** implements the operation **EXTRACT-MAX**. **MAX-HEAP-EXTRACT-MAX** is similar to the **for** loop body (line 3~5) of the HEAPSORT procedure. The running time of **MAX-HEAP-EXTRACT-MAX** is $O(\lg n)$, since it performs only a constant amount of work on top of the $O(\lg n)$ time for **MAX-HEAPIFY**, plus whatever overhead is incurred within **MAX-HEAPIFY** for mapping priority-queue objects to array indices.

##### MAX-HEAP-MAXIMUM($A$)

```pseudocode
if A.heap_size < 1
	error "heap underflow"
return A[1]
```

##### MAX-HEAP-EXTRACT-MAX($A$)

```pseudocode
max = MAX_HEAP_MAXIMUM(A)
A[1] = A[A.heap-size]
A.heap_size = A.heap_size - 1
MAX_HEAPIFY(A, 1)
return max
```

The procedure **MAX-HEAP-INCREASE-KEY** implements the **INCREASE-KEY** operation. It first verifies that the new key $k$ will not cause the key in the object $x$ to decrease, and if there is no problem, it gives $x$ the new key value. The procedure then finds the index $i$ in the array corresponding to object $x$, so that A[i] is $x$. Because increasing the key of A[i] might violate the max-heap property, the procedure then, in a manner reminiscent of the insertion loop, traverses a simple path from this node toward the root to find a proper place for the newly increased key. In addition to the overhead for mapping priority queue objects to array indices, the running time of **MAX-HEAP-INCREASE-KEY** on an *n*-element heap is $O(\lg n)$, since the path traced from the node updated in line 3 to the root has length $O(\lg n)$.

##### **MAX-HEAP-INCREASE-KEY($A$, $x$, $k$)**

```pseudocode
if k < x.key
	error "new key is smaller than current key"
x.key = k
find the index i in array A where object x occurs
while i > 1 and A[PARENT(i)].key < A[i].key
	exchange A[i] with A[PARENT(i)], updating the information that maps priority queue objects to array 		indices
	i = PARENT(i)
```

The procedure **MAX-HEAP-INSERT** implements the **INSERT** operation. It takes as inputs the array *A* implementing the max-heap, the new object $x$ to be inserted into the max-heap, and the size $n$ of array $A$. The procedure first verifies that the array has room for the new element. It then expands the max-heap by adding to the tree a new leaf whose key is $-\infty$. Then it calls **MAX-HEAP-INCREASE-KEY** to set the key of this new element to its correct value and maintain the max-heap property. The running time of **MAX-HEAP-INSERT** on an $n$-element heap is $O(\lg n)$ plus the overhead for mapping priority queue objects to indices.

##### MAX-HEAP-INSERT($A$, $x$, $n$)

```pseudocode
if A.heap_size == n
	error "heap overflow"
A.heap_size = A.heap_size + 1
k = x.key
x.key = -∞
A[A.heap_size] = x
map x to index heap_size in the array
MAX-HEAP-INCREASE-KEY(A, x, k)
```

In summary, a heap can support any priority-queue operation on a set of size $n$ in $O(\lg n)$ time, plus the overhead for mapping priority queue objects to array indices.





---

Copyright © Kevin Ye, 2023.

All Rights Reserved.
