#include <stdio.h>

void input(int *, int *);
int subtract(int, int);
int modify(int);
void output(int);

int main() {
    int A;
    int B;
    int ANS;

    input(&A, &B);
    ANS = subtract(A, B);
    ANS = modify(ANS);
    output(ANS);

    return 0;
}

void input(int * a, int * b) {
    scanf("%d %d", a, b);
}

int subtract(int a, int b) {
    return (a - b);
}

int modify(int n) {
    int unitDigit;

    unitDigit = n % 10;
    n /= 10;

    unitDigit++;
    unitDigit %= 10;

    if (unitDigit == 0) {
        unitDigit = 1;
    }

    n = (n * 10) + unitDigit;

    return n;
}

void output(int n) {
    printf("%d\n", n);
}
