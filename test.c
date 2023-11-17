//
// Created by Kevin Ye on 11/16/2023.
//

#include<stdio.h>

#define SIZE 5

int sets[SIZE][SIZE] = {0};

//元素是否在集合内
int inset(int key, int number[]) {
    for (int i = 0; i < SIZE; i++) {
        if (key == number[i])
            return 1;
    }
    return 0;
}

//对每个集合进行排序
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

//找集合的交集
int findintersection(int a[], int b[]) {
    int i = 0;
    int j = 0;
    while (i < SIZE && j < SIZE) {
        if (a[i] < b[j]) {
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else
            i++;
        j++;
    }
}

//主函数
int main(void) {

    int intersection[5] = {0};
    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &sets[i][j]);
        }
    }
    for (int i = 0; i < 5; i++) {

    }
}