# 8	Sorting in Linear Time

***By Kevin Ye***

---

We have now seen a handful of algorithms that can sort $n$ numbers in $O(n\lg n)$ time. Whereas merge sort and heapsort achieve this upper bound in the worst case, quicksort achieves it on average. Moreover, for each of these algorithms, we can produce a sequence of $n$ input numbers that causes the algorithm to run in $\Omega(n\lg n)$ time.

These algorithms share an interesting property: *the sorted order they determine is based only on comparisons between the input elements*. We call such sorting algorithms ***comparison sorts***. All the sorting algorithms introduced thus far are comparison sorts.

In Section 8.1, we’ll prove that any comparison sort must make $\Omega(n\lg n)$ comparisons in the worst case to sort $n$ elements. Thus, merge sort and heapsort are asymptotically optimal, and no comparison sort exists that is faster by more than a constant factor.

Section 8.2, 8.3 and 8.4 examine three sorting algorithms - counting sort, radix sort, and bucket sort - that run in linear time on certain types of inputs. Of course, these algorithms use operations other than comparisons to determine the sorted order. Consequently, the $\Omega(n\lg n)$ lower bound does not apply to them.





## 8.1	Lower bounds for sorting

A comparison sort uses only comparisons between elements to gain order information about an input sequence $\left \langle a_1,a_2,\cdots,a_n\right \rangle$. That is, given two elements $a_i$ and $a_j$, it performs one of the tests $a_i<a_j$,$a_i\leqslant a_j$,$a_i=a_j$,$a_i\geqslant a_j$, or $a_i>a_j$ to determine their relative order. It may not inspect the values of the elements or gain order information about them in any other way.

Since we are proving a lower bound, we assume without loss of generality in this section that all the input elements are distinct. After all, a lower bound for distinct elements applies when elements may or may not be distinct. Consequently, comparisons of the form $a_i=a_j$ are useless, which means that we can assume that no comparisons for exact equality occur. Moreover, the comparisons $a_i\leqslant a_j$, $a_i\geqslant a_j$, $a_i>a_j$, and $a_i<a_j$ are all equivalent in that they yield identical information about the relative order of $a_i$ and $a_j$. We therefore assume that all comparisons have the form $a_i\leqslant a_j$.



### The decision-tree model

We can view comparison sorts abstractly in terms of decision trees. A ***decision tree*** is a full binary tree (each node is either a leaf or has both children) that represents the comparisons between elements that are performed by a particular sorting algorithm operating on an input of a given size. Control, data movement, and all other aspects of the algorithm are ignored.

A decision tree has each internal node annotated by $i:j$ for son $i$ and $j$ in the rang $1\leqslant i$, $j\leqslant n$, where $n$ is the number of elements in the input sequence. We also annotate each leaf by a permutation $\langle \pi(1), \pi(2),\dots,\pi(n)\rangle$.Indices in the internal nodes and the leaves always refer to the original positions of the array elements at the start of the sorting algorithm. The execution of the comparison sorting algorithm corresponds to tracing a simple path from the root of the decision tree down to a leaf. Each internal node indicates a comparison $a_i\leqslant a_j$. The left subtree then dictates subsequent comparisons once we know that $a_i\leqslant a_j$, and the right subtree dictates subsequent comparisons when $a_i>a_j$. Arriving at a leaf, the sorting algorithm has established the ordering $a_{\pi(1)}\leqslant a_{\pi(2)}\leqslant \cdots \leqslant a_{\pi(n)}$. Because any correct sorting algorithm must be able to produce each permutation of its input, each of the $n!$ permutations on $n$ elements must appear as at least one of the leaves of the decision tree for a comparison sort to be correct. Furthermore, each of these leaves must be reachable from the root by a downward path corresponding to an actual execution of the comparison sort. Thus, we consider only decision trees in which each permutation appears as a reachable leaf.

### A lower bound for the worst case

The length of the longest simple path from the root of a decision tree to any of its reachable leaves represents the worst-case number of comparisons that the corresponding sorting algorithm performs. Consequently, the worst-case number of comparisons for a given comparison sort algorithm  equals the height of its decision tree. A lower bound on the heights of all decision trees in which each permutation appears as a reachable leaf is therefore a lower bound on the running time of any comparison sort algorithm. The following theorem establishes such a lower bound.

##### Theorem 8.1

>  Any comparison sort algorithm requires $\Omega(n\lg n)$ comparisons in the worst case.

##### Corollary 8.2

> Heapsort and merge sort are asymptotically optimal comparison sorts.





## 8.2	Counting sort

