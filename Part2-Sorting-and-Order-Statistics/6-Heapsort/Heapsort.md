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

