//
// Created by Kevin Ye on 11/16/2023.
// Copyright © 2023 Kevin Ye. All rights reserved.

#include <stdio.h>

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void MaxHeapify(int *arr, int arrSize, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < arrSize && arr[l] > arr[largest]) largest = l;
    if (r < arrSize && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        Swap(&arr[i], &arr[largest]);
        MaxHeapify(arr, arrSize, largest);
    }
}

void BuildMaxHeap(int *arr, int arrSize) {
    for (int i = arrSize / 2 - 1; i >= 0; i--) MaxHeapify(arr, arrSize, i);
}

void HeapSort(int *arr, int arrSize) {
    BuildMaxHeap(arr, arrSize);

    for (int i = arrSize - 1; i >= 1; i--) {
        Swap(&arr[0], &arr[i]);
        arrSize--;
        MaxHeapify(arr, arrSize, 0);
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