//
// Created by Kevin Ye on 10/15/2023.
// Copyright (c) KevinYe on 10/15/2023.


#include <stdio.h>

void merge(int *arr, int left, int middle, int right) {
    // two subarrays to be merged
    int i, j, k;
    // subarray sizes
    int n1 = middle - left + 1;
    int n2 = right - middle;
    // temp arrays to hold sorted subarrays
    int L[n1], R[n2];

    // copy elements of arr[] to L[] and R[]
    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[middle + 1 + j];

    // initial indexes of two subarrays to be merged
    i = 0;
    j = 0;
    k = left;

    // merge L[] and R[]
    while (i < n1 && j < n2) {
        // compare elements of both subarrays
        if (L[i] <= R[j]) {
            // copy the smaller element to the merged subarray
            arr[k] = L[i];
            // increment index of L[]
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        // increment index of merged subarray
        k++;
    }

    // copy remaining elements of L[] to merged subarray
    while (i < n1) arr[k++] = L[i++];
    // copy remaining elements of R[] to merged subarray
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int *arr, int left, int right) {
    // if array has only one element
    if (left < right) {
        // find the middle point
        int middle = left + (right - left) / 2;

        // sort left half
        mergeSort(arr, left, middle);
        // sort right half
        mergeSort(arr, middle + 1, right);

        // merge left and right half
        merge(arr, left, middle, right);
    }
}

int main(void) {
    // create an array
    int arr[] = {2, 4, 5, 7, 1, 2, 3, 6};
    // get the size of the array
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    // print the original array
    printf("The original array is:");
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);

    // sort the array
    mergeSort(arr, 0, arr_size - 1);

    // print the sorted array
    printf("\nThe sorted array is:  ");
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    return 0;
}