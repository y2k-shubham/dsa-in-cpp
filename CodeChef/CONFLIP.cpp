#include <stdio.h>
#include <climits>
#include <cmath>

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
    int G;
    int N;
    int Q;
    int I;
    int i;
    int j;

    scanInt(T);

    for (i = 1; i <= T; i++) {
        scanInt(G);

        for (j = 1; j <= G; j++) {
            scanInt(I);
            scanInt(N);
            scanInt(Q);

            if (!(N % 2) || (I == Q)) {
                printf("%d\n", (N / 2));
            } else {
                printf("%d\n", ((N / 2) + 1));
            }
        }
    }

    return 0;
}
