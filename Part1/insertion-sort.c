//
// Created by Kevin Ye on 10/15/2023.
// Copyright (c) KevinYe on 10/15/2023

#include <stdio.h>

void selectionSort(int *arr, int arr_size) {
    // Iterate through the array
    for (int i = 0; i < arr_size - 1; i++) {
        // Initialize the minimum index
        int min_index = i;
        // Iterate through the array to find the minimum value
        for (int j = 0; j < arr_size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap the values at the current index and the minimum index
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

int main(void) {
    // Initialize the array
    int arr[] = {5, 2, 4, 6, 1, 3};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    // Print the original array
    printf("The original array is:");
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);

    // Sort the array
    selectionSort(arr, arr_size);
    // Print the sorted array
    printf("\nThe sorted array is:");
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    return 0;
}
