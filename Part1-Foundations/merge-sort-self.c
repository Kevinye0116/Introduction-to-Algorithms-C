//
// Created by Kevin Ye on 11/11/2023.
// Copyright (c) KevinYe on 11/11/2023.

#include <stdio.h>

void MergeSort(int *nums, int left, int right);

void Merge(int *nums, int left, int mid, int right);

int main(void) {
    int nums[] = {2, 4, 5, 7, 1, 2, 3, 6};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    printf("The original array is: ");
    for (int i = 0; i < numsSize; i++) printf("%d ", nums[i]);

    MergeSort(nums, 0, numsSize - 1);

    printf("\nThe sorted array is: ");
    for (int i = 0; i < numsSize; i++) printf("%d ", nums[i]);
    return 0;
}

void MergeSort(int *nums, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        MergeSort(nums, left, mid);
        MergeSort(nums, mid + 1, right);

        Merge(nums, left, mid, right);
    }
}

void Merge(int *nums, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = nums[left + i];
    for (j = 0; j < n2; j++) R[j] = nums[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) nums[k] = L[i++];
        else nums[k] = R[j++];
        k++;
    }
    while (i < n1) nums[k++] = L[i++];
    while (j < n2) nums[k++] = R[j++];
}