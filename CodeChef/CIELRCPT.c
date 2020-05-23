#include <stdio.h>
#include <math.h>

void inputAndProcess(int [], int);
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
    int i;
    int p;
    int index;
    int prices[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

    for (i = 0; i < t; i++) {
        scanf("%d", &p);
        result[i] = 0;

        //printf("\n\nFor p = %d\n\n", p);
        while (p > 0) {
            index = (int) floor(log2f(p));
            index = (index >= 12) ? 11 : index;

            /*
            printf("\nWhen p = %d\n", p);
            printf("index = %d\n", index);
            printf("prices[index] = %d\n", prices[index]);
            printf("p / prices[index] = %d\n", (p / prices[index]));
            printf("p = %d\n\n", (p % prices[index]));
            */

            result[i] += p / prices[index];
            p %= prices[index];
        }
    }
}

void output(int result[], int t) {
    int i;

    for (i = 0; i < t; i++) {
        printf("%d\n", result[i]);
    }
}
