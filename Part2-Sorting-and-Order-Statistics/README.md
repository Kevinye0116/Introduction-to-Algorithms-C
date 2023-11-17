# Introduction

**_By Kevin Ye_**

---

This part presents several algorithms that solve the following **_sorting problem_**:

**Input:** A sequence of n numbers  <$a_{1}, a_{2}, \ldots , a_{n}$>.

**Output:** A permutation (reordering) <$a’_{1}, a’_{2}, \ldots , a’_{n}$> of the input sequence such that  $a’_{1} ≤ a’_{2} ≤ \ldots ≤ a’_{n}$ .

The input sequence is usually an *n*-element array, although it may be represented in some other fashion such as a linked list.



## The structure of the data

In practice, the numbers to be sorted are rarely isolated values. Each is usually part of a collection of data called a ***record***. Each record contains a ***key***, which is the value to be sorted. The remainder of the record consists of ***satellite data***, which are usually carried around with the key. In practice, when a sorting algorithm permutes the keys, it must permute the satellite data as well. If each record includes a large amount of satellite data, it often pays to permute an array of pointers to the records rather than the records themselves in order to minimize data movement.



## Why sorting?

Many computer scientists consider sorting to be the most fundamental problem in the study of algorithms. 

#### Sorting algorithms

We introduced two algorithms that sort *n* real numbers in Chapter 2. **Insertion sort** takes $\Theta(n^{2})$ time in the worst case. Because its inner loops are tight, however, it is a fast sorting algorithm for small input sizes. Moreover, unlike merge sort, it sorts ***in place***, meaning that at most a constant number of elements of the input array are ever stored outside the array, which can be advantageous for space efficiency. Merge sort has a better asymptotic running time, $\Theta(n\lg n)$, but the **MERGE** procedure it uses does not operate in place. (We’ll see a parallelized version of merge sort in Section 26.3)

This part introduces two more algorithms that sort arbitrary real numbers. ***Heapsort***, presented in Chapter 6, sorts *n* numbers in place in $O(n\lg n)$ time. It uses an important data structure, called a heap, which can also implement a priority queue.

***Quicksort***, in Chapter 7, also sorts *n* numbers in place, but its worst-case running time is $\Theta(n^2)$. Its expected running time is $\Theta(n\lg n)$, however, and ==it generally outperforms heapsort in practice.==  ~~Heapsort is quite quick in some circumstances.~~

The table following summarizes the running times of the sorting algorithms from Chapters 2and 6~8.

| Algorithm      | Worst-case running time | Average-case/expected running time |
| -------------- | ----------------------- | ---------------------------------- |
| Insertion Sort | $\Theta(n^2)$           | $\Theta(n^2)$                      |
| Merge Sort     | $\Theta(n\lg n)$        | $\Theta(n\lg n)$                   |
| Heap Sort      | $O(n\lg n)$             | __                                 |
| Quick Sort     | $\Theta(n^2)$           | $\Theta(n\lg n)$ (expected)        |
| Counting Sort  | $\Theta(k+n)$           | $\Theta(k+n)$                      |
| Radix Sort     | $\Theta(d(n+k))$        | $\Theta(d(n+k))$                   |
| Bucket Sort    | $\Theta(n^2)$           | $\Theta(n)$ (average-case)         |



#### Order statistics

The *i*th order statistic of a set of *n* numbers is the *i*th smallest number in the set. You can, of course, select the *i*th order statistic by sorting the input and indexing the *i*th element of the output. With no assumptions about the input distribution, thish method runs in $\Omega(n\lg n)$ time, as the lower bound proved in Chapter 8 shows.

Chapter 9 shows how to find the *i*th smallest element in $O(n)$ time, even when the elements are arbitrary real numbers. We present a randomized algorithm with tight pseudocode that runs in $\Theta(n^2)$ time in the worst case, but whose expected running time is $O(n)$. We also give a more complicated algorithm that runs in $O(n)$ worst-case time.

