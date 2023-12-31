//
// Created by Kevin Ye on 11/21/2023.
// Copyright  (c) 2023 Kevin Ye. All rights reserved.


#include <stdio.h>
#include <time.h>

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void QuickSort(int *arr, int low, int high) {
    if (low < high) {
        int part = Partition(arr, low, high);
        QuickSort(arr, low, part - 1);
        QuickSort(arr, part + 1, high);
    }
}

int main(void) {
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    clock_t start_time = clock();

    printf("The original array is:");
    for (int i = 0; i < arrSize; i++) printf("%d ", arr[i]);
    printf("\n");

    QuickSort(arr, 0, arrSize - 1);

    printf("The sorted array is : ");
    for (int i = 0; i < arrSize; i++) printf("%d ", arr[i]);
    printf("\n");

    clock_t end_time = clock();
    double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.6lf seconds\n", elapsed_time);

    return 0;
}