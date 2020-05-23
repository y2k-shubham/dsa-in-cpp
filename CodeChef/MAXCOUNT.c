#include <stdio.h>
#include <string.h>

#define max 10001

void inputAndProcess(int [][2], int);
void output(int [][2], int);

int main() {
    int T;

    scanf("%uhd", &T);
    int result[T][2];

    inputAndProcess(result, T);
    output(result, T);

    return 0;
}

void inputAndProcess(int result[][2], int T) {
    int freq[max];
    int maxFreq;
    int maxNumber;
    int number;
    int N;
    int i;
    int j;

    for (i = 0; i < T; i++) {
        scanf("%uhd", &N);
        memset(freq, ((int) 0), (max * sizeof(int)));
        //int freq[max] = {(int) 0};
        maxFreq = 0;

        for (j = 1; j <= N; j++) {
            scanf("%uhd", &number);
            freq[number]++;

            if (freq[number] > maxFreq) {
                maxFreq = freq[number];
                maxNumber = number;
            } else if ((freq[number] == maxFreq) && (number < maxNumber)) {
                maxNumber = number;
            }
        }

        result[i][0] = maxNumber;
        result[i][1] = maxFreq;
    }
}

void output(int result[][2], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }
}
