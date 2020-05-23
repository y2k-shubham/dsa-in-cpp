#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int cmpfunc(const void *, const void *);
void input(int [], int);
int findMinDiff(int [], int);
void output(int [], int);

int main() {
    int T;
    int N;
    int numbers[5000];
    int i;

    scanf("%d", &T);
    int result[T];

    for (i = 0; i < T; i++) {
        scanf("%d", &N);
        input(numbers, N);
        qsort(numbers, N, sizeof(int), cmpfunc);

        //printf("\nAfter sorting, the array is:-\n");
        //output(numbers, N);

        result[i] = findMinDiff(numbers, N);
    }

    output(result, T);

    return 0;
}

int cmpfunc(const void * n1, const void * n2) {
    return ((*((int *) n1)) - (*((int *) n2)));
}

void input(int numbers[], int N) {
    int i;

    for (i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }
}

int findMinDiff(int numbers[], int N) {
    int minDiff;
    int temp;
    int i;

    minDiff = INT_MAX;
    for (i = 1; i < N; i++) {
        if ((temp = abs(numbers[i] - numbers[i - 1])) < minDiff) {
            minDiff = temp;
        }
    }

    return minDiff;
}

void output(int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d\n", result[i]);
    }
}
