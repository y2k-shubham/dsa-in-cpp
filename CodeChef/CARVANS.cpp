#include <stdio.h>
#include <climits>

void scanInt(int &);
void inputAndProcess(int [], int);
void output(int [], int);

void scanInt(int &x) {
    register int c;

    c = getchar();
    x = 0;

    // ignoring characters (consuming unwanted bits)
    for ( ; ((c < 48) || (c > 57)); ) {
        c = getchar();
    }

    // reading and constructing numbers
    for ( ; ((c > 47) && (c < 58)); ) {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
}

int main() {
    int T;

    scanInt(T);
    int result[T];

    inputAndProcess(result, T);
    output(result, T);

    return 0;
}

void inputAndProcess(int result[], int T) {
    int N;
    int i;
    int j;
    int prevSpeed;
    int currSpeed;

    for (i = 0; i < T; i++) {
        scanInt(N);

        prevSpeed = INT_MAX;
        result[i] = 0;
        for (j = 1; j <= N; j++) {
            scanInt(currSpeed);

            if (currSpeed <= prevSpeed) {
                result[i]++;
                prevSpeed = currSpeed;
            }
        }
    }
}

void output(int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d\n", result[i]);
    }
}
