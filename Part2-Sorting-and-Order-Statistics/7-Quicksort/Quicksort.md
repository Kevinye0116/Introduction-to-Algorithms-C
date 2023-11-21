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

The final two lines of **PARTITION** finish up by swapping the pivot with the leftmost element greater than $x$, thereby moving the pivot into its correct place in the partitioned array, and then returning the pivot’s new index.