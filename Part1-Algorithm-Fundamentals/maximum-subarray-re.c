//
// Created by Kevin Ye on 11/11/2023.
// Copyright (c) KevinYe on 11/11/2023.


#include <stdio.h>
#include <limits.h>

int MaxSubArray(const int *arr, int low, int high);

int MaxCrossing(const int *arr, int low, int mid, int high);

int main(void) {
    int arr[] = {13, -3, -25, 20, -3, -16,
            -23, 18, 20, -7, 12,
            -5, -22, 15, -4, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
    int answer = MaxSubArray(arr, 0, len - 1);
    printf("%d\n", answer);
    return 0;
}

// This function returns the maximum subarray sum
int MaxSubArray(const int *arr, int low, int high) {
    // If the array has only one element, then the maximum subarray sum is the element itself
    if (low == high) return arr[low];

    // Find the midpoint of the array
    int mid = (low + high) / 2;

    // Find the maximum subarray sum in the left side of the array
    int leftMax = MaxSubArray(arr, low, mid);
    // Find the maximum subarray sum in the right side of the array
    int rightMax = MaxSubArray(arr, mid + 1, high);
    // Find the maximum subarray sum crossing the midpoint
    int crossMax = MaxCrossing(arr, low, mid, high);

    // Return the maximum subarray sum
    return (leftMax > rightMax && leftMax > crossMax) ? leftMax : (rightMax > crossMax) ? rightMax : crossMax;
}

// This function returns the maximum subarray sum crossing the midpoint
int MaxCrossing(const int *arr, int low, int mid, int high) {
    // Initialize the left max subarray sum to the minimum value
    int leftMax = INT_MIN;
    // Initialize the sum of the left side of the array
    int sum = 0;

    // Iterate through the left side of the array
    for (int i = mid; i >= low; i--) {
        // Add the current element to the sum
        sum += arr[i];
        // Update the left max subarray sum if the current sum is greater than the left max subarray sum
        if (sum > leftMax) {
            leftMax = sum;
        }
    }

    // Initialize the right max subarray sum to the minimum value
    int rightMax = INT_MIN;
    // Initialize the sum of the right side of the array
    sum = 0;

    // Iterate through the right side of the array
    for (int i = mid + 1; i <= high; i++) {
        // Add the current element to the sum
        sum += arr[i];
        // Update the right max subarray sum if the current sum is greater than the right max subarray sum
        if (sum > rightMax) {
            rightMax = sum;
        }
    }

    // Return the sum of the left max subarray sum and the right max subarray sum
    return leftMax + rightMax;
}