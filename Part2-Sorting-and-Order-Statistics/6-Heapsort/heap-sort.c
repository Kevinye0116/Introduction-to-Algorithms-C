//
// Created by Kevin Ye on 11/16/2023.
// Copyright © 2023 Kevin Ye. All rights reserved.

#include <stdio.h>

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void BuildMaxHeap(int *arr, int arrSize) {
    
}

void HeapSort(int *arr, int arrSize) {
    BuildMaxHeap(arr, arrSize);

    for (int i = arrSize - 1; i >= 1; i--) {
        Swap(&arr[0], &arr[i]);
        arrSize--;
        MaxHeapify(arr, 0);
    }
}


int main(void) {
    int arr[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("The original array is:");
    for (int i = 0; i < arrSize; i++) printf("%d ", arr[i]);
    printf("\n");

    HeapSort(arr, arrSize);

    printf("The sorted array is : ");
    for (int i = 0; i < arrSize; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}