//
// Created by Kevin Ye on 11/16/2023.
// Copyright © 2023 Kevin Ye. All rights reserved.

#include <stdio.h>

void InsertionSort(int *arr, int arrSize);

int main(void) {
    int arr[] = {5, 2, 4, 6, 1, 3};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("The original array is:");
    for (int i = 0; i < arrSize; i++) printf("%d ", arr[i]);
    printf("\n");

    InsertionSort(arr, arrSize);

    printf("The sorted array is : ");
    for (int i = 0; i < arrSize; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

void InsertionSort(int *arr, int arrSize) {
    for (int i = 2; i < arrSize; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j > 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}