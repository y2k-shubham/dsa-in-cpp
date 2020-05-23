#include <stdio.h>
#include <string.h>

void inputAndProcess(int [], int);
void countingSort(int [], int [], int);
void output(int [], int);

int main() {
    int t;

    scanf("%d", &t);
    int result[t];

    inputAndProcess(result, t);
    output(result, t);

    return 0;
}

void inputAndProcess(int result[], int t) {
    int n;
    int i;
    int j;
    int k;
    int freq[101];
    int weight[30];
    int capacity[30];

    for (i = 0; i < t; i++) {
        scanf("%d", &n);
        for (j = 0; j < n; j++) {
            scanf("%d", &weight[j]);
        }
        for (j = 0; j < n; j++) {
            scanf("%d", &capacity[j]);
        }

        result[i] = 0;
        countingSort(weight, freq, n);
        countingSort(capacity, freq, n);

        for (j = 0, k = 0; k < n; ) {
            if (weight[j] <= capacity[k]) {
                result[i]++;
                j++;
                k++;
            } else {
                k++;
            }
        }
    }
}

void countingSort(int arr[], int freq[], int len) {
    int i;
    int j;
    int k;

    memset(freq, 0, (101 * sizeof(int)));

    for (i = 0; i < len; i++) {
        freq[arr[i]]++;
    }

    k = 0;
    for (i = 0; i < 101; i++) {
        for (j = 1; j <= freq[i]; j++) {
            arr[k++] = i;
        }
    }
}

void output(int result[], int t) {
    int i;

    for (i = 0; i < t; i++) {
        printf("%d\n", result[i]);
    }
}
