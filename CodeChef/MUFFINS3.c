#include <stdio.h>

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
    int N;

    for (i = 0; i < t; i++) {
        scanf("%d", &N);
        result[i] = (N / 2) + 1;
    }
}

void output(int result[], int t) {
    int i;

    for (i = 0; i < t; i++) {
        printf("%d\n", result[i]);
    }
}
