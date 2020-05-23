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
    int K;
    int lesser_count;
    int len_uncle_johny;
    int len[max];

    for (i = 0; i < T; i++) {
        scanf("%d", &N);

        for (j = 0; j < N; j++) {
                scanf("%d", &len[j]);
        }

        scanf("%d", &K);
        len_uncle_johny = len[K - 1];
        lesser_count = 0;

        //printf("\n\n===\n\nCASE 1\nlen_uncle_johny = %d\n\n", len_uncle_johny);
        for (j = 0; j < (K - 1); j++) {
            if ((len[j] < len_uncle_johny) || (len[j] == len_uncle_johny)) {
                //printf("%d is less-than-or-equal-to %d\n", len[j], len_uncle_johny);
                ++lesser_count;
            }
        }

        for (j = K; j < N; j++) {
            if (len[j] < len_uncle_johny) {
                //printf("%d is less-than %d\n", len[j], len_uncle_johny);
                ++lesser_count;
            }
        }

        result[i] = lesser_count + 1;
        //printf("\n===\n\n");
    }
}

void output(int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d\n", result[i]);
    }
}
