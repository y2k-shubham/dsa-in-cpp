#include <stdio.h>

void inputAndProcess(int [], int);
int inputAndFindSum(int);
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
    int sum;
    int N;
    int K;

    for (i = 0; i < T; i++) {
        scanf("%d%d", &N, &K);
        sum = inputAndFindSum(N);

        //printf("\nsum = %d\n", sum);
        if (!(K % 2)) {
            //printf("since K = %d is even, so final answer is %d\n", K, sum % 2);
            result[i] = sum % 2;
        } else {
            if (sum % 2) {
                result[i] = 0;
            } else {
                result[i] = 1;
            }
            //printf("since K = %d is odd , so final answer is %d\n\n", K, result[i]);
        }
    }
}

int inputAndFindSum(int N) {
    int i;
    int num;
    int sum;

    sum = 0;
    for (i = 0; i < N; i++) {
        scanf("%d", &num);
        sum += num;
    }

    return sum;
}

void output(int result[], int T) {
    int i;
    char * answer[] = {"odd", "even"};

    for (i = 0; i < T; i++) {
        printf("%s\n", answer[result[i]]);
    }
}
