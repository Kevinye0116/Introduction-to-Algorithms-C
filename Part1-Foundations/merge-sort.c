//
// Created by Kevin Ye on 10/15/2023.
// Copyright (c) KevinYe on 10/15/2023.


#include <stdio.h>

void merge(int *arr, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int *arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main(void) {
    int arr[] = {2, 4, 5, 7, 1, 2, 3, 6};
    int arr_size = sizeof(arr) / sizeof(arr[0]);


    printf("The original array is:");
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, 0, arr_size - 1);

    printf("\nThe sorted array is:  ");
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    return 0;
}