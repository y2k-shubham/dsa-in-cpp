#include <cstdio>
#include <iostream>
#include <string.h>

using namespace std;

void input(int [], int);
void output(int [], int);
void compute(int [], int [], int);

int main() {
    int n;

    cin >> n;
    int num[n];
    int result[n];

    input(num, n);
    compute(num, result, n);
    output(result, n);

    return 0;
}

void input(int num[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        cin >> num[i];
    }
}

void compute(int num[], int result[], int n) {
    int rem[10];
    int numOrig;
    int numCopy;
    int digit;
    int sum;
    int i;
    int j;

    rem[0] = 1;
    rem[1] = 0;

    for (i = 0; i < n; i++) {
        numOrig = numCopy = num[i];
        memset(&rem[2], -1, 8);
        sum = 0;

        printf("\nnum = %d\n", numOrig);

        while (numCopy > 0) {
            // Extract a digit
            digit = numCopy % 10;
            numCopy /= 10;

            // Find remainder, if not already found
            if (rem[digit] < 0) {
                rem[digit] = numOrig % digit;
            }

            printf("rem by %d = %d\t", digit, rem[digit]);

            // Increment sum if remainder = 0
            if (!rem[digit]) {
                    sum++;
                    printf("sum incremented");
            }

            printf("\n");
        }

        // Store the result
        result[i] = sum;
    }
}

void output(int result[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }
}
