#include <stdio.h>

void inputAndProcess(short [], int);
void output(char *[], short [], int);

int main() {
    int noOfTestCases;
    char * alice = "ALICE";
    char * bob = "BOB";
    char * winner[2];

    winner[0] = alice;
    winner[1] = bob;

    scanf("%d", &noOfTestCases);
    short result[noOfTestCases];

    inputAndProcess(result, noOfTestCases);
    output(winner, result, noOfTestCases);

    return 0;
}

void inputAndProcess(short result[], int noOfTestCases) {
    int i;
    unsigned long temp;

    for (i = 0; i < noOfTestCases; i++) {
        scanf("%ul", &temp);
        result[i] = (short) (temp % 2);
    }
}

void output(char * winner[], short result[], int noOfTestCases) {
    int i;

    for (i = 0; i < noOfTestCases; i++) {
        printf("%s\n", winner[result[i]]);
    }
}
