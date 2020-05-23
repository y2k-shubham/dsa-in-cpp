#include <stdio.h>

void inputAndProcess(unsigned long [], int);
void output(unsigned long [], int);

int main() {
    int noOfTestCases;

    scanf("%d", &noOfTestCases);
    unsigned long numbers[noOfTestCases];

    inputAndProcess(numbers, noOfTestCases);
    output(numbers, noOfTestCases);

    return 0;
}

void inputAndProcess(unsigned long numbers[], int noOfTestCases) {
    int i;

    for (i = 0; i < noOfTestCases; i++) {
        scanf("%lu", &numbers[i]);

        if (numbers[i] % 2) {
            numbers[i]--;
        }
    }
}

void output(unsigned long numbers[], int noOfTestCases) {
    int i;

    for (i = 0; i < noOfTestCases; i++) {
        printf("%lu\n", numbers[i]);
    }
}
