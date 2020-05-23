#include <stdio.h>
#include <math.h>

int input();
int findPrimePallindrome(int);
int isPallindrome(int);
int isPrime(int);
void output(int);

int main() {
    int N;
    int PP;

    N = input();
    PP = findPrimePallindrome(N);
    output(PP);

    return 0;
}

int input() {
    int N;
    scanf("%d", &N);
    return N;
}

int findPrimePallindrome(int N) {
    N = (N % 2) ? N : (N + 1);

    //printf("\nAfter adjustment, N = %d\n", N);
    for ( ; ; N++) {
        if (isPallindrome(N) && isPrime(N)) {
            break;
        }
    }

    return N;
}

int isPallindrome(int N) {
    int rev;
    int copy;

    rev = 0;
    copy = N;

    while (N > 0) {
        rev = (rev * 10) + (N % 10);
        N /= 10;
    }

    if (rev == copy) {
        //printf("\n%d is pallindrome\n", copy);
        return 1;
    } else {
        //printf("\n%d is not pallindrome\n", copy);
        return 0;
    }
}

int isPrime(int N) {
    int fact;
    int limit;

    //printf("\n\nChecking if  %d is Prime\n", N);
    if (N % 2) {
        limit = (int) sqrt(N);
        //printf("Limit = %d\n", limit);
        for (fact = 3; fact <= limit; fact += 2) {
            if (!(N % fact)) {
                //printf("Factor found : %d\nNot prime\n", fact);
                return 0;
            }
        }
        //printf("\nNo factor found: prime\n");
        return 1;
    } else {
        //printf("Even no: not prime\n");
        return 0;
    }
}

void output(int PP) {
    printf("%d\n", PP);
}
