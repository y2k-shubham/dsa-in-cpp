#include <stdio.h>

void inputAndProcess(int [], int);
void output(int [], char * [], int);

int main() {
    int T;
    char * result[] = {"No", "Yes"};

    scanf("%d", &T);
    int answer[T];

    inputAndProcess(answer, T);
    output(answer, result, T);

    return 0;
}

void inputAndProcess(int answer[], int T) {
    int i;
    int j;
    int sum;
    int demand;
    int noOfElephants;
    int noOfCandies;

    for (i = 0; i < T; i++) {
        scanf("%d %d", &noOfElephants, &noOfCandies);
        sum = 0;

        for (j = 1; j <= noOfElephants; j++) {
            scanf("%d", &demand);
            sum += demand;
        }

        if (sum <= noOfCandies) {
            answer[i] = 1;
        } else {
            answer[i] = 0;
        }
    }
}

void output(int answer[], char * result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%s\n", result[answer[i]]);
    }
}
