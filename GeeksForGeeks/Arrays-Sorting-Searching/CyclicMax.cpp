#include <stdio.h>
#define max(a, b) ((a > b) ? a : b)

int input(int [], int);
int findMax(int [], int, int);

int main() {
    int n;
    int sigma;
    int maxSum;

    printf("Enter n:\t");
    scanf("%d", &n);

    int arr[n];

    sigma = input(arr, n);
    maxSum = findMax(arr, n, sigma);

    printf("\nThe maximum cyclic sum of arr[i]*i is %d\n", maxSum);

    return 0;
}

int input(int arr[], int n) {
    int i;
    int sum;

    printf("Enter the values:-\n");

    sum = 0;
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    return sum;
}

int findMax(int arr[], int n, int sigma) {
    int i;
    int crrSum;
    int prevSum;
    int maxSum;

    prevSum = 0;
    for (i = 0; i < n; i++) {
        prevSum += i * arr[i];
    }

    maxSum = prevSum;
    for (i = 1; i < n; i++) {
        crrSum = prevSum + sigma - ((n - i) * arr[n - i]);
        maxSum = max(maxSum, crrSum);
        prevSum = crrSum;
    }

    return maxSum;
}