***Counting sort*** assumes that each of the $n$ input elements is an integer in the range $0$ to $k$, for some integer $k$. It runs in $\Theta(n+k)$ time, so that when $k=O(n)$, counting sort runs in $\Theta(n)$ time.

Counting sort first determines, for each input element $x$, the number of elements less than or equal to $x$. It then uses this information to place element $x$ directly into the output array. We must modify this scheme slightly to handle the situation in which several elements have the same value, since we do not want them all to end up in the same position.

The **COUNTING-SORT** procedure takes as input an array $A[1:n]$, the size $n$ of this array, and the limit $k$ on the nonnegative integer values in $A$. It returns its sorted output in the array $B[1:n]$ and uses an array $C[0:k]$ for temporary working storage.

##### COUNTING-SORT($A$, $n$, $k$)

```pseudocode
let B[1 : n] and C[0 : k] be new arrays
for i = 0 to k
	C[i] = 0
for j = 1 to n
	C[A[j]] = C[A[j]] + 1
// C[i] now contains the number of elements equal to i.
for i = 1 to k
	C[i] = C[i] + C[i - 1]
// C[i] now contains the number of elements less than or equal to i
// Copy A to B, starting from the end of A.
for j = n downto 1
	B[C[A[j]]] = A[j]
	C[A[j]] = C[A[j]] - 1			// to hancle duplicate values
return B
```

After the **for** loop of lines 2~3 initializes the array $C$ to all zeros, the **for** loop of line 4~5 makes a pass over the array $A$ to inspect each input element. Each time it finds an input element whose value is $i$, it increments $C[i]$. Thus, after line 5, $C[i]$ holds the number of input elements equal to $i$ for each integer $i=0,1,\dots,k$. Lines 7~8 determine for each $i=0,1,\dots,k$ how many input elements are less than or equal to $i$ by keeping a running sum of the array $C$.

Finally, the **for** loop of lines 11~13 makes another pass over $A$, but in reverse, to place each element $A[j]$ into its correct sorted position in the output array $B$. If all $n$ elements are distinct, then when line 11 is first entered, for each $A[j]$, the value $C[A[j]]$ is the correct final position of $A[j]$ in the output array, since there are $C[A[j]]$ elements less than or equal to $A[j]$. Because the elements might not be distinct, the loop decrements $C[A[j]]$ each time it places a value $A[j]$ into $B$. Decrementing $C[A[j]]$ causes the previous element in $A$ with a value equal to $A[j]$, if one exists, to go to the position immediately before $A[j]$ in the output array $B$.

Counting sort can beat the lower bound of $\Omega(n\lg n)$ proved before because it is not a comparison sort. In fact, no comparisons between input elements occur anywhere in the code. Instead, counting sort uses the actual values of the elements to index into an array. The $\Omega(n\lg n)$ lower bound for sorting does not apply when we depart from the comparison sort model.

An important property of counting sort is that it is ***stable***: elements with the same value appear in the output array in the same order as they do in the input array. That is, it breaks ties between two elements by the rule that whichever element appears first in the input array appears first in the output array. Normally, the property of stability is important only when satellite data are carried around with the element being sorted. Counting sort’s stability is important for another reason: counting sort is often used as a subroutine in radix sort. ==In order for radix sort to work correctly, counting sort must be stable.==





## 8.3	Radix sort

***Radix sort*** is the algorithm used by the card-sorting machines. The cards have 80 columns, and in each column a machine can punch a hole in one of 12 places. The sorter an be mechanically “programmed” to examine a given column of each card in a deck and distribute the card into one of 12 bins depending on which place has been punched. An operator can then gather the cards bin by bin, so that cards with the first place punched are on top of cards with the second place punched, and so on.

> This part would be omitted.





## 8.4	Bucket sort

***Bucket sort*** assumes that the input is drawn from a uniform distribution and has an average-case running time of $O(n)$. Like counting sort, bucket sort is fast because it assumes something about the input. Whereas counting sort assumes that the input consists of integers in a small range, bucket sort assumes that the input is generated by a random process that distributes elements uniformly and independently over the interval $\left[ 0,1\right)$.

Bucket sort divides the interval $\left[ 0,1\right)$ into $n$ equal-sized subintervals, or ***buckets***, and then distributes the $n$ input numbers into the buckets. Since the inputs are uniformly and independently distributed over $\left[ 0,1\right)$, we do not expect many numbers to fall into each bucket. To produce the output, we simply sort the numbers in each bucket and then go through the buckets in order, listing the elements in each.

> This part would be omitted.





---

Copyright © Kevin Ye, 2023.

All Rights Reserved.
