//
// Created by Kevin Ye on 11/14/2023.
// Copyright © 2023 Kevin Ye. All rights reserved.

#include <stdio.h>
#include <limits.h>

int MaxSubArray(const int *arr, int low, int high);

int FindMaxCrossingSubArray(const int *arr, int low, int mid, int high);

int main(void) {
    int arr[] = {13, -3, -25, 20, -3, -16,
            -23, 18, 20, -7, 12,
            -5, -22, 15, -4, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
    int answer = MaxSubArray(arr, 0, len - 1);
    printf("%d\n", answer);
    return 0;
}

int MaxSubArray(const int *arr, int low, int high) {
    if (low == high) return arr[low];

    int mid = (low + high) / 2;

    int left_max = MaxSubArray(arr, low, mid);
    int right_max = MaxSubArray(arr, mid + 1, high);
    int crossing_max = FindMaxCrossingSubArray(arr, low, mid, high);

    return (left_max > right_max && left_max > crossing_max) ? left_max : (right_max > crossing_max) ? right_max : crossing_max;
}

int FindMaxCrossingSubArray(const int *arr, int low, int mid, int high) {
    int left_sum = INT_MIN;
    // int max_left, max_right;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            // max_left = i;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            // max_right = i;
        }
    }
    return left_sum + right_sum;
}