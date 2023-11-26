# 9	Medians and Order Statistics

***By Kevin Ye***

---

The $i$th ***order statistic*** of a set of $n$ elements is the $i$th smallest element. For example, the ***minimum*** of a set is the first order statistic ($i=1$), and the ***maximum*** is the $n$th order statistic ($i=n$). A ***median***, informally, is the “halfway point” of the set. When $n$ is odd, the median is unique, occurring at $i=(n+1)/2$. When $n$ is even, there are two medians, the ***lower median*** occurring at $i=n/2$ and the ***upper median*** occurring at $i=n/2+1$. Thus, regardless of the parity of $n$, medians occur at $i=\left \lfloor(n+1)/2\right \rfloor$ and $i=\left \lceil(n+1)/2\right \rceil$. For simplicity in this text, however, we consistently use the phrase “the median” to refer to the lower median.

This chapter addresses the problem of selecting the $i$th order statistic from a set of $n$ distinct numbers. We assume for convenience that the set contains distinct numbers, although virtually everything that we do extends to the situation in which a set contains repeated values. We formally specify the ***selection problem*** as follows:

- **Input**: A set $A$ of $n$ distinct numbers and an integer $i$, with $1\leqslant i\leqslant n$.
- **Output**: The element $x \in A$ that is larger than exactly $i-1$ other elements of $A$.

We can solve the selection problem in $O(n\lg n)$ time simply by sorting the numbers using heapsort or merge sort and then outputting the $i$th element in the sorted array. This chapter presents asymptotically faster algorithms.

Section 9.1 examines the problem of selecting the minimum and maximum of a set of elements. More interesting is the general selection problem, which we investigate in the subsequent two sections. Section 9.2 analyzes a practical randomized algorithm that achieves an $O(n)$ expected running time, assuming distinct elements. Section 9.3 contains an algorithm of more theoretical interest that achieves the $O(n)$ running time in the worst case.



## 9.1	Minimum and maximum

To obtain an upper bound of $n-1$ comparisons, just examine each element of the set in turn and keep track of the smallest element seen so far. The **MINIMUM** procedure assumes that the set resides in array $A[1:n]$.

##### MINIMUM($A$, $n$)

```pseudocode
min = A[1]
for i = 2 to n
	if min > A[i]
		min = A[i]
return min
```

It’s no more difficult to find the maximum with $n-1$ comparisons.

Is this algorithm for minimum the best we can do? Yes, because it turns out that there’s a lower bound of $n-1$ comparisons for the problem of determining the minimum. Think of any algorithm that determines the minimum as a tournament among the elements. Each comparison is a match in the tournament in which the smaller of the two elements wins. Since every element except the winner must lose at least one match, we can conclude that $n-1$ comparisons are necessary to determine the minimum. Hence the algorithm **MINIMUM** is optimal with respect to the number of comparisons performed.

### Simultaneous minimum and maximum

Some applications need to find both the minimum and the maximum of a set of $n$ elements.

Of course, we can determine both the minimum and the maximum of $n$ elements using $\Theta(n)$ comparisons. We simply find the minimum and maximum independently, using $n-1$ comparisons for each, for a total of $2n-2=\Theta(n)$ comparisons.

Although $2n-2$ comparisons is asymptotically optimal, it is possible to improve the leading constant. We can find both the minimum and the maximum using at most $3\left \lfloor n/2 \right \rfloor$ comparisons. The trick is to maintain both the minimum and maximum elements seen thus far. Rather than processing each element of the input by comparing it against the current minimum and maximum, at a cost of $2$ comparisons per element, process elements in pairs. Compare pairs of elements from the input first *with each other*, and then compare the smaller with the current minimum and the larger to the current maximum, at a cost of $3$ comparisons for every $2$ elements.

How you set up initial values for the current minimum and maximum depends on whether $n$ is odd or even. If $n$ is odd, set both the minimum and maximum to the value of the first element, and then process the rest of the elements in pairs. If $n$ is even, perform $1$ comparison on the first $2$ elements to determine the initial values of the minimum and maximum, and then process the rest of the elements in pairs as in the case for odd $n$.

If $n$ is odd, then $3\left \lfloor n/2 \right \rfloor$ comparisons occur. If $n$ is even, $1$ initial comparison occurs, followed by another $3(n-1)/2$ comparisons, for a total of $\frac {3n}{2}-2$. Thus, in either case, the total number of comparisons is at most $3\left \lfloor n/2 \right \rfloor$.



## 9.2	Selection in expected linear time

The general selection problem - finding the $i$th order statistic for any value of $i$ - appears more difficult than the simple problem of finding a minimum. Yet, surprisingly, the asymptotic running time for both problems is the same: $\Theta(n)$. This section presents a divide-and-conquer algorithm for the selection problem. The algorithm R**ANDOMIZED-SELECT** is modeled after the quicksort algorithm. Like quicksort it partitions the input array recursively. But unlike quicksort, which recursively processes both sides of the partition, **RANDOMIZED-SELECT** works on only one side of the partition. This difference shows up in the analysis: whereas quicksort has an expected running time of $\Theta(n\lg n)$, the expected running time of **RANDOMIZED-SELECT** is $\Theta(n)$, assuming that the elements are distinct.

