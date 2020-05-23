#include <stdio.h>
#include <math.h>
#include <limits.h>

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
    int freq[10];
    int minimum[10];
    int smallest;
    int temp_1;
    int temp_2;
    int i;
    int j;

    for (i = 0; i < T; i++) {
        // input frequencies of candle of each number
        for (j = 0; j < 10; j++) {
            scanf("%d", &freq[j]);
        }

        // find minimum power of 10 that can't be represented
        if (freq[1] == 0) {
            minimum[0] = 1;
        } else {
            minimum[0] = pow(10, (freq[0] + 1));
        }

        // find minimum repeated digit that can't be represented
        for (j = 1; j < 10; j++) {
            temp_1 = freq[j];
            temp_2 = 0;

            while (temp_1 > 0) {
                temp_2 = (temp_2 * 10) + j;
                temp_1--;
            }
            temp_2 = (temp_2 * 10) + j;

            minimum[j] = temp_2;
        }

        smallest = INT_MAX;
        for (j = 0; j < 10; j++) {
            if (minimum[j] < smallest) {
                smallest = minimum[j];
            }
        }

        result[i] = smallest;
    }
}

void output(int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d\n", result[i]);
    }
}
