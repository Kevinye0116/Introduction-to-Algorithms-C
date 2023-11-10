//
// Created by Kevin Ye on 10/15/2023.
// Copyright (c) KevinYe on 10/15/2023.

#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int const *arr, int low, int high) {
    if (low < high) {
        int part = partition(arr, low, high);

        quickSort(arr, low, part - 1);
        quickSort(arr, part + 1, high);
    }
}

int main(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("The original array is:");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);

    quickSort(arr, 0, size - 1);

    printf("\nThe sorted array is:");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    return 0;
}