**RANDOMIZED-SELECT** uses the procedure **RANDOMIZED-PARTITION** introduced before. Like **RANDOMIZED-QUICKSORT**, it is a randomized algorithm, since its behavior is determined in part by the output of a random-number generator. The **RANDOMIZED-SELECT** procedure returns the $i$th smallest element of the array $A[p:r]$, where $1\leqslant i \leqslant r-p+1$.

##### RANDOMIZED-SELECT($A$, $p$, $r$, $i$)

```pseudocode
if p == r
	return A[p] // 1<=i<=r-p+1 when p == r means that i = 1
q = RANDOMIZED-PARTITION(A, p, r)
k = q - p + 1
if i == k
	return A[q] //the pivot value is the answer
else if i < k
	return RANDOMIZED-SELECT(A, p, q - 1, i)
else return RANDOMIZED-SELECT(A, q + 1, r, i - k)
```

Line $1$ checks for the base case of the recursion, in which the subarray $A[p:r]$ consists of just one element. In this case, $i$ must equal $1$, and line $2$ simply returns $A[p]$ as the $i$th smallest element. Otherwise, the call to **RANDOMIZED-PARTITION** in line $3$ partitions the array $A[p:r]$ into two (possibly empty) subarrays $A[p:q-1]$ and $A[q+1:r]$ such that each element of $A[p:q-1]$ is less than or equal to $A[q]$, which in turn is less than each element of $A[q+1:r]$. As in quicksort, we’ll refer to $A[q]$ as the ***pivot*** element. Line $4$ computes the number $k$ of elements in the subarray $A[p:q]$, that is, the number of elements in the low side of the partition, plus $1$ for the pivot element. Line 5 then checks whether $A[q]$ is the $i$th smallest element. If it is, then line $6$ returns $A[q]$. Otherwise, the algorithm determines in which of the two subarrays $A[p:q-1]$ and A[q+1:r] the $i$th smallest element lies. If $i<k$, then the desired element lies on the low side of the partition, and line $8$ recursively selects it from the subarray. If $i>k$, however, then the desired element lies on the high side of the partition. Since we already know $k$ values that are smaller than the $i$th smallest element of $A[p:r]$ - namely, the elements of $A[p:q]$ - the desired element is the $(i-k)$th smallest element of $A[q+1:r]$, which line $9$ finds recursively. The code appears to allow recursive calls to subarrays with $0$ elements.

The worst-case running time for **RANDOMIZED-SELECT** is $\Theta(n^2)$, even to find the minimum, because it could be extremely unlucky and always partition around the largest remaining element before identifying the $i$th smallest when only one element remains.

##### Lemma 9.1

> A partitioning is helpful with probability at least $1/2$.

##### Theorem 9.2

> The procedure **RANDOMIZED-SELECT** on an input array of $n$ distinct elements has an expected running time of $\Theta(n)$.



## 9.3	Selection in worst-case linear time

We’ll now examine a remarkable and theoretically interesting selection algorithm whose running time is $\Theta(n)$ in the worst case. Although the **RANDOMIZED-SELECT** algorithm achieves linear expected time, we saw that its running time in the worst case was quadratic. The selection algorithm presented in this section achieves linear time in the worst case, but it is not nearly as practical as **RANDOMIZED-SELECT**. It is mostly of theoretical interest.

> We’ll just omit it then.



---

##	Chapter notes

The source code of R**ANDOMIZED-SELECT** provided by ChatGPT is slightly different from the pseudocode provided by the book.

```c
//
// Created by Kevin Ye on 11/26/2023.
// Copyright (c) KevinYe on 11/26/2023.

#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int QuickSelect(int arr[], int l, int r, int k) {
    if (l <= r) {
        int pivotIndex = l + rand() % (r - l + 1);
        int pivot = arr[pivotIndex];
        Swap(&arr[pivotIndex], &arr[r]);

        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (arr[j] <= pivot) {
                i++;
                Swap(&arr[i], &arr[j]);
            }
        }
        Swap(&arr[i + 1], &arr[r]);

        int pivotPos = i + 1;

        if (pivotPos == k) {
            return arr[pivotPos];
        } else if (pivotPos < k) {
            return QuickSelect(arr, pivotPos + 1, r, k);
        } else {
            return QuickSelect(arr, l, pivotPos - 1, k);
        }
    }
    return -1;
}

int main(void) {
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 6;

    int result = QuickSelect(arr, 0, n - 1, k - 1);

    if (result != -1) {
        printf("The  %dth smallest number is %d\n", k, result);
    } else {
        printf("No such number\n");
    }
    return 0;
}
```





---

Copyright © Kevin Ye, 2023.

All Rights Reserved.
