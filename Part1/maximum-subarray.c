//
// Created by Kevin Ye on 10/15/2023.
// Copyright (c) KevinYe on 10/15/2023.

#include <stdio.h>

int maxSubArray(int const *nums, int numsSize) {
    // Check if the array is empty
    if (numsSize == 0) return 0;

    // Initialize maxSum and currentSum to the first element of the array
    int maxSum = nums[0];
    int currentSum = nums[0];

    // Iterate through the array
    for (int i = 1; i < numsSize; i++) {
        // If currentSum is less than 0, set it to the current element
        currentSum = currentSum < 0 ? nums[i] : currentSum + nums[i];
        // If maxSum is greater than currentSum, set it to maxSum
        maxSum = maxSum > currentSum ? maxSum : currentSum;
    }
    // Return the maxSum
    return maxSum;
}

int main(void) {
    // Initialize the array
    int arr[] = {13, -3, -25, 20, -3, -16,
            -23, 18, 20, -7, 12,
            -5, -22, 15, -4, 7};
    // Get the length of the array
    int len = sizeof(arr) / sizeof(arr[0]);
    // Call the maxSubArray function to get the maxSum
    int result = maxSubArray(arr, len);
    // Print the maxSum
    printf("%d\n", result);
    return 0;
}