#include <stdio.h>

int main() {
    int A;
    int N;
    int K;
    int i;
    int limit;

    scanf("%d %d %d", &A, &N, &K);
    limit = N + 1;

    printf("%d", (A % limit));
    for (i = 2; i <= K; i++) {
        A /= limit;
        printf(" %d", (A % limit));
    }
    printf("\n");

    return 0;
}
