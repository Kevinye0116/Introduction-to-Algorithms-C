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
