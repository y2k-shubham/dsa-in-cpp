#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void inputAndProcess(float [][2], int);
void output(float [][2], int);

int main() {
    int T;

    scanf("%d", &T);
    float result[T][2];

    inputAndProcess(result, T);
    output(result, T);

    return 0;
}

void inputAndProcess(float result[][2], int T) {
    int i;
    float B;
    float LS;
    float sqrB;
    float sqrLS;

    for (i = 0; i < T; i++) {
        scanf("%f%f", &B, &LS);

        sqrB = pow(B, 2);
        sqrLS = pow(LS, 2);

        result[i][0] = sqrt(sqrLS - sqrB);
        result[i][1] = sqrt(sqrLS + sqrB);
    }
}

void output(float result[][2], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%f %f\n", result[i][0], result[i][1]);
    }
}
