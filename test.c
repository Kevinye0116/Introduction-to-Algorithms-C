#include<stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void Del_findgcd(int a[], int n, int *f) {
    int count = 0;
    //delete
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            a[count] = a[i];
            printf("%d ", a[count]);
            count++;
        }
    }
    printf("\n");
    //find the greatest common divisor
    *f = a[0];
    for (int i = 1; i < count; i++) {
        *f = gcd(*f, a[i]);
    }
}

int main() {
    int gcd;
    int array[10] = {6, 8, 9, 11, 12, 13, 15, 16, 18, 19};
    Del_findgcd(array, 10, &gcd);
    printf("max common divisor is %d", gcd);
    return 0;
}