# 7	Quicksort

***By Kevin Ye***

---

The quicksort algorithm has a worst-case running time of $\Theta(n^2)$ on an input array on $n$ numbers. Despite this low worst-case running time, quicksort is often the best practical choice for sorting because it is remarkably efficient on average: its expected running time is $\Theta(n\lg n)$ when all numbers are distinct, and the constant factors hidden in the $\Theta(n\lg n)$ notation are small. Unlike merge sort, it also has the advantage of sorting in place, and it works well even in virtual-memory environments.

> The learning of Quicksort Algorithm is divided into four parts.





## 7.1	Description of quicksort

Quicksort, like merge sort, applies the divide-and-conquer method introduced before. Here is the three-step divide-and-conquer process for sorting a subarray $A[p : r]$:

- **Divide** by partitioning (rearranging) the array $A[p : r]$ into two (possibly empty) subarrays $A[p : q - 1]$ (the ***low side***) and $A[q + 1 : r]$ (the ***high side***) such that each element in the low side of the partition is less than or equal to the ***pivot*** $A[q]$, which is, in turn, less than or equal to each element in the high side. Compute the index $q$ of the pivot as part of this partitioning procedure.
- **Conquer** by calling quicksort recursively to sort each of the subarrays $A[p : q - 1]$ and $A[q + 1 : r]$.
- **Combine** by doing nothing: because the two subarrays are already sorted, no work is needed to combine them. All elements in $A[p : q - 1]$ are sorted and less than or equal to $A[q]$, and all elements in $A[q + 1 : r]$ are sorted and greater than or equal to the pivot $A[q]$. The entire subarray $A[p : r]$ cannot help but be sorted!

The **QUICKSORT** procedure implements quicksort. To sort an entire $n$-element array $A[1 : n]$, the initial call is **QUICKSORT($A$, $1$, $n$)**. 

##### QUICKSORT($A$, $p$, $r$)

```pseudocode
if p < r
	// Partition the subarray around the pivot, which ends up in A[q].
	q = PARTITION(A, p, r)
	QUICKSORT(A, p, q - 1)	// recursively sort the low side
	QUICKSORT(A, q + 1, r)	// recursively sort the high side
```

#### Partitioning the array

The key to the algorithm is the **PARTITION** procedure, which rearranges the subarray $A[p : r]$ in place, returning the index of the dividing point between the two sides of the partition.

**PARTITION** always selects the element $x = A[r]$ as the pivot. As the procedure runs, each element falls into exactly one of four regions, some of which may be empty. At the start of each iteration of the **for** loop in lines 3~6, the regions satisfy certain properties. We state these properties as a loop invariant:

##### PARTITION($A$, $p$, $r$)

```pseudocode
x = A[r]						// the pivot
i = p - 1						// highest index into the low side
for j = p to r - 1				// process each element other than the pivot
	if A[j] <= x				// does this element belong on the low side?
		i += 1					// index of a new slot in the low side
		exchange A[i] with A[j]	// put this element there
exchange A[i + 1] with A[r]		// pivot goes just to the right of the low side
return i + 1					// new index of the pivot
```

> At the beginning of each iteration of the loop of lines 3~6, for any array index $k$, the following conditions hold:
>
> 1. if $p \leq k \leq i$, then $A[k] \leq x$;
> 2. if $i + 1 \leq k \leq j - 1$, then $A[k] > x$;
> 3. if $k = r$, then $A[k] = x$.

We need to show that this loop invariant is true prior to the first iteration, that each iteration of the loop maintains the invariant, that the loop terminates, and that correctness follows from the invariant when the loop terminates.

> The proving process of the correctness of the algorithm is omitted here.

The final two lines of **PARTITION** finish up by swapping the pivot with the leftmost element greater than $x$, thereby moving the pivot into its correct place in the partitioned array, and then returning the pivot’s new index. The output of **PARTITION** now satisfies the specifications given for the divide step. In fact, it satisfies a slightly stronger  condition: after line 3 of **QUICKSORT**, $A[q]$ is strictly less than every element of $A[q + 1 : r]$.





## 7.2	Performance of quicksort

The running time of quicksort depends on how balanced each partitioning is, which in turn depends on which elements are used as pivots. If the two sides of a partition are about the same size - the partitioning is balanced - then the algorithm runs asymptotically as fast as merge sort. If the partitioning is unbalanced, however, it can run asymptotically as slowly as insertion sort. To allow you to gain some intuition before diving into a formal analysis, this section informally investigates how quicksort performs under the assumptions of balanced versus unbalanced partitioning.

But first, let’s briefly look at the maximum amount of memory that quicksort requires. Although quicksort sorts in place according to the definition, the amount of memory it uses - aside from the array being sorted - is not constant. Since each recursive call requires a constant amount of space on the runtime stack, outside of the array being sorted, quicksort requires space proportional to the maximum depth of the recursion. As we’ll see now, that could be as bad as $\Theta(n)$ in the worst case.

