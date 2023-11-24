//
// Created by Kevin Ye on 11/23/2023.
// Copyright (c) KevinYe on 11/23/2023.

#include <stdio.h>
#include <stdlib.h>

void CountingSort(int *arr, int n);

int main(void) {
    int num[] = {4, 2, 3, 1, 5, 2, 3, 1};
    int numSize = sizeof(num) / sizeof(num[0]);

    printf("The original array is:");
    for (int i = 0; i < numSize; i++) printf("%d ", num[i]);
    printf("\n");

    CountingSort(num, numSize);

    printf("The sorted array is : ");
    for (int i = 0; i < numSize; i++) printf("%d ", num[i]);
    return 0;
}

void CountingSort(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) max = (max > arr[i]) ? max : arr[i];

    int count[max + 1];
    for (int i = 0; i <= max; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[arr[i]]++;

    for (int i = 1; i <= max; i++) count[i] += count[i - 1];
    int *output = (int *) calloc(sizeof(int), n);
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}