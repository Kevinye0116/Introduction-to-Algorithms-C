//
// Created by Kevin Ye on 11/19/2023.
// Copyright (c) 2023 Kevin Ye. All rights reserved.

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void MaxHeapify(int *arr, int size, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < size && arr[l] > arr[largest]) largest = l;
    if (r < size && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        Swap(&arr[i], &arr[largest]);
        MaxHeapify(arr, size, largest);
    }
}

void Insert(int *arr, int *size, int key, int capacity) {
    if (*size >= capacity) {
        printf("Error! Queue overflow!\n");
        return;
    }

    (*size)++;
    int i = *size;
    arr[i] = key;

    while (i > 1 && arr[i / 2] < arr[i]) {
        Swap(&arr[i / 2], &arr[i]);
        i /= 2;
    }
}

int Maximum(const int *arr, const int *size) {
    if (*size < 1) return -1;
    return arr[1];
}

int ExtractMax(int *arr, int *size) {
    if (*size < 1) return -1;
    int max = arr[1];
    arr[1] = arr[*size];
    (*size)--;
    MaxHeapify(arr, *size, 1);
    return max;
}

void IncreaseKey(int *arr, int size, int i, int key) {
    if (i < 1 || i > size) {
        printf("Invalid index!\n");
        return;
    }
    if (key < arr[i]) {
        printf("Error! New key is smaller than current key!\n");
        return;
    }
    arr[i] = key;
    while (i > 1 && arr[i / 2] < arr[i]) {
        Swap(&arr[i], &arr[i / 2]);
        i /= 2;
    }
}

int main(void) {
    int arr[MAX_SIZE + 1];
    int size = 0;

    printf("This program supports following operations:\n"
           "1. Add an element to the array (operation code: insert)\n"
           "2. Return the element with the largest key (operation code: maximum)\n"
           "3. Remove and return the element with the largest key (operation code: extractmax)\n"
           "4. Increase the value of element x's key to the new value k (operation code: increasekey)\n"
           "5. End the program (operation code: exit)\n");
    char op[15];
    while (1) {
        scanf("%s", op);
        if (!strcmp(op, "exit")) return 0;
        else if (!strcmp(op, "insert")) {
            int key;
            scanf("%d", &key);
            Insert(arr, &size, key, MAX_SIZE);
        } else if (!strcmp(op, "maximum")) {
            int max = Maximum(arr, &size);
            if (max == -1) printf("Error! Queue underflow!\n");
            else printf("The maximum element: %d\n", max);
        } else if (!strcmp(op, "extractmax")) {
            int max = ExtractMax(arr, &size);
            if (max == -1) printf("Error! Queue underflow!\n");
            else printf("The maximum element extracted: %d\n", max);
        } else if (!strcmp(op, "increasekey")) {
            int index, new_key;
            scanf("%d %d", &index, &new_key);
            IncreaseKey(arr, size, index, new_key);
        } else {
            printf("There is something wrong with the operation code, please try again!\n");
        }
    }
}