#### Worst-case partitioning

The worst-case behavior for quicksort occurs when the partitioning produces one subproblem with $n - 1$ elements and one with $0$ elements. Let us assume that this unbalanced partitioning arises in each recursive call. The partitioning costs $\Theta(n)$ time. Since the recursive call on an array of size $0$ just returns without doing anything, $T(0)=\Theta(1)$. The recurrence for the running time is
$$
T(n) = T(n - 1) + T(0) + \Theta(n)
	 = T(n - 1) + \Theta(n).
$$
By summing the costs incurred at each level of the recursion, we obtain an arithmetic series, which evaluates to $\Theta(n^2)$. Indeed, the substitution method can be used to prove that the recurrence $T(n)=T(n-1)+\Theta(n)$ has the solution $T(n)=\Theta(n^2)$.

Thus, if the partitioning is maximally unbalanced at every recursive level of the algorithm, the running time is $\Theta(n^2)$. The worst-case running time of quicksort is therefore no better than that of insertion sort. Moreover, the $\Theta(n^2)$ running time occurs when the input array is already completely sorted - a situation in which insertion sort runs in $O(n)$ time.

#### Best-case partitioning

In the most even possible split, **PARTITION** produces two subproblems, each of size no more than $n/2$, since one is of size $[(n-1)//2]\leq n/2$ and one of size $[(n-1)//2]-1\leq n/2$. In this case, quicksort runs much faster. An upper bound on the running time can then be described by the recurrence
$$
T(n)=2T(n/2)+\Theta(n).
$$
This recurrence has the solution $T(n)=\Theta(n\lg n)$. Thus, if the partitioning is equally balanced at every level of the recursion, an asymptotically faster algorithm results.

#### Balanced partitioning

As the analyses will show, the average-case running time of quicksort is much closer to the best case than to the worst case. Suppose, for example, that the partitioning algorithm always produces a 9-10-1 proportional split, which at first blush seems quite unbalanced. We then obtain the recurrence
$$
T(n)=T(\frac{9n}{10})+T(\frac{n}{10})+\Theta(n),
$$
on the running time of quicksort. Every level of the recursion tree has cost $n$, until the recursion bottoms out in a base case at depth $\log_{10} f=\Theta(\lg n)$, and then the levels have cost at most $n$. The recursion terminates at depth $\log_{\frac{10}{9}} n=\Theta(\lg n)$. Thus with a 9-to-1 proportional split at every level of recursion, which intuitively seems highly unbalanced, quicksort runs in $O(n\lg n)$ time - asymptotically the same as if the split were right down the middle.  In fact, any split of *constant* proportionality yields a recursion tree of depth $\Theta(\lg n)$, where the cost at each level is $O(n)$. The running time is therefore $O(n\lg n)$ whenever the split has constant proportionality. The ratio of the split affects only the constant hidden in the $O$-notation.





## 7.3	A randomized version of quicksort

In exploring the average-case behavior of quicksort, we have assumed that all permutations of the input numbers are equally likely. This assumption does not always hold, however, judicious randomization can sometimes be added to an algorithm to obtain good expected performance over all inputs. For quicksort, randomization yields a fast and practical algorithm. Many software libraries provide a randomized version of quicksort as their algorithm of choice for sorting large data sets.

Instead of always using $A[r]$ as the pivot, a randomized version randomly chooses the pivot from the subarray $A[p:r]$, where each element in $A[p:r]$ has an equal probability of being chosen. It then exchanges that element with $A[r]$ before partitioning. Because the pivot is chosen randomly, we expect the split of the input array to be reasonably well balanced on average.

The changes to **PARTITION** and **QUICKSORT** are small. The new partitioning procedure, **RANDOMIZED-PARTITION**, simply swaps before performing the partitioning. The new quicksort procedure, **RANDOMIZED-QUICKSORT**, calls **RANDOMIZED-PARTITION** instead of **PARTITION**.

##### RANDOMIZED-PARTITION($A$, $p$, $r$)

```pseudocode
i = RANDOM(p, r)
exchange A[r] with A[i]
return PARTITION(A, p, r)
```

##### RANDOMIZED-QUICKSORT($A$, $p$, $r$)

```pseudocode
if p < r
	q = RANDOMIZED-PARTITION(A, p, r)
	RANDOMIZED-QUICKSORT(A, p, q - 1)
	RANDOMIZED-QUICKSORT(A, q + 1, r)
```



## 7.4	Analysis of quicksort

> This part is omitted in my personal notes.





---

Copyright © Kevin Ye, 2023.

All Rights Reserved.
