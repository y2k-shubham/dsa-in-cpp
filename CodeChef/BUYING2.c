#include <stdio.h>
#define max 100

void inputAndProcess(int [], int);
void output(int [], int);

int main() {
    int T;

    scanf("%d", &T);
    int result[T];

    inputAndProcess(result, T);
    output(result, T);

    return 0;
}

void inputAndProcess(int result[], int T) {
    int i;
    int j;
    int N;
    int X;
    int remainder;
    int sum;
    int price[max];

    for (i = 0; i < T; i++) {
        scanf("%d%d", &N, &X);
        sum = 0;

        for (j = 0; j < N; j++) {
            scanf("%d", &price[j]);
            sum += price[j];
        }

        remainder = sum % X;
        for (j = 0; j < N; j++) {
            if (price[j] <= remainder) {
                break;
            }
        }

        if (j < N) {
            result[i] = -1;
        } else {
            result[i] = sum / X;
        }
    }
}

void output(int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d\n", result[i]);
    }
}
